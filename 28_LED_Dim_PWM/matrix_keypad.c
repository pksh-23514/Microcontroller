/*
Name         : Prabhat Kiran
Date         : 30th November 2022
Description  : To detect the Key Press.
*/

#include <xc.h>
#include "matrix_keypad.h"

void init_matrix_keypad (void)
{
	/* Config PORTB as digital */
	ADCON1 = 0x0F;

	/* Set Rows (RB7 - RB5) as Outputs and Columns (RB4 - RB1) as Inputs */
	TRISB = 0x1E;

	/* Set PORTB input as pull up for columns */
	RBPU = 0;

	MATRIX_KEYPAD_PORT = MATRIX_KEYPAD_PORT | 0xE0;
}

unsigned char scan_key (void)
{
	ROW1 = LO;						//Set the ROW1 as LOW.
	ROW2 = HI;						//Set the ROW2 as HIGH.
	ROW3 = HI;						//Set the ROW3 as HIGH.

	if (COL1 == LO)					//If SW1 is pressed.
	{
		return 1;
	}
	else if (COL2 == LO)			//If SW4 is pressed.
	{
		return 4;
	}
	else if (COL2 == LO)			//If SW7 is pressed.
	{
		return 7;
	}

	return 0xFF;					//If no SW on the Matrix Keypad is pressed.
}

unsigned char read_switches (unsigned char detection_type)
{
	static unsigned char once = 1, key;

	if (detection_type == STATE_CHANGE)				//If it Edge-trigger detection mechanism.
	{
		key = scan_key ();
		if (key != 0xFF && once)					//If any Key is pressed and it is detected for the first time.
		{
			once = 0;								//Reset 'once' to 0.
			return key;								//Return the Key press.
		}
		else if (key == 0xFF)						//If no SW on the Matrix Keypad is pressed.
		{
			once = 1;								//Set 'once' to 1.
		}
	}
	else if (detection_type == LEVEL_CHANGE)		//If it is Level-trigger mechanism.
	{
		return scan_key ();							//Return the Key press.
	}

	return 0xFF;									//If no SW on the Matrix Keypad is pressed.
}
