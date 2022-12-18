/*
Name         : Prabhat Kiran
Date         : 30th November 2022
Description  : To perform the operations when an Interrupt is requested.
*/

#include <xc.h>
#include "main.h"

extern unsigned int flag;			//To extend the Scope of Visibility for the variable from main.c file.

void interrupt isr (void)
{
	static unsigned int count = 0;
	if (TMR2IF)						//If the Timer2 Overflow Interrupt Flag Bit is set, Timer2 is requesting for an Interrupt.
	{
		if (count++ == 200)			//The formula for the Timer2 yields the result as: 0.01 sec for every 200 ticks.
		{
			flag = 1;				//Set the 'flag' as 1.
			count = 0;				//Reset the 'count' as 0.
		}
	}
	TMR2IF = 0;						//To clear the Timer2 Overflow Interrupt Flag Bit to avoid Recursive interrupts.
}
