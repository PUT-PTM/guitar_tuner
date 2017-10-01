#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_adc.h"
#include "misc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_spi.h"
#include "math.h"
#include "stm32f4xx_i2c.h"
#include "arm_math.h"
//#include "display_8x4.h"

// FFT settings
#define SAMPLES                    512            // 256 real party and 256 imaginary parts
#define FFT_SIZE                SAMPLES / 2        // FFT size is always the same size as we have samples, so 256 in our case



static __IO uint32_t TimingDelay = 0;
void Delay(uint32_t time)
{
	TimingDelay = time;
	while(TimingDelay!=0);
}

void SysTick_Handler(void)
{
	if(TimingDelay!=0x00)
		TimingDelay--;

}


float32_t buffer_input[SAMPLES];
float32_t buffer_output[FFT_SIZE];

uint32_t maxIndex=0;                // Index in Output array where max value is
float32_t maxValue;             // Max FFT value is stored here

uint16_t i=0;
uint16_t tmp=0;

arm_rfft_instance_f32 S;
arm_cfft_radix4_instance_f32 S_CFFT;


void TIM4_IRQHandler(void){
            if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
            {
//              if(licznik>4200)
//                  licznik=0;
//              if(licznik<4096){
//                  if(licznik==0)
//                      GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
//                  tmp = ADC_GetConversionValue(ADC1);
//                  buffer_input[licznik]=(float32_t)tmp;
//              }
//              licznik++;
                TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
            }
}
void TIM3_IRQHandler(void){
            if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
            {
                //Calculate Real FFT
//                arm_rfft_f32(&S, buffer_input, buffer_output);
//                // Calculate magnitude
//                arm_cmplx_mag_f32(buffer_output, buffer_output_mag, 4096);
//                // Get maximum value of magnitude
//                arm_max_f32(buffer_output_mag, 4096, &maxvalue, &maxvalueindex);
                GPIO_ToggleBits(GPIOD, GPIO_Pin_15);

                TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
            }
}
void timerconf(){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = 8400-1;
    TIM_TimeBaseStructure.TIM_Prescaler = 10000-1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    TIM_Cmd(TIM3, ENABLE);
}
void timer4conf(){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = 200-1;
    TIM_TimeBaseStructure.TIM_Prescaler = 100-1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    TIM_Cmd(TIM4, ENABLE);
}
void nvic(){
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}
void nvic4(){
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
}

int main(void)
{
    for(i=0; i<SAMPLES; i++){
        buffer_input[i]=0;
    }
    SystemInit();
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE); // zegar dla portu GPIO z którego wykorzystany zostanie pin jako wejście ADC (PA1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); // zegar dla modułu ADC1
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

//inicjalizacja wejścia ADC
    GPIO_InitTypeDef GPIO_ADC;
    GPIO_ADC.GPIO_Pin = GPIO_Pin_1;
    GPIO_ADC.GPIO_Mode = GPIO_Mode_AN;
    GPIO_ADC.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_ADC.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(GPIOA, &GPIO_ADC);


    GPIO_DISPLAY.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5;
    GPIO_DISPLAY.GPIO_Mode = GPIO_Mode_OUT;
   	GPIO_DISPLAY.GPIO_OType = GPIO_OType_PP;
    GPIO_DISPLAY.GPIO_Speed = GPIO_Speed_100MHz;
   	GPIO_DISPLAY.GPIO_PuPd = GPIO_PuPd_NOPULL;
   	GPIO_Init(GPIOA, &GPIO_DISPLAY);


   	GPIO_SEGMENT.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8| GPIO_Pin_9| GPIO_Pin_10| GPIO_Pin_11;
    GPIO_SEGMENT.GPIO_Pin |= GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
   	GPIO_SEGMENT.GPIO_Mode = GPIO_Mode_OUT;
   	GPIO_SEGMENT.GPIO_OType = GPIO_OType_PP;
   	GPIO_SEGMENT.GPIO_Speed = GPIO_Speed_100MHz;
   	GPIO_SEGMENT.GPIO_PuPd = GPIO_PuPd_NOPULL;
   	GPIO_Init(GPIOE, &GPIO_SEGMENT);

//
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    GPIO_InitTypeDef  GPIO_LED;

    GPIO_LED.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
    GPIO_LED.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_LED.GPIO_OType = GPIO_OType_PP;
    GPIO_LED.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_LED);


//
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&ADC_CommonInitStructure);

    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_84Cycles);

    ADC_Cmd(ADC1, ENABLE);
    SysTick_Config(SystemCoreClock / 1000000);
   // SysTick_Config(SystemCoreClock / 10000);//for delay


    ADC_SoftwareStartConv(ADC1);
  //  timerconf();
  //  nvic();
  //   timer4conf();
  //  nvic4();
  //  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

    arm_cfft_radix4_instance_f32 S; // ARM CFFT module

    //display_test_characters();

    while(1){
        for (i = 0; i < SAMPLES; i += 2) {
            // Each 22us ~ 45kHz sample rate
            Delay(21);
            // We assume that sampling and other stuff will take about 1us

            // Real part, must be between -1 and 1
            tmp=ADC_GetConversionValue(ADC1);
            buffer_input[(uint16_t)i] = (float32_t)((float32_t)ADC_GetConversionValue(ADC1) - (float32_t)2048.0);
            // Imaginary part
            buffer_input[(uint16_t)(i + 1)] = 0;
        }

        GPIO_ToggleBits(GPIOD,GPIO_Pin_14);

        GPIO_SetBits(GPIOD,GPIO_Pin_15);

        // Initialize the CFFT/CIFFT module, intFlag = 0, doBitReverse = 1
        arm_cfft_radix4_init_f32(&S, FFT_SIZE, 0, 1);

        // Process the data through the CFFT/CIFFT module
        arm_cfft_radix4_f32(&S, buffer_input);

        // Process the data through the Complex Magniture Module for calculating the magnitude at each bin
        arm_cmplx_mag_f32(buffer_input, buffer_output, FFT_SIZE);

        // Calculates maxValue and returns corresponding value
        arm_max_f32(buffer_output, FFT_SIZE, &maxValue, &maxIndex);
        GPIO_ResetBits(GPIOD, GPIO_Pin_15);


        GPIO_ResetBits(GPIOD, GPIO_Pin_12);
        GPIO_ResetBits(GPIOD, GPIO_Pin_13);

        if(maxIndex>(uint32_t)10)
            GPIO_SetBits(GPIOD, GPIO_Pin_12);
        if(maxIndex>50)
            GPIO_SetBits(GPIOD, GPIO_Pin_13);
        //if(maxIndex>300)
            //GPIO_SetBits(GPIOD, GPIO_Pin_14);
          }
}
