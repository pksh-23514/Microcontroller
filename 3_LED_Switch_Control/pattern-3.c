/*
Name         : Prabhat Kiran
Date         : 8th November 2022
Description  : The LEDs should blink alternately.
*/

#include <xc.h>
#include "main.h"

extern unsigned char pos;
extern unsigned int wait;

void led_alternate (void)
{
	if (wait++ == 50000)			//To implement the Non-Blocking Delay.
	{
		if (pos == 1)				//The LED pattern shall be: 10101010.
		{
			LED_ARRAY = 0xAA;
		}
		else						//The LED pattern shall be: 01010101.
		{
			LED_ARRAY = 0x55;
		}

		wait = 1;
		pos += 1;
		if (pos > 2)				//If one set of Alternate Blinking is executed, the positions are reset.
			pos = 1;
	}
}
