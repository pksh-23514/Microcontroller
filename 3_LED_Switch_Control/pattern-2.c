/*
Name         : Prabhat Kiran
Date         : 8th November 2022
Description  : The LEDs should glow from Left to Right and switch off from Left to Right, no direction control/ direction change.
*/

#include <xc.h>
#include "main.h"

extern unsigned char pos, bias;
extern unsigned int wait;

void led_L_to_R (void)
{
	if (wait++ == 50000)								//To implement the Non-Blocking Delay.
	{
		if (pos <= 8)									//The direction is set from Left to Right.
		{
			LED_ARRAY = (1 << pos) - 1;					//The LEDs will be turned ON one by one starting from the LSB side.
		}
		else if (pos <= 16)								//The direction is set from Left to Right.
		{
			LED_ARRAY = LED_ARRAY << 1;					//The LEDs will be turned OFF one by one starting from the LSB side.
		}

		wait = 1;
		pos += 1;

		if (pos > 16)									//If the LEDs have been turned ON and OFF completely, the position shall again start from 1.
			pos = 1;
	}
}
