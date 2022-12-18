/*
Name         : Prabhat Kiran
Date         : 30th November 2022
Description  : Implement a LED dimmer application using PWM (Time ISR Based).
1. As soon as the board is powered on or reset, The LED should glow with 0% Duty Cycle (i.e OFF) and the CLCD should print the title message on the first line.
2. The Increment Brightness Input should increase the Duty Cycle upto 100% (Total ON) which should be reflected on the CLCD as progress bar
3. The Decrement Brightness Input should decrease the Duty Cycle to 0% (Total OFF) which should be reflected on the CLCD as progress bar.
*/

#include <xc.h>
#include "main.h"
#include "matrix_keypad.h"
#include"isr.h"
#include"timer2.h"

#define PERIOD			100

unsigned int flag;

static void init_config (void)
{
	/* Basic Configuration */
	ADCON1 = 0x0F;
	RB0 = OFF;
	TRISB = 0;
	PORTB = 0x00;
	init_matrix_keypad();
	init_timer2();
	GIE = 1;
	PEIE = 1;
}

void main(void)
{
	init_config();
	
	while (1)
	{
		unsigned char key;
		static unsigned short wait = 0;
		static unsigned char prog_cycle;
		static unsigned char duty_change = 50;

		key = read_switches(LEVEL_CHANGE);					//To read the Key press.
		if (wait++ == 1000)									//To implement the Non-Blocking Delay.
		{
			wait = 0;
			if (key == 1)									//If SW1 is pressed, Increment the Duty Cycle.
			{
				if (duty_change != PERIOD)
				{
					duty_change++;
				}
			}
			if (key == 4)									//if SW2 is pressed, Decrement the Duty Cycle.
			{
				if (duty_change != 0)
				{
					duty_change--;
				}
			}
		}
		if (flag < duty_change)								//If the 'flag' value is less than Duty Cycle; turn ON the LED.
		{
			RB0 = ON;
		}
		else												//If the 'flag' value is greater than Duty Cycle; turn OFF the LED.
		{
			RB0 = OFF;
		}
		if (flag >= PERIOD)									//If the 'flag' value is equal to PERIOD; reset the 'flag' to 0.
		{
			flag = 0;
		}
	}
}
