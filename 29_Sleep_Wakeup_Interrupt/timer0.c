/*
Name         : Prabhat Kiran
Date         : 4th December 2022
Description  : To configure the Timer0.
*/

#include <xc.h>
#include "timer0.h"

void init_timer0 (void)
{
	/*
	 * Setting instruction cycle clock (Fosc / 4) as the source of
	 * timer0
	 */
	T08BIT = 1;
	T0CS = 0;
	TMR0 = 6;
	PSA = 1;
	/* Clearing timer0 overflow interrupt flag bit */
	TMR0IF = 0;
	/* Enabling timer0 overflow interrupt */
	TMR0IE = 1;
	TMR0ON = 1;
}
