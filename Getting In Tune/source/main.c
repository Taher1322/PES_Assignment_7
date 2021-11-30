/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
 *    File name   : main.c
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
#include <stdio.h>
#include <stdint.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "test_sin.h"
#include "adc.h"
#include "dac.h"
#include "fp_sin.h"
#include "systick.h"
#include "analog_out.h"


int main(void) {

	/* Initialisation of peripherals */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif

	init_systick();
	Init_TPM0();
	Init_DMA();
	Init_DAC();
	Init_TPM1();
	Init_ADC();

	//Testing integer sine function for errors with inbuilt math function
	PRINTF("Testing Sine function and comparing with standard sine function provided by Math Library\r\n");
	test_sin();
	PRINTF("\r\n Errors computed \r\n");

	int samples, i=0;
	uint16_t DAC_BUFFER[BUFFER_SIZE], ADC_BUFFER[BUFFER_SIZE];
	int tone_freq[] = {440, 587, 659, 880};
	reset_timer();
	while(1)
	{
		if(get_timer() >= 100)
		{
			i++;

			if(i == 4)
			{
				i = 0;
			}

			reset_timer();
		}

		samples = tone_to_samples(tone_freq[i], DAC_BUFFER, BUFFER_SIZE);
		DAC_Data(DAC_BUFFER, samples);

		ADC_Data(ADC_BUFFER, BUFFER_SIZE);
		analysis(ADC_BUFFER, BUFFER_SIZE);
	}

	return 0;

}
