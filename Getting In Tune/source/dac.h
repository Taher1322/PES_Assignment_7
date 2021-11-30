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

#include <stdint.h>


#define DAC_SAMPLING_FREQ          	(48000)
#define SYSTEM_CLOCK            	(48e6)


void Init_DAC(void);


void Init_DMA(void);


void Init_TPM0(void);


void DAC_Data(uint16_t *buffer, uint32_t sample);

#endif /* DAC_H_ */
