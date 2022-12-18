/*
Name         : Prabhat Kiran
Date         : 30th November 2022
Description  : To implement UART Communication between the Microcontroller Board and Laptop.
*/

#include <xc.h>
#include "uart.h"

void init_uart (void)
{
	/* Serial initialization */
	RX_PIN = 1;
	TX_PIN = 0;

	BRGH = 1;
	SPEN = 1;
	CREN = 1;

	/* Set to 10 for 115200, 64 for 19200 and 129 for 9600 */
	SPBRG = 129;

	RCIE = 1;
}

void putch (unsigned char byte) 
{
	/* Output one byte */
	/* Set when register is empty */
	while (!TXIF)
	{
		continue;
	}

	TXREG = byte;
}

int puts (const char *s)
{
	while (*s)		
	{
		putch (*s++);	
	}

	return 0;
}

unsigned char getch (void)
{
	/* Retrieve one byte */
	/* Set when register is not empty */
	while (!RCIF)
	{
		continue;
	}

	return RCREG;
}

unsigned char getche (void)
{
	unsigned char c;

	putch (c = getch());

	return (c);
}
