/*
Name         : Prabhat Kiran
Date         : 10th November 2022
Description  : To configure the TIMER2.
*/

#include <xc.h>
#include "timer.h"

void init_timer2 (void)
{
	/* Basic configuration for Timer2 */
	TMR2ON = 1;
	PR2 = 250;
	TMR2IF = 0;
	TMR2IE = 1;
}
