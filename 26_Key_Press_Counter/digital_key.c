/*
Name         : Prabhat Kiran
Date         : 23rd November 2022
Description  : To check for the Digital Key press.
*/

#include <xc.h>
#include "main.h"

unsigned char key_press (void)
{
	if ((KEY_PORT & 0x01) == 0)			//If the SW1 is pressed, the value at the PORT shall be 0.
		return 1;
	else if ((KEY_PORT & 0x02) == 0)	//If the SW2 is pressed, the value at the PORT shall be 0.
		return 2;
	else
		return 0;
}
