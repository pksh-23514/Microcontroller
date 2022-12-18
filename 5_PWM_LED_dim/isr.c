/*
Name         : Prabhat Kiran
Date         : 18th November 2022
Description  : To perform the operations when an Interrupt is requested.
*/

#include <xc.h>
#include "main.h"

extern unsigned int flag;	//To extend the Scope of Visibility for the variable from the main.c file.

void interrupt isr (void)
{
	if (TMR2IF)				//If the Timer2 Overflow Interrupt Flag Bit is set, Timer2 is requesting for an Interrupt.
	{
		flag++;				//Increment the 'flag'.
		TMR2IF = 0;			//To clear the Timer2 Overflow Interrupt Flag Bit to avoid Recursive interrupts.
	}
}
