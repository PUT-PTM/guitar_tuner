/*
 * display_8x4.c
 *
 *  Created on: 28.09.2017
 *      Author: jaroslaw-wieczorek
 */

/* Segment
 * 0 - PA2
 * 1 - PA3
 * 2 - PA4
 * 3 - PA5
 */


#include <stdint.h>
#include <stdio.h>

#include "display_8x4.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx.h"

void display_test_characters()
{
	char characters[18] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H'};
    for(int i=0; i<18; i++)
	{

	   	display_character(1,characters[i]);
	    Delay(200000);

	}

}


/*
 * 								   PE14	PE13 PE12 PE11 PE10 PE9  PE8 PE7(.)
 * Cyfra 	gfedcba 	abcdefg    a 	b 	 c	  d    e 	f 	 g
 *   0 	 	  0×3F 		  0×7E 	   1 	1 	 1 	  1    1 	1
 *   1 	 	  0×06 	  	  0×30 		    1 	 1
 *   2 		  0×5B 	      0×6D 	   1 	1 	   	  1    1 	     1
 *   3 		  0×4F        0×79 	   1 	1 	 1 	  1 	         1
 *   4 		  0×66        0×33 		    1 	 1 	      		1 	 1
 *   5 		  0×6D 		  0×5B 	   1 	     1 	  1 	    1 	 1
 *   6 		  0×7D 		  0×5F 	   1 	     1 	  1    1 	1 	 1
 *   7 		  0×07 		  0×70 	   1 	1 	 1
 *   8 		  0×7F 		  0×7F 	   1 	1 	 1 	  1    1 	1 	 1
 *   9 		  0×6F 		  0×7B 	   1 	1 	 1 	  1 	    1 	 1
 *   A 		  0×77 		  0×77 	   1 	1 	 1 	  	   1 	1	 1	  1
 *   b 		  0×7C 		  0×1F 		         1 	  1    1 	1 	 1	  1
 *   C 		  0×39 		  0×4E 	   1 	       	  1    1 	1		  1
 *   d 		  0×5E 		  0×3D 		    1 	 1 	  1	   1 	     1	  1
 *   E 		  0×79 		  0×4F 	   1 	   		  1    1 	1 	 1	  1
 *   F 		  0×71 		  0×47 	   1 	          1    1 	1		  1
 *   H							   1 	          1    1 	1	 	  1
*/

/*
 *   <::A::>
 * 	<D>	  <B>
 * 	 <::G::>
 *  <E>	  <C>
 *   <::D::>  (H)
 *
 */


void display_turn_on_digit(int segment)
{
	switch(segment){
	case 3:
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		break;
	}
	case 2:
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		break;
	}
	case 1:
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
		break;
	}
	case 0:
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		break;
	}
	default:
	{
		GPIO_SetBits(GPIOA, GPIO_SEGMENT.GPIO_Pin);
	}
	}
}

void display_character(int digit, char character)
{	// channel 0-3
	uint32_t pins = 0;

	display_turn_on_digit(digit);
	GPIO_SetBits(GPIOE, GPIO_SEGMENT.GPIO_Pin);
	if(character == '0')
	{
		// PE14	PE13 PE12 PE11 PE10 PE9  PE8
		// a 	b 	 c	  d    e 	f 	 g
		// 1	1 	 1	  1	   1	1
		GPIO_ResetBits(GPIOE, GPIO_Pin_14 |GPIO_Pin_13 | GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_10| GPIO_Pin_9);
	}
	else if (character == '1')
	{
		// PE14	PE13 PE12 PE11 PE10 PE9  PE8
		// a 	b 	 c	  d    e 	f 	 g
		//  	1 	 1

		pins =  GPIO_Pin_13 | GPIO_Pin_12;
		GPIO_ResetBits(GPIOE, pins);
	}
	if(character == '2')
	{
		// PE14	PE13 PE12 PE11 PE10 PE9  PE8
		// a 	b 	 c	  d    e 	f 	 g
		// 1 	1 	   	  1    1 	     1
		pins =  GPIO_Pin_14| GPIO_Pin_13 |GPIO_Pin_11 | GPIO_Pin_10 | GPIO_Pin_8;
		GPIO_ResetBits(GPIOE, pins);
	}
	if(character == '3')
	{
		// PE14	PE13 PE12 PE11 PE10 PE9  PE8
		// a 	b 	 c	  d    e 	f 	 g
		// 1 	1 	 1 	  1 	         1

		pins =  GPIO_Pin_14 |GPIO_Pin_13 | GPIO_Pin_12 | GPIO_Pin_11 |GPIO_Pin_8;
		GPIO_ResetBits(GPIOE, pins);
	}

	if(character == '4')
	{
		// PE14	PE13 PE12 PE11 PE10 PE9  PE8
		// a 	b 	 c	  d    e 	f 	 g
	    // 	    1 	 1 	       		1    1
		pins =  GPIO_Pin_13 |GPIO_Pin_12 | GPIO_Pin_9 | GPIO_Pin_8;
		GPIO_ResetBits(GPIOE, pins);
	}
	if(character == '5')
	{
		// PE14	PE13 PE12 PE11 PE10 PE9  PE8
		// a 	b 	 c	  d    e 	f 	 g
		// 1 	     1 	  1 	    1 	 1
		pins =  GPIO_Pin_14 | GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_9 |GPIO_Pin_8;
		GPIO_ResetBits(GPIOE, pins);
	}
	if(character == '6')
	{
		// PE14	PE13 PE12 PE11 PE10 PE9  PE8
		// a 	b 	 c	  d    e 	f 	 g
		// 1 	     1 	  1    1 	1 	 1
		pins =  GPIO_Pin_14 | GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_10 | GPIO_Pin_9 |GPIO_Pin_8;
		GPIO_ResetBits(GPIOE, pins);
	}
	if(character == '7')
	{
		// PE14	PE13 PE12 PE11 PE10 PE9  PE8
		// a 	b 	 c	  d    e 	f 	 g
		// 1 	1    1
		pins =  GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12;
		GPIO_ResetBits(GPIOE, pins);
	}
	if(character == '8')
	{
		// PE14	PE13 PE12 PE11 PE10 PE9  PE8
		// a 	b 	 c	  d    e 	f 	 g
		// 1 	1 	 1 	  1    1 	1 	 1
		pins =  GPIO_Pin_14 |GPIO_Pin_13 | GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_10 |GPIO_Pin_9 |GPIO_Pin_8;
		GPIO_ResetBits(GPIOE, pins);
	}
	if(character == '9')
	{
		// PE14	PE13 PE12 PE11 PE10 PE9  PE8
		// a 	b 	 c	  d    e 	f 	 g
		// 1 	1 	 1 	  1     	1 	 1
		pins =  GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_9 | GPIO_Pin_8;
		GPIO_ResetBits(GPIOE, pins);
	}
	if(character == 'A')
	{
		// PE14	PE13 PE12 PE11 PE10 PE9  PE8  PE7
		// a 	b 	 c	  d    e 	f 	 g	  .
		// 1 	1 	 1 	  	   1 	1	 1 	  1
		pins =  GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12 | GPIO_Pin_10 | GPIO_Pin_9 | GPIO_Pin_8 | GPIO_Pin_7;
		GPIO_ResetBits(GPIOE, pins);
	}
	if(character == 'B')
	{
		// PE14	PE13 PE12 PE11 PE10 PE9  PE8  PE7
		// a 	b 	 c	  d    e 	f 	 g	  .
		// 	         1 	  1    1 	1 	 1	  1
		pins =  GPIO_Pin_12 |GPIO_Pin_11 | GPIO_Pin_10 | GPIO_Pin_9 |GPIO_Pin_8| GPIO_Pin_7;
		GPIO_ResetBits(GPIOE, pins);
	}
	if(character == 'C')
	{
		// PE14	PE13 PE12 PE11 PE10 PE9  PE8  PE7
		// a 	b 	 c	  d    e 	f 	 g	  .
		// 1 	       	  1    1 	1		  1
		pins =  GPIO_Pin_14 |GPIO_Pin_11 | GPIO_Pin_10 | GPIO_Pin_9 | GPIO_Pin_7;
		GPIO_ResetBits(GPIOE, pins);
	}

	if(character == 'D')
	{
		// PE14	PE13 PE12 PE11 PE10 PE9  PE8  PE7
		// a 	b 	 c	  d    e 	f 	 g	  .
		//      1 	 1 	  1	   1 	     1	  1
		pins =  GPIO_Pin_13 |GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_10 | GPIO_Pin_8| GPIO_Pin_7;
		GPIO_ResetBits(GPIOE, pins);
	}
	if(character == 'E')
	{
		// PE14	PE13 PE12 PE11 PE10 PE9  PE8  PE7
		// a 	b 	 c	  d    e 	f 	 g	  .
		// 1 	   		  1    1 	1 	 1	  1
		pins =  GPIO_Pin_14 |GPIO_Pin_11 | GPIO_Pin_10 | GPIO_Pin_9 | GPIO_Pin_8 | GPIO_Pin_7;
		GPIO_ResetBits(GPIOE, pins);
	}
	if(character == 'F')
	{
		// PE14	PE13 PE12 PE11 PE10 PE9  PE8  PE7
		// a 	b 	 c	  d    e 	f 	 g	  .
		// 1 	               1 	1	 1	  1
		pins =  GPIO_Pin_14 | GPIO_Pin_10| GPIO_Pin_9 | GPIO_Pin_8| GPIO_Pin_7;
		GPIO_ResetBits(GPIOE, pins);
	}
	if(character == 'G')
	{
		// PE14	PE13 PE12 PE11 PE10 PE9  PE8  PE7
		// a 	b 	 c	  d    e 	f 	 g	  .
		// 1 	          1    1 	1		  1
		pins = GPIO_Pin_14 | GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_10 | GPIO_Pin_9 |GPIO_Pin_8|GPIO_Pin_7;
		GPIO_ResetBits(GPIOE, pins);
	}
	if(character == 'H')
	{
		// PE14	PE13 PE12 PE11 PE10 PE9  PE8  PE7
		// a 	b 	 c	  d    e 	f 	 g	  .
		// 1 	          1    1 	1		  1
		pins =  GPIO_Pin_13 |GPIO_Pin_12 | GPIO_Pin_10 | GPIO_Pin_9 | GPIO_Pin_8 | GPIO_Pin_7;
		GPIO_ResetBits(GPIOE, pins);
	}

}

