/*
Name         : Prabhat Kiran
Date         : 18th November 2022
Description  : Implement a 10-Digit DOWN Counter with Preset.
 */

#include <xc.h>
#include "clcd.h"
#include "matrix_keypad.h"

static void init_config (void)
{
	/* Basic Configuration */
	init_clcd ();
	init_matrix_keypad ();
}

void main()
{
	init_config ();

	//To initialize the varibales, char and array with the Starting values.
	int i = 15, wait2=0;
	unsigned char key;
	unsigned int count=0, flag=0;
	unsigned char str [17] = "COUNT:0000000000";

	clcd_print ("10_DIGIT_COUNTER", LINE1(0));						//To print the String on LINE-1 of the CLCD from position 0.
	clcd_print (str, LINE2(0));										//To print the String on LINE-2 of the CLCD from position 0.

	while (1)
	{
		key = read_switches(STATE_CHANGE);							//To read which Key is pressed.
		if (flag == 1)												//If the flag is '1' then Start the Counter or else go to Edit Mode.
		{
			if (count++ == 5000)									//To implement the Non-Blocking delay.
			{
				clcd_print(str, LINE2(0));							//To print the String on LINE-2 of the CLCD from position 0.
				str[15]--;											//To decrement the Last Digit of the Counter.
				
				/* The loop for decrementing the next array element or reset the counter */
				for (i = 15 ; i >= 6 ; i--)
				{
					if (str[6] == '/')								//Check the first array element is not number and then reset the Counter.
					{
						for (int i = 6; i<= 15; i++)				//The loop to reset the Counter.
						{
							str[i] = '0';
						}
						flag = 0;									//Reset the 'flag'.
						i = 15;
						break;
					}
					if (str[i] == '/')								//Check the array element is not a Number, then Decrement the previous array element and set the array element to 9.
					{
						str[i] = '9';

						if (i != 0)									//If the Digit is non-zero; decrement the Digit.
							str[i-1]--;
					}
				}
				count = 0;											//Reinitialise the Counter to 0.
			}
		}
		else														//To enter the Edit Mode.
		{
			if (key == MK_SW1)										//If SW1 is pressed, then Increment the value.
			{
				str[i]++;

				if ( str[i] == ':' )
					str[i] = '0';
			}
			if (key == MK_SW2)										//If SW2 is pressed, then Change the Field of the Counter.
			{
				clcd_putch (str [i], LINE2(i));						//To print the String on LINE-2 of the CLCD from position 'i'.
				i--;
				if (i == 5)
					i = 15;
				wait2 = 0;
			}
			if ( key == MK_SW3 )									//If SW3 is pressed, then Start the Counter.
			{
				flag = 1;
			}
			if (!flag)												//If the 'flag' is zero.
			{
				/* Then according to wait: Input to 2nd line of CLCD is given */
				if (wait2++ < 250)
				{
					clcd_putch (-1, LINE2(i));
				}
				else
				{
					clcd_putch (str [i], LINE2(i));					//To print the String on LINE-2 of the CLCD from position 'i'.

					if (wait2 == 500)
						wait2 = 0;									//Reset the 'wait2'.
				}
			}
			for (int i = 1000; i--;);								//Blocking delay for the Bouncing effect.
		}
	}
}
