/*
Name         : Prabhat Kiran
Date         : 8th November 2022
Description  : Implement Pattern Generator on LEDs controlled by Switches.
1. There are 8 LEDs on the Board, these LEDs has to glow one by one as if a train bogie coming out of a tunnel every second from Left to Right as soon as the board is powered on or reset.
2. Once all LEDS are ON, the LEDs  should switch OFF one by one as if the train bogie is entering inside a tunnel from Left to Right (Let’s call it as entry).
3. The direction of train would remain as is unless and until the DCI (Direction Change Input) is detected.
4. On Direction Change Input, The Train direction should change instantly to opposite and remains same until the next Direction Change Input.
*/

#include <xc.h>
#include "main.h"

static void init_config (void)
{
	ADCON1 = 0X0F;				//To make the pins as Digital I/O.
	TRISB = 0X00;				//To make the PORTB as an Output port.
	LED_ARRAY = 0X00;			//To turn OFF the LEDs when the Power is ON.
	TRISC = TRISC | 0x01;		//To make the PORTC as an Input port.
}

void main()
{
	init_config ();						//To initialize the ports and registers with the default values.

	unsigned int wait = 1;
	unsigned char flag, count = 1;

	while (1)
	{
		if (wait++ == 200)				//To implement the Non-Blocking Delay for preventing the Bouncing effect.
		{
			flag = key_press ();		//To read the Digital key Press.
			wait = 1;					//Reset the 'wait' for the next Press.
			if (flag == 1)				//If the Digital key is pressed, count the Number of Press.
			{
				count += 1;
				if (count == 2)			//If the Press is second time, the original direction of Pattern is restored.
					count = 0;			//Update the 'count' to 0.
			}
		}

		led_train (count);				//The LED pattern generate function is called as per the Key press.
	}
}
