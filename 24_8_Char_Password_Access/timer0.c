/*
Name         : Prabhat Kiran
Date         : 25th November 2022
Description  : To configure the Timer0.
*/

#include <xc.h>
#include "timer0.h"

void init_timer0 (void)
{
	/* Basic Configuration for Timer0 */
	TMR2ON = 1;
	PR2 = 250;
	TMR2IF = 0;
	TMR2IE = 1;
}
