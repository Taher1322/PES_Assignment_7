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
 *    File name   : dac.h
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

#ifndef DAC_H_
#define DAC_H_

//Including the header file
#include <stdint.h>

//Defining Macros
#define DAC_SAMPLING_FREQ          	(48000)			//DAC sampling frequency 48KHz
#define SYSTEM_CLOCK            	(48e6)			//Clock Frequency 48MHz

/*************************************************************************************************************
 *
 * Name :		  	void Init_DAC(void)
 *
 *
 * Description :	This function initializes the DAC
 *
 * Inputs: NONE
 *
 *
 * Return: NONE
 *************************************************************************************************************/
void Init_DAC(void);


/*************************************************************************************************************
 *
 * Name :		  	void Init_DMA(void)
 *
 *
 *
 * Description :	This function initialized the DMA
 *
 * Inputs: NONE
 *
 *
 * Return: NONE
 *************************************************************************************************************/
void Init_DMA(void);


/*************************************************************************************************************
 *
 * Name :		  	void Init_TPM0(void)
 *
 *
 *
 * Description :	This function initializes the Timer 1
 *
 * Inputs: NONE
 *
 * Return: NONE
 *************************************************************************************************************/
void Init_TPM0(void);


/*************************************************************************************************************
 *
 * Name :		  	void DAC_Data(uint16_t *buffer, uint32_t sample)
 *
 *
 *
 * Description :	This function processes Analog waveform based on the Tone frequency.
 * It processes the data and stores it into buffer (same buffer for all tones)
 *
 * Inputs:
 * *buffer Pointer to buffer array - DAC Buffer
 * sample Total number of bytes
 *
 *
 * Return: NONE
 *************************************************************************************************************/
void DAC_Data(uint16_t *buffer, uint32_t sample);

#endif /* DAC_H_ */
