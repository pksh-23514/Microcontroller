/*
Name         : Prabhat Kiran
Date         : 10th November 2022
Description  : Implement a Point Brightness control using PWM (Timer ISR Based). The LED should dim to a fixed brightness (say 10% Duty Cycle).
Once the user presses a switch the LED should glow at 100% duty cycle for 5 seconds and then after 5 seconds time out, the LED should dim back to 10% duty cycle.
1. As soon as the board is powered on or reset, LED should glow with half brightness (Duty cycle = 10%).
2. On Interrupt, LED should glow with 100% brightness for 5 seconds.
3. After 5 seconds, the LED should go back to 10% brightness.
*/

#include <xc.h>
#include "main.h"
#include "digital_keypad.h"
#include "timer.h"
#define PERIOD 100

unsigned int flag;

static void init_config (void)
{
	/* Basic Configuration for all the PORTS and other Peripherals */
	ADCON1 = 0x0F;
	RB0 = OFF;
	TRISB = 0;
	init_digital_keypad();
	init_timer2();
	GIE = 1;
	PEIE = 1;
}
void main(void)
{

	unsigned char key;
	unsigned short wait = 0;
	unsigned char prog_cycle;
	unsigned char duty_change = 50;

	init_config ();

	while (1)
	{
		/* Reading SW from Digital Keypad */
		key = read_digital_keypad (STATE_CHANGE);

		if(flag >= 1 || key == SWITCH1)
		{
			if (key == SWITCH1)				//If the SW1 is pressed, then make the Duty Cycle as 100 percent.
			{
				duty_change = PERIOD;
			}
			else
			{
				duty_change = 10;			//Otherwise, make the Duty Cycle as 10 percent.
			}
			flag= 0;
		}

		if (prog_cycle++ < duty_change)		//If the Program cycle value is less than the Duty Cycle, the LED shall be ON (High state of the Waveform).
		{
			RB0 = 1;
		}
		else								//If the Program cycle value is greater than the Duty Cycle and less than PERIOD, the LED shall be OFF (Low state of the Waveform).
		{
			RB0 = 0;
		}

		if (prog_cycle >= PERIOD)			//If the Program Cycle becomes greater than PERIOD, reset it to 0.
		{
			prog_cycle = 0;
		}
	}
}
