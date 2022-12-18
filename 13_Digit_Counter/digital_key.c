/*
Name         : Prabhat Kiran
Date         : 14th November 2022
Description  : Check which Key is Pressed on the Microcontroller.
*/

#include <xc.h>
#include "main.h"

unsigned char key_press (void)
{
	if ((KEY_PORT & 0x01) == 0)		//The Digital Keypad are connected in a Pull Up circuit. So, if the Switch is pressed; the value at the Pin shall be 0.
		return 1;
	else
		return 0;
}
