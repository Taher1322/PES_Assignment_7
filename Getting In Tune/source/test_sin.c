/*****************************************************************************
* Copyright (C) 2021 by Gaurang Rane
*
* Redistribution, modification or use of this software in source or binary
* forms is permitted as long as the files maintain this copyright. Users are
* permitted to modify this and use it to learn about the field of embedded
* software. Gaurang Rane and the University of Colorado are not liable for
* any misuse of this material.
*
**************************************************************************/
/*************************************************************************
 *
 *
 *
 *    File name   : test_sin.c
 *    Description : function declaration for test_sin function
 *
 *    History :
 *    1. Date        : 30, Nov 2021
 *       Author      : Gaurang Rane
 *       Tools       : MCUXpresso IDE,GCC,PEMICRO-OPENSDA INTERFACE
 *       Description : function prototype is provided by Howdy Pierce
 *
 *    $Revision: 100 $
 **************************************************************************/


/*********************************************************************
 * Header File
 * *******************************************************************/
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
