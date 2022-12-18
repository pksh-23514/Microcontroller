/*
Name         : Prabhat Kiran
Date         : 18th November 2022
Description  : Using Timer based PWM, implement a LED dimmer application.
1. As soon as the board is powered on or reset, The LED should glow with 50% Duty Cycle (i.e the glow, half of its maximum intensity).
2. The Increment Brightness Input should increase the Duty Cycle upto 100% (Total ON).
3. The Decrement Brightness Input should decrease the Duty Cycle to 0% (Total OFF).
*/

#include <xc.h>
#include "main.h"
#include "digital_keypad.h"
#include"timer2.h"

#define PERIOD	100
unsigned int flag;

static void init_config(void)
{
	ADCON1 = 0x0F;			//To make the pins as Digital I/O.
	RB0 = OFF;				//LED0 is OFF initially.
	TRISB = 0;				//To make the PORTB as an Output port.
	PORTB = 0x00;			//To turn OFF the LEDs initially.
	init_digital_keypad();	//To initialize the ports and registers with the default values.
	init_timer2();			//To initialize the ports and registers with the default values.
	GIE = 1;				//To set the Global Interrupt Enable bit.
	PEIE = 1;				//To set the Peripheral Interrupt Enable bit.
}
void main(void)
{
	init_config();									//To initialize the ports and registers with the default values.
	
	while (1)
	{
		unsigned char key;
		static unsigned short wait = 0;
		static unsigned char prog_cycle;
		static unsigned char duty_change = 50;
		
		key = read_digital_keypad (LEVEL);			//To read the Digital key Press.

		if (wait++ == 1000)							//To implement the Non-Blocking Delay for preventing the Bouncing effect.
		{
			wait = 0;
			if (key == SWITCH1)						//If SW1 is pressed, then check if Duty Cycle is not equal to PERIOD (maximum value) and increment it.
			{
				if (duty_change != PERIOD)
				{
					duty_change++;					//Increment the Duty Cycle.
				}
			}
			if (key == SWITCH2)						//If SW2 is pressed, then check if Duty Cycle is not equal to 0 (minimum value) and decrement it.
			{
				if (duty_change != 0)
				{
					duty_change--;					//Decrement the Duty Cycle.
				}
			}
		}

		if (flag < duty_change)						//Keep the LED in ON state till the waveform is HIGH (i.e. till the Duty Cycle)
		{
			RB0 = ON;
		}
		else										//Keep the LED in OFF state till the waveform is LOW (i.e. till the (PERIOD - Duty Cycle)).
		{
			RB0 = OFF;
		}
		if (flag >= PERIOD)							//If the 'flag' completes one waveform, reset it to 0 for the next waveform.
		{
			flag = 0;
		}
	}
}
