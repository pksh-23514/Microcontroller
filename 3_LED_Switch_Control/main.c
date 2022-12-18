/*
Name         : Prabhat Kiran
Date         : 8th November 2022
Description  : Implement multiple Patterns on LEDs controlled by Switches.
1. Upon giving the power supply, all 8 LEDs should be OFF.
2. Now, press Switch-1 on the Digital Keypad, LEDs should glow according to the Pattern-1.
3. Press Switch-2, LEDs should glow according to the Pattern-2.
4. Press Switch-3, LEDs should glow according to the Pattern-3.
5. Press Switch-4, LEDs should glow according to the Pattern-4.
*Pattern-1: The LEDs should glow from Left to Right and Right to Left.
*Pattern-2: The LEDs should glow from Left to Right and switch off from Left to Right, no direction control/ direction change.
*Pattern-3: The LEDs should blink alternately.
*Pattern-4: The LEDs has to blink nibble wise, i.e first 4 LEDs will be ON, next 4 LEDs will be OFF, after first 4 LEDs will be OFF, next 4 LEDs will be ON.
*/

#include <xc.h>
#include "main.h"

unsigned char pos = 1;		//To store the Direction of the Activity.
unsigned int wait = 1;		//To store the Delay Timer.
unsigned char bias = 8;		//To store the Position of LED for the direction of Right to Left.

static void init_config (void)
{
	ADCON1 = 0X0F;				//To make the pins as Digital I/O.
	TRISB = 0X00;				//To make the PORTB as an Output port.
	LED_ARRAY = 0X00;			//To turn OFF the LEDs when the Power is ON.
	TRISC = TRISC | 0x0F;		//To make the PORTC as an Input port.
}

void main()
{
	init_config ();             //To initialize the ports and registers with the default values.

	unsigned char opt = 1, flag;

	while (1)
	{
		flag = key_press ();	//To read the Digital key Press.

		if (flag != 0)			//If the Key is pressed, the previous Pattern shall be updated with the new Pattern.
		{
			opt = flag;
		}

		if (opt == 1)			//If the SW1 is pressed, the Pattern-1 shall be executed.
		{
			led_train ();
		}
		else if (opt == 2)		//If the SW2 is pressed, the Pattern-2 shall be executed.
		{
			led_L_to_R ();
		}
		else if (opt == 3)		//If the SW3 is pressed, the Pattern-3 shall be executed.
		{
			led_alternate ();
		}
		else if (opt == 4)		//If the SW4 is pressed, the Pattern-4 shall be executed.
		{
			led_nibble ();
		}
	}
}
