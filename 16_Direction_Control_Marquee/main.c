/*
Name         : Prabhat Kiran
Date         : 15th November 2022
Description  : Implement a scrolling number Marquee with Direction Control.
1. As soon as the board is powered on or reset, a static message (hardcoded) should start scrolling from right to left SSD.
2. The scroll should repeat indefinitely unless and until the direction change keys are pressed.
3. The scroll frequency should be 0.5Hz (Approximately, Non Timer Based).
4. On press of Right Direction Key, the scroll direction should change from left to right on the same instance.
5. On press of Left Direction Key, the scroll direction should change from right to left on the same instance.
6. On press of Stop / Start Key the scroll should be stopped on the same instance.
7. On press of any key the scroll should start on the same instance.
*/

#include <xc.h>
#include "main.h"

static unsigned char digit [] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, UNDER, UNDER};
unsigned char ssd[4] = {ZERO, ZERO, ZERO, ZERO};

static void init_config (void)
{
	/* Basic Configuration */
	ADCON1 = 0x0F;
	TRISD = 0x00;
	TRISA = TRISA & 0xF0;
	TRISC = TRISC | 0x07;
	SSD_CTRL_PORT = SSD_CTRL_PORT | 0x0F;
}

void main()
{
	unsigned char count = 0, opt = 1, flag, flag_count = 0, prev;
	unsigned int wait1 = 1, wait2 = 1;

	init_config ();

	while (1)
	{
		if (wait1++ == 100)									//To generate the Non-Blocking delay.
		{
			flag = key_press ();							//To store the Key press.
			if (flag == 1 || flag == 2)						//If the SW1 or SW2 is pressed.
			{
				if (flag != opt)							//If the Direction has changed, the 'opt' and 'count' shall be updated.
				{
					if (flag == 2)
						count += 1;
					else
						count -= 1;
				}
				opt = flag;
			}
			if (flag == 3)									//If the SW3 is pressed, the Marquee shall be Started or Stopped.
			{
				flag_count += 1;							//The 'flag_count' shall be incremented.
				if (flag_count % 2 == 1)					//If the 'flag_count' value is Odd, store the Direction of the Marquee in 'prev'.
				{
					prev = opt;
					opt = flag;								//The 'opt' shall be updated to Stop the Marquee.
				}
				else										//If the 'flag_count' value is Even, the previous Direction of the Marquee shall be updated to 'opt'.
				{
					flag_count = 0;							//Reset the 'flag_count'.
					opt = prev;
				}
			}
			wait1 = 1;										//Reset the 'wait'.
		}

		if (wait2++ == 200)									//To implement the Non-Blocking delay.
		{
			if (opt == 1)									//To generate the Left Marquee.
			{
				if (count == 12)
					count = 0;
				ssd [0] = digit [count % 12];
				ssd [1] = digit [(count + 1) % 12];
				ssd [2] = digit [(count + 2) % 12];
				ssd [3] = digit [(count + 3) % 12];

				count += 1;
				wait2 = 1;
			}
			else if (opt == 2)								//To generate the Right Marquee.
			{
				if (count < 3)
					count = 16 - count;
				ssd [3] = digit [count % 12];
				ssd [2] = digit [(count - 1) % 12];
				ssd [1] = digit [(count - 2) % 12];
				ssd [0] = digit [(count - 3) % 12];

				count -= 1;
				wait2 = 1;
			}
			else if (opt == 3)								//To Stop the Marquee.
			{
				wait2 = 1;
			}
		}

		display (ssd);
	}
}
