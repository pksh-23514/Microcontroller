/*
Name         : Prabhat Kiran
Date         : 30th November 2022
Description  : To configure the Timer2.
*/

#include <xc.h>
#include "timer2.h"

void init_timer2 (void)
{
	/* Configuration for Timer 2 */
	TMR2ON = 1;
	PR2 = 250;
	TMR2IF = 0;
	TMR2IE = 1;
}
