/*
Name         : Prabhat Kiran
Date         : 20th November 2022
Description  : Implement a Right scrolling Message Marquee.
1. As soon as the board is powered up or reset, a static message (hardcoded) should start scrolling from left to right CLCD.
2. The scroll should repeat indefinitely.
3. The scroll frequency should be 0.5Hz (Approximately, Non-Timer Based).
 */

#include "main.h"

//Initialize a message string (Should not exceed 16)
static char str[] = "Hello World";

/* Function to return the String length */
unsigned short my_strlen (const char *s)
{
	unsigned short letter_count = 0;
	while (*s++ != '\0')
	{
		letter_count++;
	}

	return letter_count;
}

void main()
{
	//Initialize CLCD with the Basic configuration.
	init_clcd();

	//Variables to store non-blocking delay, display index & string length.
	unsigned short delay = 0, disp_index = 0, str_len = my_strlen(str);
	short reduce = 0;
	
	while (1)
	{
		//Increment display index in the range of 0-15 after some Non-blocking delay.
		if (delay++ == 900)
		{
			CLEAR_DISP_SCREEN;
			disp_index = (disp_index + 1) % 16;
			delay = 0;
		}

		//Print each character with respect to display index on the 1st line.
		for (unsigned short str_index = 0; str_index < str_len; str_index++)
		{
#if LEFT_TO_RIGHT
			//Use Mod-16 to rotate back the characters on the Screen.
			clcd_putch (str [str_index], LINE1((str_index + disp_index) % 16));
#else
			if ((reduce = str_index - disp_index) < 0)
				reduce += 16;
			clcd_putch (str [str_index], LINE1(reduce));
#endif
		}
	}
}
