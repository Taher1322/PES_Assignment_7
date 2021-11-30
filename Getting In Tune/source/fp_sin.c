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
 *    File name   : fp_sin.c
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
//Including all the header files
#include "fp_sin.h"
#include "MKL25Z4.h"
#include <stdio.h>
#include <stdint.h>
#include "assert.h"
#include "fsl_debug_console.h"

#include "adc.h"
#include "dac.h"
#include "autocorrelate.h"
#include "systick.h"


#define TRIG_TABLE_STEPS 							(32)
#define TRIG_TABLE_STEP_SIZE 						(HALF_PI/TRIG_TABLE_STEPS)


static const int16_t sin_lookup[TRIG_TABLE_STEPS+1] =
{0, 100, 200, 299, 397, 495, 591, 686, 780, 871, 960, 1047,
		1132, 1214, 1292, 1368, 1440, 1509, 1575, 1636, 1694, 1747,
		1797, 1842, 1882, 1918, 1949, 1976, 1998, 2015, 2027, 2035,
		2037};



int32_t fp_sin(int32_t x)
{
	int32_t index;
	int sign = 1;

	//Checking the boundary for sine wave - x value within -PI to PI by wrapping it using 2 PI
	  while (x < -PI){
	    x += TWO_PI;
	  }
	  while (x > PI){
	    x -= TWO_PI;
	  }

	  //sin(-x) = -sin(x)
	  if (x < 0) {
	    x = -x;
	    sign = -1;
	  }

	  //Making it within range 0 to +PI/2*/
	  if (x > HALF_PI) {
		  x = PI - x;
	  }

	  //Calculating index
	  index = TRIG_TABLE_STEPS * x / HALF_PI;

	  //Calcuting the angle
	  int32_t x1 = index * TRIG_TABLE_STEP_SIZE;


	  if (x1 == x)
	  {
		  return sign * sin_lookup[index];
	  }
	  else
	  {
		  int32_t x2 = (index+1) * TRIG_TABLE_STEP_SIZE;
		  int32_t interpolation_result = interpolate(x, x1, sin_lookup[index], x2, sin_lookup[index+1]);
		  return sign * interpolation_result;
	  }
}


int32_t interpolate(int32_t x, int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
  return ( (((x2 - x1)/2) + ((x - x1) * (y2 - y1))) / (x2 - x1) + y1);
}


