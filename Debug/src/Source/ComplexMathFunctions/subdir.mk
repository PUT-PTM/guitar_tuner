################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Source/ComplexMathFunctions/arm_cmplx_conj_f32.c \
../src/Source/ComplexMathFunctions/arm_cmplx_conj_q15.c \
../src/Source/ComplexMathFunctions/arm_cmplx_conj_q31.c \
../src/Source/ComplexMathFunctions/arm_cmplx_dot_prod_f32.c \
../src/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q15.c \
../src/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q31.c \
../src/Source/ComplexMathFunctions/arm_cmplx_mag_f32.c \
../src/Source/ComplexMathFunctions/arm_cmplx_mag_q15.c \
../src/Source/ComplexMathFunctions/arm_cmplx_mag_q31.c \
../src/Source/ComplexMathFunctions/arm_cmplx_mag_squared_f32.c \
../src/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q15.c \
../src/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q31.c \
../src/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_f32.c \
../src/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q15.c \
../src/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q31.c \
../src/Source/ComplexMathFunctions/arm_cmplx_mult_real_f32.c \
../src/Source/ComplexMathFunctions/arm_cmplx_mult_real_q15.c \
../src/Source/ComplexMathFunctions/arm_cmplx_mult_real_q31.c 

OBJS += \
./src/Source/ComplexMathFunctions/arm_cmplx_conj_f32.o \
./src/Source/ComplexMathFunctions/arm_cmplx_conj_q15.o \
./src/Source/ComplexMathFunctions/arm_cmplx_conj_q31.o \
./src/Source/ComplexMathFunctions/arm_cmplx_dot_prod_f32.o \
./src/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q15.o \
./src/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q31.o \
./src/Source/ComplexMathFunctions/arm_cmplx_mag_f32.o \
./src/Source/ComplexMathFunctions/arm_cmplx_mag_q15.o \
./src/Source/ComplexMathFunctions/arm_cmplx_mag_q31.o \
./src/Source/ComplexMathFunctions/arm_cmplx_mag_squared_f32.o \
./src/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q15.o \
./src/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q31.o \
./src/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_f32.o \
./src/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q15.o \
./src/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q31.o \
./src/Source/ComplexMathFunctions/arm_cmplx_mult_real_f32.o \
./src/Source/ComplexMathFunctions/arm_cmplx_mult_real_q15.o \
./src/Source/ComplexMathFunctions/arm_cmplx_mult_real_q31.o 

C_DEPS += \
./src/Source/ComplexMathFunctions/arm_cmplx_conj_f32.d \
./src/Source/ComplexMathFunctions/arm_cmplx_conj_q15.d \
./src/Source/ComplexMathFunctions/arm_cmplx_conj_q31.d \
./src/Source/ComplexMathFunctions/arm_cmplx_dot_prod_f32.d \
./src/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q15.d \
./src/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q31.d \
./src/Source/ComplexMathFunctions/arm_cmplx_mag_f32.d \
./src/Source/ComplexMathFunctions/arm_cmplx_mag_q15.d \
./src/Source/ComplexMathFunctions/arm_cmplx_mag_q31.d \
./src/Source/ComplexMathFunctions/arm_cmplx_mag_squared_f32.d \
./src/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q15.d \
./src/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q31.d \
./src/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_f32.d \
./src/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q15.d \
./src/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q31.d \
./src/Source/ComplexMathFunctions/arm_cmplx_mult_real_f32.d \
./src/Source/ComplexMathFunctions/arm_cmplx_mult_real_q15.d \
./src/Source/ComplexMathFunctions/arm_cmplx_mult_real_q31.d 


# Each subdirectory must supply rules for building sources it contributes
src/Source/ComplexMathFunctions/%.o: ../src/Source/ComplexMathFunctions/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DARM_MATH_CM4 -DSTM32F4 -DSTM32F407VGTx -DDEBUG -DSTM32F40XX -DSTM32F40_41xxx -D__ASSEMBLY__ '-DHSE_VALUE=8000000' -DUSE_STDPERIPH_DRIVER -D_FPU_USED '-D_FPU_PRESENT=1' -I"/home/jaroslaw-wieczorek/stm32workspace/stm32f407_stdperiph_lib" -I"/home/jaroslaw-wieczorek/stm32workspace/stm32f407_stdperiph_lib/CMSIS/core" -I"/home/jaroslaw-wieczorek/stm32workspace/stm32f407_stdperiph_lib/CMSIS/device" -I"/home/jaroslaw-wieczorek/stm32workspace/stm32f407_stdperiph_lib/StdPeriph_Driver/inc" -I"/home/jaroslaw-wieczorek/stm32workspace/STM32F4xx_DSP_StdPeriph_Lib_V1.8.0/Libraries/CMSIS/Device/ST/STM32F4xx" -I"/home/jaroslaw-wieczorek/stm32workspace/STM32F4xx_DSP_StdPeriph_Lib_V1.8.0" -I"/home/jaroslaw-wieczorek/stm32workspace/STM32F4xx_DSP_StdPeriph_Lib_V1.8.0/Libraries/CMSIS/DSP_Lib/Source" -I"/home/jaroslaw-wieczorek/stm32workspace/guitar/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


