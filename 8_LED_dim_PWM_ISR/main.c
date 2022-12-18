/*
Name         : Prabhat Kiran
Date         : 11th November 2022
Description  : Implement a LED dimmer application using PWM (Timer ISR Based).
Implement a LED dimmer application using PWM (Timer ISR Based). The brightness of the LED illumination should be based on the User Input tuning the Knob of Potentiometer.
1. On giving power supply to the board, read the value of pot. Based on that value, set the duty cycle. Again read the Pot value.
a. If it is different from previous value, update Duty Cycle accordingly.
b. If it is same do nothing.
2. Repeat the same on regular interval or continuously.
3. Use Timer to generate PWM.
*/

#include <xc.h>
#include "main.h"
#include "adc.h"

#define PERIOD	10

static void init_config (void)
{
	/* Basic configuration of PORTS and Peripherals */
	RB0 = OFF;
	TRISB = 0;
	PORTB = 0x00;
	init_adc();
}
void main(void)
{
	init_config ();
	static unsigned long prog_cycle;
	static unsigned long duty_change;

	while (1)
	{
		duty_change = read_adc(CHANNEL4) / 102.3;			//To Map the value of the ADC (0-1023) to (0-10).

		if (prog_cycle++ < duty_change)						//If the Program cycle value is less than the Duty Cycle, the LED shall be ON (High state of the Waveform).
		{
			RB0 = ON;
		}
		else if (prog_cycle < PERIOD)						//If the Program cycle value is greater than the Duty Cycle and less than PERIOD, the LED shall be OFF (Low state of the Waveform).
		{
			RB0 = OFF;
		}
		else												//If the Waveform is complete, reset the Program cycle.
		{
			prog_cycle= 0;
		}
	}
}
