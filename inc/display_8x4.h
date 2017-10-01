/*
 * diplay_LCD.h
 *
 *  Created on: 28.09.2017
 *      Author: jaroslaw-wieczorek
 */

#ifndef DISPLAY_8X4_H_
#define DISPLAY_8X4_H_


#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx.h"

GPIO_InitTypeDef  GPIO_SEGMENT;
GPIO_InitTypeDef  GPIO_DISPLAY;

void display_test_characters();
void display_turn_OnOffSegments(int segment);
void display_turn_OnSegments(int segment);
void display_character(int segment, char character);



#endif /* DISPLAY_8X4_H_ */
