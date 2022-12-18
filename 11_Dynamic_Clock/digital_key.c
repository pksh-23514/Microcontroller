/*
Name         : Prabhat Kiran
Date         : 14th November 2022
Description  : Check which Key is Pressed on the Microcontroller.
*/

#include <xc.h>
#include "main.h"

unsigned char key_press (void)
{
	static unsigned char once [4] = {1, 1, 1, 1};			//To implement the Edge-trigger Mechanism for all the 4 Switches.

	if (((KEY_PORT & 0x01) == 0) && (once [0] == 1))		//The Digital Keypad are connected in a Pull Up circuit. So, if the Switch is pressed; the value at the Pin shall be 0.
	{
		once [0] = 0;
		return 1;
	}
	else if (((KEY_PORT & 0x02) == 0) && (once [1] == 1))
	{
		once [1] = 0;
		return 2;
	}
	else if (((KEY_PORT & 0x04) == 0) && (once [2] == 1))
	{
		once [2] = 0;
		return 3;
	}
	else if (((KEY_PORT & 0x08) == 0) && (once [3] == 1))
	{
		once [3] = 0;
		return 4;
	}
	else
	{
		once [0] = once [1] = once [2] = once [3] = 0;
		return 0;
	}
}
