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
 *    File name   : analog_out.c
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
#include <stdio.h>
#include <stdint.h>
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#include "analog_out.h"
#include "autocorrelate.h"
#include "adc.h"
#include "systick.h"
#include "dac.h"
#include "fp_sin.h"


size_t tone_to_samples(int tone_freq, uint16_t *buffer, int size)
{

	int i=0;
	int period = ((DAC_SAMPLING_FREQ + (tone_freq/2)) / tone_freq);
	int total_iterations = size/period;
	int sample = period*total_iterations;

	for (i=0; i < sample; i++) {
		buffer[i] = fp_sin(i * TWO_PI / period) + TRIG_SCALE_FACTOR;
	}

	PRINTF("Generated %d samples at %d Hz; computed period=%d, observed=%d\r\n",
			sample, tone_freq, ((DAC_SAMPLING_FREQ + (tone_freq/2)) / tone_freq),
			autocorrelate_detect_period(buffer, sample, 0));

	   return sample;
}
