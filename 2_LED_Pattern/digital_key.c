/*
Name         : Prabhat Kiran
Date         : 8th November 2022
Description  : To return the Key Press.
*/

#include <xc.h>
#include "main.h"

unsigned char key_press (void)
{
	static unsigned char once = 1;					//To implement Edge Trigger detection mechanism for the Switch press.

	if (((KEY_PORT & 0x01) == 0) && (once == 1))	//The Digital Keypad are connected in a Pull Up circuit. So, if the Switch is pressed; the value at the Pin shall be 0.
	{
		once = 0;									//To prevent the Key press from being detected more than once.
		return 1;
	}
	else											//If the Digital Keypad is not pressed, the value at Pin shall be 1.
	{
		once = 1;
		return 0;
	}
}
