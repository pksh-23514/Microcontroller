/*
Name         : Prabhat Kiran
Date         : 25th November 2022
Description  : Implement a Message Display using UART and CLCD.
1. Any message typed on the host system should be shown in a CLCD.
2. On completion of the first line it should start on the second line.
3. One full screen the second line should be moved to first line.
*/

#include <xc.h>
#include "uart.h"
#include "clcd.h"

/* Basic Configuration */
static void init_config ()
{
	init_clcd ();
	init_uart ();
}

void main()
{
	init_config ();

	unsigned char flag = 1, ch, i = 0, line_1 [17], line_2 [17] = "                ";

	while (1)
	{
		ch = getche ();										//To transmit back the Character from Controller to Laptop which is received from the Laptop.

		if ((i < 16) && (flag == 1))						//Initially the Characters typed on the Laptop will be displayed on the LINE-1 of the CLCD.
		{
			clcd_putch (ch, LINE1(i));						//To display the Character on the LINE-1 of the CLCD at position 'i'.
			i += 1;											//Increment the 'i' for printing the Next Character at the Next position of the CLCD.

			if (i == 16)									//If the value of 'i' reaches 16; LINE-1 of the CLCD is completely filled with Characters.
			{
				i = 0;										//Reset the 'i' to 0.
				flag = 2;									//The Next Character received shall be displayed on the LINE-2.
			}
		}
		else if ((i < 16) && (flag == 2))					//After the LINE-1 is full, the Characters shall be displayed on the LINE-2.
		{
			line_1 [i] = ch;								//Start storing the Characters displayed on the LINE-2 of the CLCD in the 'line_1' array.
			clcd_putch (ch, LINE2(i));						//To display the Character on the LINE-2 of the CLCD at position 'i'.
			i += 1;											//Increment the 'i' for printing the Next Character at the Next position of the CLCD.

			if (i == 16)									//If the value of 'i' reaches 16; LINE-2 of the CLCD is completely filled with Characters.
			{
				i = 0;										//Reset the 'i' to 0.
				clcd_print (line_1, LINE1(0));				//Shift all the Characters of LINE-2 to LINE-1 by displaying the 'line_1' on LINE-1 of the CLCD.
				clcd_print (line_2, LINE2(0));				//Clear the LINE-2 for the next Character received to be printed on the CLCD.
			}
		}
	}
}
