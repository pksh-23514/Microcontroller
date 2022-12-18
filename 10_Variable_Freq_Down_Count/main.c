/*
Name         : Prabhat Kiran
Date         : 22nd November 2022
Description  : Implement a 4-digit Down Counter with Variable Frequency. The system should count from 9999 to 0000 and then should stop. The count source should be the program cycles.
The frequency of the counting should be varied using a potentiometer. If the potentiometer is tuned to max position the counting should be 10 times faster than the default.
The result would be displayed on SSDs
1. As soon as the board is powered on or reset, it should start decrementing
2. The rate of the count should be based on the current position of the Potentiometer Knob.
3. On clockwise rotation of the Knob, the rate of down count should increase.
4. On anticlockwise rotation of the Knob, the rate of the count should decrease (approximately 10 times slower than the max rate)
5. The counter should stop once it reaches 0.
*/

#include <xc.h>
#include "main.h"
#include "adc.h"
#include "ssd_display.h"

static unsigned char ssd[MAX_SSD_CNT];
static unsigned char digit[] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,BLANK,BLANK,C,DOT};

static void init_config (void)
{
	//Basic Configuration.
	init_adc();
	init_ssd_control();
}
void main(void)
{
	int value=9999,wait=0,a;

	init_config();							//To implement Initial Configuration.

	ssd[3] = digit[9];
	ssd[2] = digit[9];
	ssd[1] = digit[9];
	ssd[0] = digit[9];

	while (1)
	{
		a = read_adc (CHANNEL4)/10.23;	//To read the Potentiometer value from ADC.
		if (wait > a) 					//If the Delay is greater than the ADC value, reset it to 0.
			wait=0;

		if (wait++ == a) 				//Otherwise, display the Counter value on SSD.
		{
			if(value-- == -1)			//If the Counter reaches 0; reset it to 9999.
			{
				value = 9999;
			}

			ssd[3] = digit [value % 10];
			ssd[2] = digit [value % 100 / 10];
			ssd[1] = digit [value % 1000 / 100];
			ssd[0] = digit [value / 1000];
			wait=0;
		}

		display(ssd);
	}
}
