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
 *    File name   : fp_sin.h
 *    Description : This file is the main entry application file to run the frequency tones
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
#ifndef FP_SIN_H_
#define FP_SIN_H_

#include <stdint.h>


#define TRIG_SCALE_FACTOR	(2037)
#define HALF_PI				(3200)
#define PI 					(6399)
#define TWO_PI				(12799)

int32_t fp_sin(int32_t x);


int32_t interpolate(int32_t x, int32_t x1, int32_t y1, int32_t x2, int32_t y2);

#endif /* FP_SIN_H_ */
