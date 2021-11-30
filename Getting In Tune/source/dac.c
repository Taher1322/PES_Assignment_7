/*****************************************************************************
* Copyright (C) 2021 by Taher Ujjainwala
*
* Redistribution, modification or use of this software in source or binary
* forms is permitted as long as the files maintain this copyright. Users are
* permitted to modify this and use it to learn about the field of embedded
* software. Taher Ujjainwala and the University of Colorado are not liable for
* any misuse of this material.
*
**************************************************************************/


/*************************
 *
 *
 *
 *    File name   : dac.c
 *    Description : This file contains all the Initialization, Timer control, DMA data handling and Buffering
 *
 *    Author: TAHER S UJJAINWALA
 * 	  Tools : MCUXpressor IDE
 * 	  General References used in development:
 * 	  Howdy lectures slides, Alexander Dean ADC, DAC, DMA, Waveform Generation section and White Math chapter
 * 	  PES Assignment 4 - https://github.com/Taher1322/PES_Assignment_4
 * 	  Guarang Rane and Harshwardhan Singh in crafting the sample generationg logic and analysis logic
 *
 *
 *    Date  : 11/30/2021
 *
 *
 */

//Including all the header files
#include "MKL25Z4.h"
#include <stdio.h>
#include <string.h>
#include "dac.h"

//Defining variables for DMA handling
static uint16_t buffer[1024];
static uint32_t total_bytes = 0;

//Generating analog waveform on PTE30
#define DAC_POS 30



void Init_DAC() {

	//Enabling Clock for DAC0 and clock for Port E
	SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

	//Configuring the DAC port
	PORTE->PCR[DAC_POS] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[DAC_POS] |= PORT_PCR_MUX(3);

	//Disabling the buffer mode
	DAC0->C1 = 0;
	DAC0->C2 = 0;

	//Control register
	//Enabling DAC and setting the reference voltage
	DAC0->C0 = DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK;

}

void TMP0_Start(){
	//Starting the Timer 0
	TPM0->SC |= TPM_SC_CMOD(1);
}

void TMP0_Stop(){
	//Stopping the Timer 0
	TPM0->SC &= ~TPM_SC_CMOD_MASK;
}



void Init_DMA() {

	//Enabling DMA clock and DMAMUX
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

	//To make any configuration for DMA, we have to disable the DMA first then make the configuration
	//Disabling the DMA
	DMAMUX0->CHCFG[0] = 0;

	//Enable interrupt when DMA tranfer is complete, Increment the source address, Setting source and destination data size as 2 bytes,
	//Enabling peripheral request and DMA
	DMA0->DMA[0].DCR = DMA_DCR_EINT_MASK |  DMA_DCR_SINC_MASK | DMA_DCR_SSIZE(2)  | DMA_DCR_DSIZE(2)  | DMA_DCR_ERQ_MASK  | DMA_DCR_CS_MASK;

	//Setting NVIC interrupt priority, clearing pending interrupt and enabling it.
	NVIC_SetPriority(DMA0_IRQn, 2);
	NVIC_ClearPendingIRQ(DMA0_IRQn);
	NVIC_EnableIRQ(DMA0_IRQn);

	//Enable DMA MUX channel with TPM0 overflow as trigger
	DMAMUX0->CHCFG[0] = DMAMUX_CHCFG_SOURCE(54);
}



void Init_TPM0() {

	//Enabling the clock for TPM0 Timer
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;

	//Setting the frequency to 48MHz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

	//Disabling the timer
	TPM0->SC = 0;

	//Setting Mod and Count
	TPM0->MOD = TPM_MOD_MOD(SYSTEM_CLOCK / (SYSTEM_CLOCK/1000));
	TPM0->CNT = 0;

	//Setting prescaler (dividing the clock by 1), Setting the Timer 1 in up counting mode, selecting low power timer clock, and Enable DMA
	TPM0->SC = TPM_SC_PS   (0) |  TPM_SC_CPWMS(0) | TPM_SC_CMOD (1) | TPM_SC_DMA_MASK;
}



void DAC_Data(uint16_t *buff, uint32_t sample){

	//Disabling Timer 0 sampling
	TMP0_Stop();

	//Coping the sample data into Total_bytes which will be used by DMA
	memcpy(&total_bytes, &sample, sizeof(int));

	//Copying the Sampled data into buffer
	memcpy(buffer, buff, sample*2);

	//Enabling Timer 0 sampling
	TMP0_Start();

	//Initializing source and destination registers
	DMA0->DMA[0].SAR = DMA_SAR_SAR((uint32_t) buffer);
	DMA0->DMA[0].DAR = DMA_DAR_DAR((uint32_t) (&(DAC0->DAT[0])));

	//Initializing the total byte to transfer register
	DMA0->DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(total_bytes * 2);

	//Enabling the DMAMUX flag
	DMAMUX0->CHCFG[0] |= DMAMUX_CHCFG_ENBL_MASK;
}


void DMA0_IRQHandler(void)
{
	//Clearing the IRQ flag
	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;

	//Initializing source and destination registers
	DMA0->DMA[0].SAR = DMA_SAR_SAR((uint32_t) buffer);
	DMA0->DMA[0].DAR = DMA_DAR_DAR((uint32_t) (&(DAC0->DAT[0])));

	//Initializing the total byte to transfer register
	DMA0->DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(total_bytes * 2);

	//Enabling the DMAMUX flag
	DMAMUX0->CHCFG[0] |= DMAMUX_CHCFG_ENBL_MASK;
}


