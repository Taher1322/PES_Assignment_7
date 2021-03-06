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
 *    File name   : test_sin.c
 *    Description : Generated the sine wave using Math Library and gives the errors with the Integer sine calculated
 *
 *    Author: TAHER S UJJAINWALA
 * 	  Tools : MCUXpressor IDE
 * 	  Reference: This code is provided by Howdy
 *
 *    Date  : 11/30/2021
 *
 *
 */

//Including all the header files
#include <stdio.h>
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fp_sin.h"
#include "math.h"

/*function provided Howdy Pierce for testing integer */
void test_sin()
{
	double act_sin;
	double exp_sin;
	double err;
	double sum_sq = 0;
	double max_err = 0;
	int i= 0;
	for (i=-TWO_PI; i <= TWO_PI; i++) {
	exp_sin = sin( (double)i / TRIG_SCALE_FACTOR) * TRIG_SCALE_FACTOR;
	act_sin = fp_sin(i);
	err = act_sin - exp_sin;
	if (err < 0)
	err = -err;
	if (err > max_err)
	max_err = err;
	sum_sq += err*err;
	}
	printf("max_err=%d sum_sq=%d\n", (int)max_err, (int)sum_sq);
}
