/*
Name         : Prabhat Kiran
Date         : 24th November 2022
Description  : Implement a Dynamic Scrolling Number Marquee with Rotation Control.
1. As soon as the board is powered up or reset, CLCD display the title in the first line In second line, should prompt for feeding user msg.
2. The cursor should be blinking at rate of 0.5Hz (approx non timer implementation) with a default character 0 .Let's call this as preset mode.
3. You should be able to set the required digit with the help of Up / Left or Down / Right Key.
4. On selection of the required char you should press the Accept Key and move the cursor to the next location.
5. On entering the required message you could start the Marquee using Start / Stop Key.
6. The default direction should be from left to right for first character position, You may change the scroll direction using Up / Left or Down / Right Key.
7. The Start / Stop Key could be used to Stop the scroll.
8. One press of the Edit Key any instance the system should enter to Preset Mode.
9. In preset mode the Backspace Key is used to remove the accepted characters.
*/

#include <xc.h>
#include "clcd.h"
#include "matrix_keypad.h"

static void init_config (void)
{
	/* Basic Configuration */
	init_clcd();
	init_matrix_keypad();
}

void main(void)
{
	init_config();

	unsigned char key;
	int i=0, j=0, wait=0, wait1=0, wait2=0, flag = 0, flag1=1, flag2=0, flag3=1;
	unsigned char str[17] = "                ",temp;

	clcd_print ("SCROLL_NO_MARQUE", LINE1(0));						//To print the String on LINE-1 of the CLCD from position 0.

	while (1)
	{
		key = read_switches (STATE_CHANGE);							//To read the Key pressed.

		if (key == MK_SW1)											//If SW1 is pressed, increment the value in Edit mode, in Run mode it act as Left Marquee.
		{
			if (!flag)
			{
				j++;
				if (j == 10)
					j = 0;
				flag1 = 0;
				str[i] = j + 48;
			}
			else
				flag2 = 0;
		}
		if (key == MK_SW2)											//If SW2 is pressed, then in Edit mode decrement the value, in Run mode it act as Right Marquee.
		{
			if ( !flag )
			{
				j--;
				if (j == -1)
					j = 9;
				flag1 = 0;
				str[i] = j + 48;
			}
			else
			{
				flag2 = 1;
			}
		}

		if (!flag)
		{
			clcd_print ("SCROLL_NO_MARQUE", LINE1(0));				//To print the String on the LINE-1 of the CLCD at position 0.
			if (wait++ <= 500)										//To implement the Non-Blocking Delay.
			{
				if (!flag1)
					clcd_putch (j + 48, LINE2(i));
				else
					clcd_putch (-1, LINE2(i));
			}
			else
			{
				if (wait == 1000)
					wait = 0;
				clcd_print (" ", LINE2(i));
			}
		}
		else
		{
			clcd_print (str, LINE2(0));								//To print the String on the LINE-2 of the CLCD at position 0.
			if (flag3)												//Based on 'flag3', either Stopping or Marquee is done.
			{
				if (!flag2)											//Based on the 'flag2', the Left Marquee is displayed.
				{
					clcd_print("__LEFT_MARQUEE__", LINE1(0));
					if ( wait1++ == 250)
					{
						temp = str[0];
						for ( int i = 0; i<= 14; i++ )
						{
							str[i] = str[i+1];
						}
						str[15] =temp;
						wait1 = 0;
					}
				}
				else												//Otherwise, the Right Marquee is displayed.
				{
					clcd_print ("_RIGHT__MARQUEE_", LINE1(0));
					if (wait2++ == 250)
					{
						temp = str[15];
						for (int i = 15; i>= 1; i--)
						{
							str[i] = str[i-1];
						}
						str[0] = temp;
						wait2 = 0;
					}
				}
			}
		}

		if (key == MK_SW3)											//If SW3 is pressed, Stop / Start the Marquee.
		{
			if (flag)
			{
				flag3 = !flag3;
			}
		}

		if (key == MK_SW4)											//If SW4 is pressed, get to Edit / Run Mode.
		{
			flag = !flag;
			if (!flag)
			{
				for (int i =0; i<=15;i++)
				{
					str[i] = ' ';
				}
			}

			clcd_print (str, LINE2(0));								//To print the String on the LINE-2 of the CLCD at the position 0.
			i=0;
			j=0;
			flag1 = 1;

		}

		if (key == MK_SW5)											//If SW5 is pressed, set the value and move to the next Index.
		{
			if (!flag)
			{
				if (!flag1)
					clcd_putch (j+48, LINE2(i));
				else
					clcd_print (" ", LINE2(i));
				i++;
				flag1 = 1;
				j = 0;
				wait = 0;
				if (i == 16)
					i = 0;
			}
		}

		if (key == MK_SW6)											//If SW6 is pressed, remove the Current and Move to previous Position.
		{
			if (!flag)
			{
				clcd_print (" ", LINE2(i));
				str[i] = ' ';
				i--;
				if (i == -1)
					i = 0;
				clcd_print (" ", LINE2(i));
				str[i] = ' ';
				j = 0;
				flag1 = 1;
			}
		}

		for (int i = 1000;i--;);									//To implement the Blocking Delay to remove the Bouncing effect.
	}
}
