/*
Name         : Prabhat Kiran
Date         : 10th November 2022
Description  : To perform the operations when an Interrupt is requested.
*/

#include <xc.h>
#include "main.h"
extern unsigned int flag;
extern unsigned int flag2;

void interrupt isr (void)
{
	static unsigned short count;
	static unsigned short sec;
	if (TMR2IF)							//If the Timer2 Overflow Interrupt Flag Bit is set, Timer2 is requesting for an Interrupt.
	{
		if (count++ == 20000)			//The formula for the Timer2 yields the result as: 1 sec for every 20000 ticks.
		{
			if (sec++ == 5)				//If 5 seconds have elapsed, set the 'flag' as 1.
			{
				sec = 0;
				flag = 1;
			}
			count = 0;					//Reset the 'count_3' to 0 for the next cycle.
		}
	}
	TMR2IF = 0;							//To clear the Timer2 Overflow Interrupt Flag Bit to avoid Recursive interrupts.
}
