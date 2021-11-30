################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/adc.c \
../source/analog_out.c \
../source/autocorrelate.c \
../source/dac.c \
../source/fp_sin.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/systick.c \
../source/test_sin.c 

OBJS += \
./source/adc.o \
./source/analog_out.o \
./source/autocorrelate.o \
./source/dac.o \
./source/fp_sin.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/systick.o \
./source/test_sin.o 

C_DEPS += \
./source/adc.d \
./source/analog_out.d \
./source/autocorrelate.d \
./source/dac.d \
./source/fp_sin.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/systick.d \
./source/test_sin.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu90 -D__REDLIB__ -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\ujjai\Downloads\Getting In Tune\Getting In Tune\board" -I"C:\Users\ujjai\Downloads\Getting In Tune\Getting In Tune\source" -I"C:\Users\ujjai\Downloads\Getting In Tune\Getting In Tune" -I"C:\Users\ujjai\Downloads\Getting In Tune\Getting In Tune\drivers" -I"C:\Users\ujjai\Downloads\Getting In Tune\Getting In Tune\CMSIS" -I"C:\Users\ujjai\Downloads\Getting In Tune\Getting In Tune\utilities" -I"C:\Users\ujjai\Downloads\Getting In Tune\Getting In Tune\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


