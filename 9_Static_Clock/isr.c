/*
Name         : Prabhat Kiran
Date         : 8th November 2022
Description  : To perform the operations when an Interrupt is requested.
*/

#include <xc.h>
#include "main.h"

extern unsigned char count;

void interrupt isr (void)
{
	static unsigned int timer = 0;
	
	if (TMR0IF == 1)			//If the Timer0 Overflow Interrupt Flag Bit is set, Timer0 is requesting for an Interrupt.
	{
		TMR0 = TMR0 + 8;		//Update the Timer0 register value to maintain the continuity of the count. (TMR0 = TMR0 + 6 + 2 {2 Instruction cycle for the adding operation}).

		if (timer++ == 10000)	//The formula for the Timer0 yields the result as: 0.5 sec for every 10000 ticks.
		{
			timer = 0;
			count += 1;			//Increment the 'count' by 1.
		}

		TMR0IF = 0;				//To clear the Timer0 Overflow Interrupt Flag Bit to avoid Recursive interrupts.
	}
}
