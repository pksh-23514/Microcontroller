/*
Name         : Prabhat Kiran
Date         : 7th November 2022
Description  : Implement LED train pattern on LEDs.
1. Consider 8 LEDs from the Board, these LEDs has to glow one by one as if a train is coming out of a tunnel every second (approximately without timer implementation) from Left to Right 
2. The above pattern shall be executed as soon as the board is powered on or reset (Let’s call it as exit).
3. Once all LEDs are ON, the LEDs should switch OFF one by one as if the train is entering inside a tunnel from Left to Right (Let’s call it as entry).
4. Once the exit and entry is complete , change the direction of the train from Right to Left.
5. This process of changing direction has to be repeated between every exit and entry of the train.
*/

#include <xc.h>
#include "main.h"

static void init_config (void)
{
	ADCON1 = 0x0F;				//To make the pins as Digital I/O.
	TRISB = 0x00;				//To make the PORTB as an Output port.
}

void led_train (void)
{
	inti_config ();				//To initialize the ports and registers with the default values.

	unsigned char pos = 1;		//To store the Direction of the Activity.
	unsigned int wait = 1;		//To store the Delay Timer.
	unsigned char bias = 8;		//To store the Position of LED for the direction of Right to Left.

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
