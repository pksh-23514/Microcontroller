/*
Name         : Prabhat Kiran
Date         : 4th December 2022
Description  : To perform the operations when an Interrupt is requested.
*/

#include <xc.h>
#include "isr.h"

bit key_detected;
extern int a = 0;

void interrupt isr (void)
{
	if (INT0F == 1) 						//To check the External Interrupt.
	{
		key_detected = 1;					//Set the 'key_detected'.

		INT0F = 0;							//To clear the External Interrupt Flag Bit to avoid Recursive interrupts.
	}
	static unsigned short count2;
	if (TMR0IF) 							//If the Timer0 Overflow Interrupt Flag Bit is set, Timer0 is requesting for an Interrupt.
	{
		TMR0 = TMR0 + 8;
		if (count2++ == 20000) 				//The formula for the Timer0 yields the result as: 1 sec for every 20000 ticks.
		{
			count2 = 0;
			if (a < 5) 						//To blink the LED for 5 times (toggle).
			{
				RB6=!RB6;
			}
			a++;
		}
		TMR0IF = 0;							//To clear the Timer0 Overflow Interrupt Flag Bit to avoid Recursive interrupts.
	}
}
