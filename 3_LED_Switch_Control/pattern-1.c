/*
Name         : Prabhat Kiran
Date         : 8th November 2022
Description  : The LEDs should glow from Left to Right and Right to Left.
*/

#include <xc.h>
#include "main.h"

extern unsigned char pos, bias;
extern unsigned int wait;

void led_train (void)
{
	if (wait++ == 50000)								//To implement the Non-Blocking Delay.
	{
		if (pos <= 8)									//The direction is set from Left to Right.
		{
			LED_ARRAY = (1 << pos) - 1;					//The LEDs will be turned ON one by one starting from the LSB side.
		}
		else if (pos <= 16)								//The direction is set from Left to Right.
		{
			LED_ARRAY = LED_ARRAY << 1;					//The LEDs will be turned OFF one by one starting from the LSB side.
		}
		else if (pos <= 24)								//The direction is set from Right to Left.
		{
			LED_ARRAY = LED_ARRAY | (1 << (bias - 1));	//The LEDs will be turned ON one by one starting from the MSB side.
		}
		else if (pos <= 32)								//The direction is set from Right to Left.
		{
			LED_ARRAY = LED_ARRAY >> 1;					//The LEDs will be turned OFF one by one starting from the MSB side.
		}
		
		wait = 1;						//Update the Delay Timer back to '1' for the next iteration.
		pos += 1;
		
		if (pos == 17)					//If the LEDs have been turned ON and OFF in Left to Right manner, make the LED states back to default.
			LED_ARRAY = 0;
		
		if (pos > 17 && pos <= 25)		//If the Direction is changed to Right to Left.
		{
			bias -= 1;					//The 'bias' shall be updated for turning on the LEDs one by one.
			if (bias < 1)				//If the 'bias' becomes less than '1'; it shall be restored to it's default value.
				bias = 8;
		}
		if (pos > 32)					//If the 'pos' becomes more than '32'; it shall be restored to it's default value.
			pos = 1;
	}
}
