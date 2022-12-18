/*
Name         : Prabhat Kiran
Date         : 10th November 2022
Description  : Implement a LED dimmer application with Bit Banging PWM. The brightness of the LED illumination should be based on the user input tuning the Knob of potentiometer.
1. On giving power supply to the board, read the value of Pot. Based on that value, set the Duty Cycle. Again read the pot value:
a. If it is different from previous value, update duty cycle accordingly.
b. If it is same do nothing.
2. Repeat the same on regular interval or continuously.
3. Use Program Cycles to generate PWM.
*/

#include <xc.h>
#include "main.h"
#include "adc.h"

#define PERIOD 500

static void init_config (void)
{
	TRISB = 0x00;
	PORTB = 0;
	/* Configure ADC */
	init_adc ();
}
void main()
{
	/* Calling init_config function to configure ADC */
	init_config ();

	unsigned long prog_cycle = 0, duty_cycle;

	while (1)
	{
		duty_cycle = read_adc (CHANNEL4);			//To set the ADC Channel as 4 to read the value from Potentiometer. The ADC value will set the Duty Cycle.

		if (prog_cycle < duty_cycle)				//If the Program cycle value is less than the Duty Cycle, the LED shall be ON (High state of the Waveform).
		{
			RB0 = 1;
			prog_cycle++;							//Increment the Program cycle.
		}
		else if (prog_cycle < PERIOD)				//If the Program cycle value is greater than the Duty Cycle and less than PERIOD, the LED shall be OFF (Low state of the Waveform).
		{
			RB0 = 0;
			prog_cycle++;							//Decrement the Program cycle.
		}
		else										//If the Waveform is complete, reset the Program cycle.
		{
			prog_cycle = 0;
		}
	}
}
