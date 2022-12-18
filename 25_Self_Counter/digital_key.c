/*
Name         : Prabhat Kiran
Date         : 22nd November 2022
Description  : To check for the Digital Key press.
*/

#include <xc.h>
#include "main.h"

unsigned char key_press (void)
{
	if ((KEY_PORT & 0x01) == 0)		//If the SW1 is pressed, the value at the PORT shall be 0.
		return 1;
	else
		return 0;
}
