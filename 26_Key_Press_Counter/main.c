/*
Name         : Prabhat Kiran
Date         : 23rd November 2022
Description  : Implement a 4-Digit Key Press Counter with Persistence.
1. As soon as the board is powered up or reset, counter should display 0000 on SSDs.
2. On every key press  counter value should increment by 1.
3. On a  long key press (2 seconds), Count should  reset to zero.
4. On pressing STORE switch, the current count should be  stored in internal EEPROM.
5. On subsequent power ups or reset the counter should start from the previous stored value in the EEPROM.
*/

#include <xc.h>
#include "main.h"

static unsigned char digit [] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
unsigned char ssd [4];

/* Basic Configuration */
static void init_config (void)
{
	ADCON1 = 0x0F;
	TRISD = 0x00;
	TRISA = TRISA & 0xF0;
	TRISC = TRISC | 0x02;
	SSD_CTRL_PORT = SSD_CTRL_PORT | 0x0F;
}

void main()
{
	unsigned char flag, reset;
	static unsigned int count, wait = 0;
	init_config ();

	/* Read the Initial value from the EEPROM */
	count = ((read_internal_eeprom (0x03) * 1000) + (read_internal_eeprom (0x02) * 100) + (read_internal_eeprom (0x01) * 10) + (read_internal_eeprom (0x00) * 1));

	while (1)
	{
		flag = key_press ();										//To read the Key press.
		if (flag == 1)												//If the Key is pressed, count the time for which the Key is pressed.
		{
			wait += 1;
		}
		if ((flag == 1) && (wait > 200))							//If the Key is pressed and the 'wait' value crosses 200; it is a Long press.
		{
			count = 0;												//Reset the 'count' to 0.
			reset = 1;												//Set the 'reset' to 1.
		}
		if ((flag == 0) && (reset == 1))							//If the Key is released and 'reset' is set.
		{
			wait = 0;												//Reset the 'wait' to 0.
			reset = 0;												//Reset the 'reset' to 0.
		}
		if ((flag == 0) && (wait > 20 && wait < 200))				//If the Key is released and the 'wait' value lies between 20 and 200; it is a Short press.
		{
			count += 1;												//Increase the 'count' by 1.
			wait = 0;												//Reset the 'wait' to 0.
		}
		if (flag == 2)												//If the SW2 is pressed, write the 'count' to EEPROM.
		{
			write_internal_eeprom (0x00, (count % 10));
			write_internal_eeprom (0x01, ((count / 10) % 10));
			write_internal_eeprom (0x02, ((count / 100) % 10));
			write_internal_eeprom (0x03, ((count / 1000) % 10));
		}

		/* Display the 'count' on SSD */
		ssd [3] = digit [count % 10];
		ssd [2] = digit [(count / 10) % 10];
		ssd [1] = digit [(count / 100) % 10];
		ssd [0] = digit [(count / 1000) % 10];
		
		display (ssd);
		
		if (count > 9999)											//If the 'count' reaches 9999; reset it to 0.
			count = 0;
	}
}
