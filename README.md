# PES_Assignment_7

Code for Assignment 7 for PES, ECEN-5813, Fall 2021 - Due Date >> 11/30/2021 @ 10:30 AM MDT

# Author: TAHER UJJAINWALA </br>

Contact me if you are facing issue in execution of the code @ tauj5361@colorado.edu

# Getting In Tune </br>

# Project source details </br>
-main.c --> Main application script initializes the Four Tones which is then generated using DAC and ADC  </br>
-adc.c --> This file contains all the ADC implementation, reading the sample sampled by DAC and Performing analysis and prints the values </br>
-dac.c --> This file contails all the DAC implementation, DMA implementation, Generating a wave based on particular tone frequency </br>
-fp_sin.c --> Using Integer Lookup table, sine wave is generated without any Floating point operations or Math Library </br>
-systick.c --> This file initialized the system clock and Timer to generate interrupt every 10ms </br>
-analog_out.c --> This file samples the tone based on the frequency (40 Hz (an A4); 587 Hz (a D5); 659 Hz (an E5); and 880 Hz (an A5) </br>
-test_sin.c --> This file implements Standard Sine wave using MATH Library and gives the error between the calculated and standard waveform </br>
-autocorrelate.c --> This file Detect the period of the fundamental frequency in a buffer full of samples </br>

# Project Comments: </br>

1) A function to accurately compute sin(x) using only integer math. You may do this using </br>
either a lookup table or a hybrid Taylor series approach, as long as you meet the requirements  </br>
below.   </br>
 
2) A tone_to_samples() function, which computes the samples representing a pure tone of a </br>
specified frequency, based on your sin(x) function. Use this function to fill a buffer of output </br>
samples. </br>
 
3) An audio output module. This module will contain the necessary configuration and runtime </br>
code that allows you to pass your computed buffer of audio samples into the module. The  </br>
module will use the KL25Z’s DAC, TPM0, and DMA hardware to repeatedly play out the buffer  </br>
without further intervention from your main loop.   </br>
 
4) An audio input module. This module will contain the necessary configuration and runtime code </br>
to capture a number of input samples at the capture sampling frequency specified above.  </br>
 
5) An audio analysis module. After capture, your code should analyze the captured buffer, </br>
reporting the minimum, maximum, and mean values. You should also integrate my </br>
autocorrelation function, provided on Canvas, to recover the fundamental period represented in </br>
the sampled audio. </br>
 
6) An oscilloscope. After you have all the code working, you should connect an oscilloscope to </br>
the DAC’s output on pin PTE30, available on the Freedom header at J10 11. Use the </br>
oscilloscope to verify that there is no tearing at the transition point in your playout buffer. </br>

# Developement Details </br>
Software used Developed using MCUExpresso IDE 7.2.0 on Windows 10. </br>
DEBUG Mode - Prints DEBUG Messages to UART terminal at Baud Rate of 115200 and 8N1. </br>
To see the console messages in UART mode change to UART in quick settings and open a new Terminal with 115200 Baud Rate and 8N1 settings </br>

# OUTPUT WAVEFORM IMAGES are attached in the repository







 


