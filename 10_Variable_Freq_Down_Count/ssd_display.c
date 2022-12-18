/*
Name         : Prabhat Kiran
Date         : 22nd November 2022
Description  : To configure the SSD display for displaying Data.
*/

#include <xc.h>
#include "ssd_display.h"

void init_ssd_control (void)
{
	/* Setting PORTB as output for Data Lines */
	TRISD = 0x00;
	/* Setting SSD Enable lines as output */
	TRISA = TRISA & 0xF0;

	/* Switching OFF all the SSDs to start with */
	SSD_CNT_PORT = SSD_CNT_PORT & 0xF0;
}

/* Better if implemented in timer handler */
void display (unsigned char data[])
{
	unsigned int wait;
	unsigned char data_bit;
	unsigned char digit;

	for (digit = 0; digit < MAX_SSD_CNT; digit++)					//The loop shall run 4 times for displaying the Data in the 4 SSDs.
	{
		SSD_DATA_PORT = data [digit];								//To control the LEDs on the SSD for displaying the particular digit.
		SSD_CNT_PORT = (SSD_CNT_PORT & 0xF0) | (0x01 << digit);		//To control the SSD to be switched ON.
		for (wait = 1000; wait--; );								//Small Delay to make the display without flickering.
	}
}
