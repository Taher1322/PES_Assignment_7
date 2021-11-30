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
 *    File name   : adc.h
 *    Description : This file contains all the function prototyping which includes Initialization, Timer control, and Buffering the
 *    samples from DAC
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

#ifndef ADC_H_
#define ADC_H_

//Including the Header files
#include <stdint.h>

//Defines for given ADC Sampling Frequency and System Clock
#define ADC_SAMPLING_FREQ       	(96000)					//ADC Sampling frequency 96KHz
#define SYSTEM_CLOCK                (48e6)					//Clock Frequency 48MHz

/*************************************************************************************************************
 *
 * Name :		  	void Init_ADC()
 *
 *
 *
 * Description :	This function initializes the ADC
 * It defines all the control and status registers as required - sampling, scanning, mode, electrode voltage
 *
 * Inputs: NONE
 *
 * Return: NONE
 *************************************************************************************************************/
void Init_ADC();

/*************************************************************************************************************
 *
 * Name :		  	void Init_TPM1()
 *
 *
 *
 * Description :	This function initializes the Timer 1
 *
 * Inputs: NONE
 *
 * Return: NONE
 *************************************************************************************************************/
void Init_TPM1();


/*************************************************************************************************************
 *
 * Name :		  	void ADC_Data(uint16_t *buffer, uint32_t sample)
 *
 *
 *
 * Description :	This function reads the DAC output data into the buffer
 * It reads until the conversion is complete
 *
 * Inputs:
 * *buffer Pointer to buffer array - Input ADC Buffer
 * sample Total number of bytes
 *
 * Return: NONE
 *************************************************************************************************************/
void ADC_Data(uint16_t *buffer, uint32_t sample);


/*************************************************************************************************************
 *
 * Name :		  	void analysis(uint16_t *input_buffer, uint32_t adc_samples)
 *
 *
 *
 * Description :	This function processes ADC Input buffer and gives the analysis
 *
 * Inputs:
 * *input_buffer Pointer to buffer array - Input ADC Buffer
 * samples Total number of bytes
 *
 *
 * Return: NONE
 *************************************************************************************************************/
void analysis(uint16_t *input_buffer, uint32_t adc_samples);

#endif /* ADC_H_ */
