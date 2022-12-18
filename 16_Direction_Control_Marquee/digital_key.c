/*
Name         : Prabhat Kiran
Date         : 16th November 2022
Description  : To detect the Key press.
*/

#include <xc.h>
#include "main.h"

unsigned char key_press (void)
{
	static unsigned char left = 1, right = 1, stop = 1, start = 1;			//To implement Edge-trigger Mechanism for all the 3 Switches.

	if (((KEY_PORT & 0x01) == 0) && (left == 1) && (start == 1))			//If SW1 is pressed, the direction of Marquee shall be Left.
	{
		left = 0;
		return 1;
	}
	else if (((KEY_PORT & 0x02) == 0) && (right == 1) && (start == 1))		//If SW2 is pressed, the direction of Marquee shall be Right.
	{
		right = 0;
		return 2;
	}
	else if (((KEY_PORT & 0x04) == 0) && (stop == 1))						//If SW3 is pressed, the Marquee shall Start or Stop.
	{
		stop = 0;
		start = !start;
		return 3;
	}
	else
	{
		left = 1;
		right = 1;
		stop = 1;
		return 0;
	}
}
