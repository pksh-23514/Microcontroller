/*
Name         : Prabhat Kiran
Date         : 18th November 2022
Description  : To return the Key Press.
 */

#include <xc.h>
#include "digital_keypad.h"

void init_digital_keypad (void)
{
	TRISC = TRISC | INPUT_PINS;									//To make the PORTC as an Input port.
}

unsigned char read_digital_keypad(unsigned char detection_type)
{
	static unsigned char once = 1;								//To implement Edge Trigger detection mechanism for the Switch press.
	if (detection_type == STATE_CHANGE)							//Edge Trigger detection mechanism.
	{
		if (((KEY_PORT & INPUT_PINS) != ALL_RELEASED) && once)	//If the Switch is pressed; the value at the Pin shall be 0.
		{
			once = 0;
			return (KEY_PORT & INPUT_PINS);
		}
		else if ((KEY_PORT & INPUT_PINS) == ALL_RELEASED)		//If the Switch is not pressed, the value at the Pin shall be 1.
		{
			once = 1;
		}
	}
	else if (detection_type == LEVEL)							//Level Trigger detection mechanism.
	{
		return (KEY_PORT & INPUT_PINS);
	}

	return 0x0F;
}
