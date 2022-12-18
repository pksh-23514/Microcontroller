/*
Name         : Prabhat Kiran
Date         : 25th November 2022
Description  : Implement a Key Detection feedback using UART.
1. On a press of any key from digital keypad, a message has to be sent to host system.
2. The message should be like “Switch X Pressed”, where X could range from 1 to 4.
*/

#include <xc.h>
#include "main.h"
#include "uart.h"

static void init_config (void)
{
	ADCON1 = 0X0F;				//To make the pins as Digital I/O.
	TRISC = TRISC | 0x0F;		//To make the PORTC as an Input port.
	init_uart ();				//To initialize the ports and registers with the default values.
	puts ("Testing...\r");		//Testing of the UART communication.
}

void main()
{
	init_config ();				//To initialize the ports and registers with the default values.

	unsigned char press = 1;	//To implement the Edge Trigger mechanism.
	unsigned int wait = 0;

	while (1)
	{
		if (wait++ == 1000)		//To implement the Non-Blocking Delay for preventing the Bouncing effect.
		{
			wait = 0;

			if (((KEY_PORT & 0x0F) == SWITCH1) && (press == 1))
			{
				press = 0;
				puts ("Switch 1 is pressed\n\r");
			}
			else if (((KEY_PORT & 0X0F) == SWITCH2) && (press == 1))
			{
				press = 0;
				puts ("Switch 2 is pressed\n\r");
			}
			else if (((KEY_PORT & 0X0F) == SWITCH3) && (press == 1))
			{
				press = 0;
				puts ("Switch 3 is pressed\n\r");
			}
			else if (((KEY_PORT & 0X0F) == SWITCH4) && (press == 1))
			{
				press = 0;
				puts ("Switch 4 is pressed\n\r");
			}
			else if ((KEY_PORT & 0x0F) == ALL_RELEASED)
			{
				press = 1;
			}
		}
	}
}
