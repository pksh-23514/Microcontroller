/*
Name         : Prabhat Kiran
Date         : 21st November 2022
Description  : Implement a Temperature Sensor (LM35) node with SSD display.
As soon as the board is powered ON or Reset, room temperature is displayed on SSD with unit.
*/

#include "main.h"
#include "adc.h"
#include <xc.h>
#include "ssd_display.h"

unsigned char ssd [MAX_SSD_CNT];
unsigned char digit [] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, C};

static void init_config (void)
{
	TRISB0 = 0;
	init_adc();
	init_ssd_control();
}
void main()
{
	unsigned short adc_reg_val;
	
	init_config ();				//To configure the Initial Configuration.

	unsigned int val;

	while (1)
	{
		adc_reg_val = read_adc (CHANNEL6);		//To read the ADC value which is the Sampled value of Temperature sensor.

		val = (adc_reg_val*500) / 1024;			//To convert the value into Degree Celsius.
		
		ssd[3] = ssd[3] | 0xC6;
		ssd[2] = ssd[2] | 0x10;
		ssd[1] = digit[(val % 10)];
		ssd[0] = digit[(val / 10) % 10];
		
		display (ssd);							//To display the value on SSD.
	}
}
