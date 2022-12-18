/*
Name         : Prabhat Kiran
Date         : 28th November 2022
Description  : Implement a 4-digit Key press Counter with Persistence.
*/

#include <xc.h>
#include "main.h"
#include "ssd_display.h"
#include "ext_eeprom.h"
#include "digital_key.h"
#include "i2c.h"

static unsigned char ssd [MAX_SSD_CNT];
static unsigned char digit [] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

void main(void)
{
	init_i2c();					//To initialize the Basic Configuration for I2C Communication.

	unsigned long i = 0;
	unsigned long j = 3;
	int count = 0;
	int wait = 0;
	int once = 0;
	unsigned char key;
	
	/* Read the Initial value from the External EEPROM  */
	count = ((read_ext_eeprom (0x03)* 1000) + (read_ext_eeprom (0x02)*100) + (read_ext_eeprom (0x01)*10) + (read_ext_eeprom (0x00)));

	while(1)
	{
		display_ssd (count);								//To initialize the 'ssd' array with the value of 'count' mapped to the corresponding MACRO of the SSD.
		key = read_digital_keypad (LEVEL);					//To detect the Key Press.
		init_ssd_control();									//To initialize the Basic Configuration for the SSDs.

		/* If SW2 is pressed, then write the 'count' into External EEPROM */
		if(key == SWITCH2)
		{
			write_ext_eeprom (0x00, count % 10);
			write_ext_eeprom (0x01, (count / 10) % 10);
			write_ext_eeprom (0x02, (count / 100) % 10);
			write_ext_eeprom (0x03, (count / 1000));
		}

		display (ssd);										//To display the 'count' on the SSD.
		
		/* If the SW1 is pressed, then increment the 'count' and if the SW1 is long pressed, then make reset the 'count' to 0 */
		if (key == SWITCH1)
		{
			wait++;											//If the SW1 is pressed, increment the 'wait' to judge if it is a Short Press or Long Press.
			once = 1;										//Set the 'once' to 1 for Short Press of the Key.
		}
		if (key == SWITCH1 && wait > 100)					//If the SW1 is pressed and 'wait' becomes greater than 100; it is a Long Press.
		{
			count = 0;										//Reset the 'count' to 0.
			display_ssd (count);							//To initialize the 'ssd' array with the value of 'count' mapped to the corresponding MACRO of the SSD.
		}
		if (key == 0x0F && once == 1)						//If the SW1 is released and 'once' is set to 1; it is a Short Press.
		{
			once = 0;										//Reset the 'once' to 0 for preventing the entry into this condition next time unless SW1 is pressed.
			if (wait < 100)
			{
				count++;									//In case of a Short Press, increment the 'count' by 1.
				display_ssd (count);						//To initialize the 'ssd' array with the value of 'count' mapped to the corresponding MACRO of the SSD.
			}

			if(count == 9999)								//If the 'count' reaches 9999; reset the 'count' to 0.
				count = 0;
			wait = 0;
		}
		
		display (ssd);										//To display the 'count' on the SSD.
	}
}

/* To initialize the 'ssd' array with the value of 'count' mapped to the corresponding MACRO of the SSD */
void display_ssd (int count)
{
	ssd[3] = digit[(count % 10)];
	ssd[2] = digit[(count / 10) % 10];
	ssd[1] = digit[(count / 100) % 10];
	ssd[0] = digit[(count / 1000) % 10];
}
