/*
Name         : Prabhat Kiran
Date         : 8th November 2022
Description  : To return the Key Press.
*/

#include <xc.h>
#include "main.h"

extern unsigned char pos, bias;									//To extend the Scope of Visibility for the Variables from the main.c file.
extern unsigned int wait;

unsigned char key_press (void)
{
	static unsigned char once = 1;								//To implement Edge Trigger detection mechanism for the Switch press.

	if (((KEY_PORT & 0x0F) == SWITCH1) && (once == 1))			//If the SW1 is pressed, the values for the Pattern-1 are Reset.
	{
		once = 0;
		pos = 1;
		wait = 1;
		bias = 8;
		LED_ARRAY = 0x00;
		return 1;
	}
	else if (((KEY_PORT & 0X0F) == SWITCH2) && (once == 1))		//If the SW2 is pressed, the values for the Pattern-2 are Reset.
	{
		once = 0;
		pos = 1;
		wait = 1;
		LED_ARRAY = 0x00;
		return 2;
	}
	else if (((KEY_PORT & 0X0F) == SWITCH3) && (once == 1))		//If the SW3 is pressed, the values for the Pattern-3 are Reset.
	{
		once = 0;
		pos = 1;
		wait = 1;
		LED_ARRAY = 0x00;
		return 3;
	}
	else if (((KEY_PORT & 0X0F) == SWITCH4) && (once == 1))		//If the SW4 is pressed, the values for the Pattern-4 are Reset.
	{
		once = 0;
		pos = 1;
		wait = 1;
		LED_ARRAY = 0x00;
		return 4;
	}
	else														//If the Digital Keypad is not pressed, the value at all the Pins shall be 1.
	{
		once = 1;
		return 0;
	}
}
