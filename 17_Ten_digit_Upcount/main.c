/*
Name         : Prabhat Kiran
Date         : 12th November 2022
Description  : Implement a 10-Digit UP-Counter.
1. As soon as the board is powered up or reset, CLCD display the title (Up Counter) on the first line.  
2. On second line, 0000000000 (10 digit number) starts incrementing. 
3. Increment happens at constant rate (You may have lesser delay as possible since it's a 10 digit counter). 
4. The counter stops after reaching count value of 9999999999 
*/

#include <xc.h>
#include "clcd.h"

static void init_config (void)
{
	/* Basic Configuration */
	init_clcd ();

}

void main()
{
	init_config ();

	char str [] = "0000000000";						//Initial value of the Counter.
	long i = 0;
	char temp;
	int wait;
	int count = 0;

	while (1)
	{
		clcd_print ("UP COUNTER", LINE1(3));					//To print the String on LINE-1 of the CLCD from position 3.
		clcd_print ("COUNT:", LINE2(0));					//To print the String on LINE-2 of the CLCD from position 0.

		if (wait++ == 50)									//To implement Non-Blocking delay.
		{
			wait = 0;
			str [10] = str [10] + 1;						//Increment the Last digit by 1.
			if (str [10] == 58)								//If the Last digit becomes '9' (ASCII - 57), need to increment the previous digits.
			{
				for (i = 10; i > 0; i--)					//The loop shall run from the the Last digit to the Second digit.
				{
					if (str [i] == 58)						//If the value of the particular digit is '9'.
					{
						str [i] = str [i] - 10;				//The value at the position shall be changed to '0'.
						str [i - 1] = str [i - 1] + 1;		//The value at the position before it shall be incremented by 1.
					}
				}
			}
			clcd_print (str, LINE2(6));						//Display the String on LINE-2 of the CLCD from position 6.
		}
	}
}
