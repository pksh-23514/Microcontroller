/*
Name         : Prabhat Kiran
Date         : 30th November 2022
Description  : To perform the operations when an Interrupt is requested.
*/

#include <xc.h>
#include "main.h"

extern unsigned int flag;

void interrupt isr (void)
{
	if (TMR2IF)				//If the Timer2 Overflow Interrupt Flag Bit is set, Timer2 is requesting for an Interrupt.
	{
		flag++;				//Increment the 'flag'.
		TMR2IF = 0;			//To clear the Timer2 Overflow Interrupt Flag Bit to avoid Recursive interrupts.
	}
}
