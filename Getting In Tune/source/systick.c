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
 *    File name   : systick.c
 *    Description : This file defines the functions to reset timer, start timer, get current time since start using Systick Timer
 *
 *    Author: TAHER S UJJAINWALA
 * 	  Tools : MCUXpressor IDE
 * 	  Reference: Howdy lectures and Alexander Dean Systick Timer section
 * 	  This section of code is leveraged from Assignment 4 - Buffahati
 *
 *    Date  : 11/30/2021
 *
 *
 */

#include "MKL25Z4.h"
#include "systick.h"
#include "core_cm0plus.h"


/******************************************************************************
* Variable here
******************************************************************************/
volatile ticktime_t timer_count = 0; 		/*Stores actual value of systick counter*/
volatile ticktime_t timer_reset_count = 0;	/*Stores value of systick counter on reset*/
volatile ticktime_t timer_value = 0;		/*Gives systick count after reset*/

//Defining variables to read the time and reset the timer value
volatile ticktime_t timer_start;
volatile ticktime_t reset_tim_value;


void init_systick() 										// initialize the timing system
{
	SysTick->LOAD  = CLOCK;              					// set reload register
	NVIC_SetPriority (SysTick_IRQn, 1); 					// set Priority for Systick Interrupt
	SysTick->VAL   = 0;                                     // Load the SysTick Counter Value
	SysTick->CTRL  = SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk;                 // Enable SysTick IRQ and SysTick Timer
}


//Timer interrupt that is called every 10ms
void SysTick_Handler()
{
	timer_start++;
}


//Returns Ticks since the last call to reset_timer()
ticktime_t get_timer()
{
	return (timer_start - reset_tim_value);
}


//Resets the timer to 0 without affecting the now() values
void reset_timer()
{
	reset_tim_value = now();
}

//Returns the time since boot
ticktime_t now()
{
	return timer_start;
}
