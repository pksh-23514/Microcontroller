/*
Name         : Prabhat Kiran
Date         : 30th November 2022
Description  : Implement a Dynamic Scrolling message marquee with Scroll Control.
1. As soon as the board is powered up or reste, system is scroll the a static message.
2. The scroll rate should be 0.5 HZs (approx, non time implementation) .
3. On press of the '#' key on host keyboard, target to should start accepting the new message from the user.
4. On the press of ‘#’ key for the second time, message should start the scroll on the left direction.
5. You may change the scroll direction using Left or Right Key.
6. The Start / Stop Key could be used to Stop the scroll.
7. The scroll should continue from the same instance on detecting the above keys.
*/

#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "uart.h"

/* Basic Configuration */
void init_config (void)
{
	init_uart();
	init_matrix_keypad();
	init_clcd();

	GIE =1;
	PEIE =1;
}

unsigned char ch;

void main()
{
	char c, temp;
	unsigned char s;
	unsigned char key;
	char str[17] = "                ";

	int flag = 0, flag1 = 0, flag2 = 1, flag3=1, wait= 0, i=0;

	init_config();

	clcd_print("               ", LINE1(0));
	clcd_print("               ", LINE2(0));

	while (1)
	{
		key = read_switches(STATE_CHANGE);				//To read the Key Press.
		if (ch != '\0')									//To check whether the character is Null character.
		{
			putch (ch);
			if (ch == '#')								//If '#' is pressed for the first time, Increment the 'flag1' and display in CLCD.
			{
				if (++flag1)							//Checking the 'flag1' and doing operation based on that.
				{
					if (flag1 == 3)
					{
						flag1 = 1;
						flag = 0;
						i = 0;
					}
					if (flag1 == 2)
					{
						flag = 1;
					}
					if (flag1 == 1)
					{
						clcd_print ("Enter_a_NEW_MSG ", LINE1(0));
						clcd_print ("                ", LINE2(0));
					}
				}
			}
			else
			{
				if ( flag == 0 )						//If the character is not '#' and flag equals 0, then update the 'ch' to String.
				{
					str[i] = ch;
					clcd_putch (ch, LINE2(i++));
					if (i == 16)
						i = 0;
				}
			}
			ch = '\0';
		}
		if (flag)										//If 'flag' is 1, then detect the Key pressed.
		{
			//Based on Key press, update 'flag' and 'wait' value.
			if (MK_SW1 == key)
			{
				wait = 0;
				flag2 = 1;
			}
			if (MK_SW2 == key)
			{
				wait = 0;
				flag2 = 0;
			}
			if (MK_SW3 == key)
			{
				wait = 0;
				flag3 = !flag3;
			}

			if (flag3)									//If 'flag3' is set, Start the Marquee.
			{
				if ( flag2 )							//If 'flag2' value is set, display the Left Marquee.
				{
					clcd_print("__LEFT_MARQUEE__",LINE1(0));
					clcd_print(str,LINE2(0));
					if ( wait++ == 250 )
					{
						temp = str[0];
						for ( int i = 0; i <= 14; i++ )
							str[i] = str[i+1];
						str[15] = temp;
						wait = 0;
					}
				}
				else									//Otherwise, display the Right Marquee.
				{
					clcd_print ("_RIGHT__MARQUEE_", LINE1(0));
					clcd_print (str, LINE2(0));
					if ( wait++ == 250 )
					{
						temp = str[15];
						for ( int i = 15; i >= 1; i-- )
							str[i] = str[i-1];
						str[0] = temp;
						wait = 0;
					}
				}
			}
			else										//Otherwise, Stop the Marquee.
			{
				clcd_print ("MESSAGE_MARQUEE ", LINE1(0));
				clcd_print (str, LINE2(0));
			}
		}
	}
}
