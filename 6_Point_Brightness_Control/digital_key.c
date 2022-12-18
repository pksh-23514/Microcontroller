/*
Name         : Prabhat Kiran
Date         : 10th November 2022
Description  : To return the Key Press.
*/

#include <xc.h>
#include "digital_keypad.h"

void init_digital_keypad (void)
{
	TRISC = TRISC | INPUT_PINS;										//The PORTC shall be configured as an Input Port.
}

unsigned char read_digital_keypad (unsigned char detection_type)
{
	static unsigned char once = 1;									//To implement Edge-trigger mechanism.

	if (detection_type == STATE_CHANGE)								//Condition for Edge-trigger mechanism.
	{
		if (((KEY_PORT & INPUT_PINS) != ALL_RELEASED) && once)		//If the Key is pressed, the value at the Pin shall be 0.
		{
			once = 0;

			return (KEY_PORT & INPUT_PINS);							//Return the Key press.
		}
		else if ((KEY_PORT & INPUT_PINS) == ALL_RELEASED)			//If the Key is released, the value at the Pin shall be 1 due to the nature of Pull-Up circuit.
		{
			once = 1;
		}
	}
	else if (detection_type == LEVEL)								//Condition for Level-trigger mechanism.
	{
		return (KEY_PORT & INPUT_PINS);
	}

	return 0x0F;													//Return 0xFF if no Key is pressed.
}
