/*
Name         : Prabhat Kiran
Date         : 27th November 2022
Description  : Implement a Temperature Sensor node with CLCD display.
1. As soon as the board is powered up or reset, CLCD display the title in the first line.
2. In second line, room temperature is displayed with unit .
*/

#include "main.h"
#include "adc.h"
#include <xc.h>
#include "clcd.h"

/* Basic Configurations */
static void init_config (void)
{
	TRISB0 = 0;
	init_adc();
	init_clcd();
}
void main()
{
	unsigned short adc_reg_val;
	init_config();
	unsigned int val;

	while (1)
	{
		adc_reg_val = read_adc (CHANNEL6);				//CHANNEL-6 is interfacing of ADC with the Temperature Sensor.
		val = (adc_reg_val * 500) / 1024;				//To convert the ADC value into Degree Celsius.

		/* Print the value on CLCD */
		clcd_print("LM35 Temp Sensor",LINE1(0));
		clcd_print("Temperature  ",LINE2(0));
		clcd_putch(((val / 10)% 10)+ '0',LINE2(12));
		clcd_putch((val % 10) + '0',LINE2(13));
		clcd_print(".C",LINE2(14));
	}
}
