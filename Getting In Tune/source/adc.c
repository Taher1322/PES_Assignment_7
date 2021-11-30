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
 *    File name   : adc.c
 *    Description : This file contains all the Initialization, Timer control, and Buffering the samples from DAC
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
#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "autocorrelate.h"
#include "adc.h"

void Init_ADC()
{

	//Enabling the clock for ADC0
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;

	//Low power configuration, clock dividing by 1, Short sampling, 16-bit conversion mode and bus clock enabling
	ADC0->CFG1 = ADC_CFG1_ADLPC (0) | ADC_CFG1_ADIV  (0) | ADC_CFG1_ADLSMP(0) |  ADC_CFG1_MODE  (3) | ADC_CFG1_ADICLK(0);


	//Configuring the status and control register
	//Hardware trigger selection, comparing function disabled, disbaling DMA, and Vref as refernce voltage
	ADC0->SC2 = ADC_SC2_ADTRG (1) |  ADC_SC2_ACFE  (0) | ADC_SC2_DMAEN (0) | ADC_SC2_REFSEL(0);

	//Configuring the status and control register
	//Disabling the conversion interrupt, selecting single ended input channel and selecting the channel
	ADC0->SC1[0] = ADC_SC1_AIEN(0) |  ADC_SC1_DIFF(0) |	ADC_SC1_ADCH(23);

	//Setting the trigger to generate on Timer 1 overflow
	SIM->SOPT7 = SIM_SOPT7_ADC0ALTTRGEN(1) | SIM_SOPT7_ADC0TRGSEL  (9);

}

void TMP1_Start(){
	//Starting the Timer 1
	TPM1->SC |= TPM_SC_CMOD(1);
}

void TMP1_Stop(){
	//Stopping the Timer 1
	TPM1->SC &= ~TPM_SC_CMOD_MASK;
}


void Init_TPM1() {

	//Enabling the clock for TPM1 Timer
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;

	//Disabling the timer
	TPM1->SC = 0;

	//Setting Mod and Count
	TPM1->MOD = TPM_MOD_MOD(SYSTEM_CLOCK / ADC_SAMPLING_FREQ);
	TPM1->CNT = 0;

	//Setting prescaler (dividing the clock by 1) and Setting the Timer 1 in up counting mode
	TPM1->SC = TPM_SC_PS(0) | TPM_SC_CPWMS(0);

}


void ADC_Data(uint16_t *buffer, uint32_t sample) {

	int i;
	//Timer 1 sampling starts
	TMP1_Start();
	memset(buffer, 0, sizeof(buffer));
	for(i =0; i < sample; i++)
	{
		//Waiting for the conversion to finish and the flag to set
		while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK));
		buffer[i] = ADC0->R[0];			//Storing the values in buffer
	}

	//Timer 1 sampling stops
	TMP1_Stop();
}


void analysis(uint16_t *input_buffer, uint32_t adc_samples)
{
	//Defining variables to calculate Minimum and Maximum values
	int i=0;
	uint16_t max = 0;
	uint32_t sum = 0;
	uint16_t min = 65535;

	//Checking each buffer values and updating the min and max variables based on the value. Calculating the summation as well.
	for (i=0; i < adc_samples; i++)
	{
		if (input_buffer[i] > max)
		{
			max = input_buffer[i];
		}
		if (input_buffer[i] < min)
		{
			min = input_buffer[i];
		}
		sum = sum + input_buffer[i];
	}

	int period = autocorrelate_detect_period(input_buffer, adc_samples, 1);
	PRINTF("min = %u max = %u avg = %u period = %d frequency = %d Hz\r\n",
			min, max, sum / adc_samples, period,  ADC_SAMPLING_FREQ / period);

}
