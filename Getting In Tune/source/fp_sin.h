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

//Including the header file
#include <stdint.h>

//References of Macros taken from Howdy Lecture
#define TRIG_SCALE_FACTOR	(2037)
#define HALF_PI				(3200)
#define PI 					(6399)
#define TWO_PI				(12799)


/*************************************************************************************************************
 *
 * Name :		  	int32_t fp_sin(int32_t x)
 *
 *
 *
 * Description :	This function takes x in radians and computes the corresponding sine wave
 *
 * Inputs: int32_t x - Angle in Radian
 *
 *
 * Return: NONE
 *************************************************************************************************************/
int32_t fp_sin(int32_t x);

/*************************************************************************************************************
 *
 * Name :		  	interpolate(int32_t x, int32_t x1, int32_t y1, int32_t x2, int32_t y2)
 *
 *
 *
 *
 * Description :	This function computes the midpoint from 2 given points
 *
 *
 * Inputs:
 * Point 1 -- int32_t x1, int32_t y1 : (x1,y1) one of the points on the sine wave
 * Point 2 -- int32_t x2, int32_t y2 : (x2,y2) one of the other point on the sine wave
 * int32_t x0 -- Middle point x co-ordinate
 *
 * Return: Y-co-ordinate value in integer
 *************************************************************************************************************/
int32_t interpolate(int32_t x, int32_t x1, int32_t y1, int32_t x2, int32_t y2);

#endif /* FP_SIN_H_ */
