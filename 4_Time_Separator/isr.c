/*
Name         : Prabhat Kiran
Date         : 15th November 2022
Description  : To perform the operations when an Interrupt is requested.
*/

#include <xc.h>
#include "main.h"

void interrupt isr (void)
{
	static unsigned int count_1 = 0, count_2 = 0, count_3 = 0;

	if (TMR0IF == 1)					//If the Timer0 Overflow Interrupt Flag Bit is set, Timer0 is requesting for an Interrupt.
	{
		TMR0 = TMR0 + 8;				//Update the Timer0 register value to maintain the continuity of the count. (TMR0 = TMR0 + 6 + 2 {2 Instruction cycle for the adding operation}).
		if (count_1++ == 20000)			//The formula for the Timer0 yields the result as: 1 sec for every 20000 ticks.
		{
			count_1 = 0;				//Reset the 'count_1' to 0 for the next cycle.
			LED1 = !LED1;				//Toggle the LED.
		}
		TMR0IF = 0;						//To clear the Timer0 Overflow Interrupt Flag Bit to avoid Recursive interrupts.
	}

	if (TMR1IF == 1)					//If the Timer1 Overflow Interrupt Flag Bit is set, Timer1 is requesting for an Interrupt.
	{
		TMR1 = TMR1 + 3038;				//Update the Timer1 register value to maintain the continuity of the count. (TMR1 = TMR1 + 3036 + 2 {2 Instruction cycle for the adding operation}).
		if (count_2++ == 80)			//The formula for the Timer1 yields the result as: 1 sec for every 80 ticks.
		{
			count_2 = 0;				//Reset the 'count_2' to 0 for the next cycle.
			LED2 = !LED2;				//Toggle the LED.
		}
		TMR1IF = 0;						//To clear the Timer1 Overflow Interrupt Flag Bit to avoid Recursive interrupts.
	}

	if (TMR2IF == 1)					//If the Timer2 Overflow Interrupt Flag Bit is set, Timer2 is requesting for an Interrupt.
	{
		if (count_3++ == 20000)			//The formula for the Timer2 yields the result as: 1 sec for every 20000 ticks.
		{
			count_3 = 0;				//Reset the 'count_3' to 0 for the next cycle.
			LED3 = !LED3;				//Toggle the LED.
		}
		TMR2IF = 0;						//To clear the Timer2 Overflow Interrupt Flag Bit to avoid Recursive interrupts.
	}
}
