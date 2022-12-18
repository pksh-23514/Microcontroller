/*
Name         : Prabhat Kiran
Date         : 14th November 2022
Description  : Implement a Left Scrolling number Marquee.
1. As soon as the board is powered up or reset, a static message (hardcoded) should start scrolling from right to left on SSD.
2. The Scroll should repeat indefinitely.
3. The Scroll Frequency should be 0.5Hz (Approximately, Non Timer Based).
*/

#include <xc.h>
#include "main.h"

static unsigned char digit [] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, UNDER, UNDER};
unsigned char ssd [] = {ZERO, ONE, TWO, THREE};

static void init_config (void)
{
	/* Basic Configuration */
	ADCON1 = 0x0F;
	TRISD = 0x00;
	TRISA = TRISA & 0xF0;
	SSD_CTRL_PORT = SSD_CTRL_PORT | 0x0F;
}

void main()
{
	unsigned char count = 1;
	unsigned int wait = 1;
	init_config ();

	while (1)
	{
		if (wait++ == 200)							//To keep the Scroll frequency as 0.5 Hz (approximately).
		{
			ssd [0] = digit [count % 12];
			ssd [1] = digit [(count + 1) % 12];
			ssd [2] = digit [(count + 2) % 12];
			ssd [3] = digit [(count + 3) % 12];
			
			count += 1;								//Increment the 'count' by 1.
			wait = 1;
		}
			display (ssd);
	}
}
