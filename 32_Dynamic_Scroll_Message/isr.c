/*
Name         : Prabhat Kiran
Date         : 30th November 2022
Description  : To perform the operations when an Interrupt is requested.
*/

#include <xc.h>

extern unsigned char ch;

void interrupt isr (void)
{
	if (RCIF == 1)			//If the Receive Interrupt Flag is set.
	{
		if (OERR == 1)		//If the Overrun Error is set, clear the OERR bit.
			OERR = 0;

		ch = RCREG;			//Read the Data from the Receive Buffer Register.

		RCIF = 0;			//To clear the Received Interrupt Flag Bit to avoid Recursive interrupts.
	}
}
