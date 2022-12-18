/*
Name         : Prabhat Kiran
Date         : 9th November 2022
Description  : To configure the SSD display for displaying Data.
*/

#include <xc.h>
#include "main.h"

void display (unsigned char data [])
{
	unsigned int wait;
	unsigned char digit;

	for (digit = 0; digit < 4; digit++)								//The loop shall run 4 times for displaying the Data in the 4 SSDs.
	{
		SSD_DATA_PORT = data [digit];								//To control the LEDs on the SSD for displaying the particular digit.
		SSD_CTRL_PORT = (SSD_CTRL_PORT & 0xF0) | (0x01 << digit);	//To control the SSD to be switched ON.

		for (wait = 1000; wait--; );								//Small Delay to make the display without flickering.
	}
}
