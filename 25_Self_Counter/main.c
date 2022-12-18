/*
Name         : Prabhat Kiran
Date         : 22nd November 2022
Description  : Self-Counter using SSDs with storage on Key Press.
1. As soon as the board is powered up or reset, counter should start self incrementing at rate of 1Hz from 0000 up to 9999 and then roll of to 0000 (Approximately, Non Timer Implementation).
2. On save key press, count value should be  stored in internal EEPROM.
3. On subsequent power ups or reset the counter should start from the previous stored value.
*/

#include <xc.h>
#include "main.h"

static unsigned char digit [] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
unsigned char ssd [4] = {ZERO, ZERO, ZERO, ZERO};

static void init_config (void)
{
	/* Basic Configuration */
	ADCON1 = 0x0F;
	TRISD = 0x00;
	TRISA = TRISA & 0xF0;
	TRISC = TRISC | 0x01;
	SSD_CTRL_PORT = SSD_CTRL_PORT | 0x0F;
}

void main()
{
	init_config ();

	unsigned int wait = 1, count;
	unsigned char flag;

	/* Read the Initial value from the EEPROM */
	count = ((read_internal_eeprom (0x03) * 1000) + (read_internal_eeprom (0x02) * 100) + (read_internal_eeprom (0x01) * 10) + (read_internal_eeprom (0x00) * 1));

	while (1)
	{
		flag = key_press ();	//To read the Key press.

		if (flag == 1)			//If the Key is pressed, write the 'count' value into the EEPROM.
		{
			write_internal_eeprom (0x00, (count % 10));
			write_internal_eeprom (0x01, ((count / 10) % 10));
			write_internal_eeprom (0x02, ((count / 100) % 10));
			write_internal_eeprom (0x03, ((count / 1000) % 10));
		}

		if (wait++ == 50)		//To implement the Non-Blocking delay.
		{
			count += 1;			//Increment the 'count' by 1.
			if (count > 9999)	//If the 'count' becomes greater than 4-Digits, reset it to 0.
			{
				count = 0;
				ssd [3] = ssd [2] = ssd [1] = ssd [0] = digit [0];
			}

			wait = 1;			//Reset the 'wait' to 0.
		}

		unsigned int temp = count;
		unsigned char pos = 3;
		while (temp != 0)		//To map the 'count' with the MACRO for the SSD.
		{
			ssd [pos] = digit [temp % 10];
			temp = temp / 10;
			pos -= 1;
		}

		display (ssd);			//Display the value on the SSD.
	}
}
