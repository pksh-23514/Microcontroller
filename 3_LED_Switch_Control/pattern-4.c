/*
Name         : Prabhat Kiran
Date         : 8th November 2022
Description  : The LEDs has to blink Nibble-wise.
*/

#include <xc.h>
#include "main.h"

extern unsigned char pos;
extern unsigned int wait;

void led_nibble (void)
{
	if (wait++ == 50000)			//To implement the Non-Blocking Delay.
	{
		if (pos == 1)				//The LED pattern shall be: 00001111.
		{
			LED_ARRAY = 0x0F;
		}
		else						//The LED pattern shall be: 11110000.
		{
			LED_ARRAY = 0XF0;
		}

		wait = 1;
		pos += 1;
		if (pos > 2)				//If one set of Nibble Blinking is executed, the positions are reset.
			pos = 1;
	}
}
