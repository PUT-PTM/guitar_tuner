################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

OBJS += \
./startup/startup_stm32.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I"/home/jaroslaw-wieczorek/stm32workspace/stm32f407_stdperiph_lib" -I"/home/jaroslaw-wieczorek/stm32workspace/stm32f407_stdperiph_lib/CMSIS/core" -I"/home/jaroslaw-wieczorek/stm32workspace/stm32f407_stdperiph_lib/CMSIS/device" -I"/home/jaroslaw-wieczorek/stm32workspace/stm32f407_stdperiph_lib/StdPeriph_Driver/inc" -I"/home/jaroslaw-wieczorek/stm32workspace/guitar/inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


