/*
Name         : Prabhat Kiran
Date         : 8th November 2022
Description  : To generate the LED Pattern.
*/

#include <xc.h>
#include "main.h"

void led_train (unsigned char press)
{
	static unsigned int count = 0, wait = 1;
	static unsigned char flag = 0;

	if (wait++ == 50000)											//To implement the Non-Blocking Delay.
	{
		if (press % 2 == 1)											//If the Press is once, the Direction is Left to Right.
		{
			if ((count < 8) && (flag == 0))							//The LED pattern to turn ON one by one from Left to Right.
			{
				LED_ARRAY = LED_ARRAY | (1 << count);				//The LEDs will be turned ON one by one starting from the LSB side.

				if (LED_ARRAY == 0xFF)								//If all the LEDs are turned ON, the pattern shall change.
					flag = 1;
				count += 1;											//To turn on the particular set of LEDs.
				wait = 1;
			}

			if ((flag == 1) && (count > 0))							//The LED pattern to turn OFF one by one from Left to Right.
			{
				LED_ARRAY = LED_ARRAY << 1;							//The LEDs will be turned OFF one by one starting from the LSB side.

				if (LED_ARRAY == 0x00)								//If all the LEDs are turned OFF, the pattern shall change.
					flag = 0;
				count -= 1;											//To turn off the particular set of LEDs.
				wait = 1;
			}
		}
		else
		{
			if ((count < 8) && (flag == 1))							//The LED pattern to turn ON one by one from Right to Left.
			{
				LED_ARRAY = LED_ARRAY | (1 << (7 - count));			//The LEDs will be turned ON one by one starting from the MSB side.

				if (LED_ARRAY == 0xFF)								//If all the LEDs are turned ON, the pattern shall change.
					flag = 0;
				count += 1;											//To turn on the particular set of LEDs.
				wait = 1;
			}

			if ((flag == 0) && (count > 0))							//The LED pattern to turn OFF one by one from Right to Left.
			{
				LED_ARRAY = LED_ARRAY >> 1;							//The LEDs will be turned OFF one by one starting from the MSB side.

				if (LED_ARRAY == 0x00)								//If all the LEDs are turned OFF, the pattern shall change.
					flag = 1;
				count -= 1;											//To turn off the particular set of LEDs.
				wait = 1;
			}
		}
	}
}
