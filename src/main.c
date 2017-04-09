/**
  ******************************************************************************
  * @file    main.c
  * @author  Wieczorek Jarosław & Norel Mateusz
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_conf.h"
#include "misc.h"

 uint16_t Data;

int main(void)
{
	 SystemInit();

	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB |
			 	 	 	 	RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE);
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1 | RCC_APB1Periph_SPI3, ENABLE);
	 RCC_PLLI2SCmd(ENABLE);


	 GPIO_InitTypeDef pin;
	 pin.GPIO_Pin = GPIO_Pin_4;
	 pin.GPIO_Mode = GPIO_Mode_OUT;
	 pin.GPIO_OType = GPIO_OType_PP;
	 pin.GPIO_PuPd = GPIO_PuPd_DOWN;
	 pin.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOD, &pin);

	 pin.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_9; 					//I2S SCL and SDA pins
	 GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_SPI3); 	//connecting pin 4 of port A to the SPI3 peripheral


	 I2S_InitTypeDef i2s;
	 i2s.I2S_AudioFreq = I2S_AudioFreq_48k;
	 i2s.I2S_MCLKOutput = I2S_MCLKOutput_Enable;
	 i2s.I2S_Mode = I2S_Mode_MasterTx;
	 i2s.I2S_DataFormat = I2S_DataFormat_16b;
	 i2s.I2S_Standard = I2S_Standard_Phillips;
	 i2s.I2S_CPOL = I2S_CPOL_Low;
	 I2S_Init(SPI3, &i2s);
	 I2S_Cmd(SPI3, ENABLE);


	I2C_InitTypeDef i2c;
	i2c.I2C_ClockSpeed = 100000;
	i2c.I2C_Mode = I2C_Mode_I2C;
	i2c.I2C_OwnAddress1 = 99;
	i2c.I2C_Ack = I2C_Ack_Enable;
	i2c.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	i2c.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_Init(I2C1, &i2c);  										 //initialize the I2C peripheral ...
	I2C_Cmd(I2C1, ENABLE);          							 //... and turn it on


	GPIO_SetBits(GPIOD, GPIO_Pin_4);


	 SPI_I2S_SendData(SPI3, Data);
	 SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE);

	for(;;);
}
