/*
Name         : Prabhat Kiran
Date         : 18th November 2022
Description  : Implement a 8-field Password access to Screen.
1. As soon as the board is powered up or reset, CLCD display the title in the first line.
2. In second line, an ‘_’ (underscore) should blink at rate of 0.5Hz to display the password entry which is indicated as ‘*’ (star).
3. Combination of Key1 and Key2 has to be used as a password.
4. You should provide a max if 5 chances to unlock the system.
5. On every wrong entry an LED should blink constant rate
6. The rate of blink doubles on every failure attempt.
7. On the fifth failure attempt the LED should glow constant and a message has to be put on screen indicating failure.
8. You have to reset the board to retry.
9. On a successful attempt the Embedded message should be displayed on screen.
*/

#include <xc.h>
#include <string.h>
#include "main.h"
#include "timer0.h"
#include "matrix_keypad.h"
#include "clcd.h"

extern unsigned short blink;
unsigned int flag = 1;

void check_matrix_keypad (void)
{
	char password[8] = "00001111";				//Default Password.
	char str[8];
	static unsigned long delay;
	static unsigned int j;
	static unsigned int k;
	static unsigned int failure_flag;
	static unsigned int led;
	static unsigned int no_attempts = 5;		//To store the Number of Password Attempts.
	unsigned char key;
	static unsigned int i;
	if (i < 8)
	{
		if (blink == 120)						//If 'blink' reaches 120; reset the 'blink' to 0.
			blink = 0;
		else if (blink % 2 == 0)				//If the 'blink' is an Even value, display the '_'.
		{
			clcd_putch ('_', LINE2(i));
		}
		else if (blink % 2 == 1)				//If the 'blink' is an Odd value, display the ' '.
		{
			clcd_putch (' ', LINE2(i));
		}
		if (flag >= 2)							//If the 'flag' is greater than equal to 2; Toggle the LED based on the 'blink' value.
		{
			if (blink % 2 == 0)					//If the 'blink' is an Even value, turn ON the LED.
				RB0 = 1;
			else								//If the 'blink' is an Odd value, turn OFF the LED.
				RB0 = 0;
			if (flag == 6)						//If the 'flag' is 6; turn ON the LED irrespective of the 'blink'.
				RB0 = 1;
		}
	}

	if(j < 8)									//To read the 8-field Password from the User.
	{
		failure_flag = 0;
		clcd_print(" Enter Password ", LINE1(0));

		key = read_switches(STATE_CHANGE);		//To read the Key Press.
		if (key != ALL_RELEASED)				//If any of the Key is pressed.
		{
			if (key == 1 || key == 4)			//If the SW1 or SW4 is pressed, read the Password as '0' or '1' based on the corresponding Key press.
			{
				if(key == 4)					//If the SW4 is pressed, read '0'.
					key = 0;
				str[j] = key + 48;				//Otherwise, read '1'.
			}

			clcd_putch ('*', LINE2(j++));		//Display '*' to hide the Password while reading.
			i++;
		}

		if (j == 8)								//If the 8-field Password is read from the User.
		{
			if (no_attempts > 0)				//If the Password Attempts are left.
			{
				for(k = 0; k < 8; k++)			//The loop shall run to check if the Password read is matching with the Default Password.
				{
					if(str[k] != password[k])	//If the Password doesn't matches, display the Error messages.
					{
						clcd_print ("Try Again", LINE1(0));
						clcd_putch (no_attempts + '0',LINE2(0));
						clcd_print ("Attempts", LINE2(2));
						for (delay = 5000; delay--;);
						CLEAR_DISP_SCREEN;

						failure_flag = 1;
						i = 0;
						j = 0;
						flag++;
						break;
					}
				}
				if (failure_flag == 0)			//If the Password matches, display the Successful message and turn OFF the LED.
				{
					RB0 = 0;
					CLEAR_DISP_SCREEN;
					clcd_print ("   SUCCESSFUL   ", LINE2(0));
				}
				no_attempts--;					//Decrement the Number of Password Attempts.
			}
			else								//If there are no more Attempts left, display the Error message.
			{
				CLEAR_DISP_SCREEN;
				clcd_print ("Attempts Over", LINE1(0));
				clcd_print ("RESET BOARD", LINE2(0));
			}
		}
	}
}

/* Basic Configuration */
void init_config(void)
{
	RB0 = 0;
	GIE = 1;
	PEIE = 1;
	init_matrix_keypad();
	init_clcd();
	init_timer0();
}

void main(void)
{
	init_config();

	while(1)
	{
		check_matrix_keypad();
	}
}
