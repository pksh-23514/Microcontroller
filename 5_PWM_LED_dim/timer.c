/*
Name         : Prabhat Kiran
Date         : 18th November 2022
Description  : To implement the 1 sec Timer.
*/

#include <xc.h>
#include "timer2.h"

void init_timer2 (void)		//Initial values for Timer2 register.
{
	TMR2ON = 1;
	PR2 = 250;
	TMR2IF = 0;
	TMR2IE = 1;
}
