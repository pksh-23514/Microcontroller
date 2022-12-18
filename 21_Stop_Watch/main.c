/*
Name         : Prabhat Kiran
Date         : 30th November 2022
Description  : Implement a Stop-Watch with 5 Laps.
1. As soon as the board is powered up or reset, CLCD display the message shown .
2. The Start / Stop Key is used to start the timer.
3. The first line shows the current time running as HH:MM:SS:ss.
4. The Lap / Reset key should capture the Lap time.
5. The latest Lap record should be shown on the second line.
6. Should be possible to capture 5 Lap time records max.
7. To view the recorded laps you need to stop the timer using Start / Stop Key and Press, Scroll - Up and Down Keys .
8. On press of the Lap /Reset Key while the timer is not running, all the timings including the recorded laps should get cleared.
*/

#include <xc.h>
#include "main.h"
#include "matrix_keypad.h"
#include "clcd.h"
#include "timer2.h"

unsigned int arr [6][4];
unsigned int flag;

/* Basic Configurations */
void init_config (void)
{
	init_matrix_keypad();
	init_clcd();
	init_timer2();

	GIE = 1;				//Global Interrupt Enable.
	PEIE = 1;				//Peripheral Interrupt Enable.
}

void main()
{
	init_config();

	/* Local varaibles */
	unsigned char key;
	unsigned int key1_count = 0;
	unsigned int key2_count = 1;
	unsigned int key3_count = 1;
	unsigned int cent = 0;
	unsigned int sec = 0;
	unsigned int min = 0;
	unsigned int hr = 0;

	while(1)
	{
		clcd_print ("SW: ", LINE1(0));						//To display the String on LINE-1 from Position 0.

		clcd_putch (((hr / 10) % 10) + '0', LINE1(5));		//To display the Hours.
		clcd_putch ((hr % 10) + '0', LINE1(6));
		clcd_putch (':', LINE1(7));

		clcd_putch (((min / 10) % 10) + '0', LINE1(8));		//To display the Minutes.
		clcd_putch ((min % 10) + '0', LINE1(9));
		clcd_putch (':', LINE1(10));

		clcd_putch (((sec / 10) % 10) + '0', LINE1(11));	//To display the Seconds.
		clcd_putch ((sec % 10) + '0', LINE1(12));
		clcd_putch (':', LINE1(13));

		clcd_putch (((cent / 10) % 10) + '0', LINE1(14));	//To display the Centi-Seconds.
		clcd_putch ((cent % 10) + '0', LINE1(15));

		key = read_switches (STATE_CHANGE);					//To read the Key press.

		if (key == 1)										//If the SW1 is pressed, Start or Stop the Timer based on the Number of times the key is pressed.
		{
			key1_count++;									//Increment the 'key1_count'. {Start - Odd Press and Stop - Even Press}
		}
		if (key == 2)										//If the SW2 is pressed.
		{
			if (key1_count % 2 == 0)						//If the Timer is stopped (Even Press of SW1) and the SW2 is pressed, reset all the timings including the recorded laps.
			{
				hr = 0;
				min = 0;
				sec = 0;
				cent = 0;
				key2_count = 0;
				CLEAR_DISP_SCREEN;							//To clear the CLCD screen.
			}
			else											//Otherwise, capture the Lap time .
			{
				arr [key2_count][0] = hr;
				arr [key2_count][1] = min;
				arr [key2_count][2] = sec;
				arr [key2_count][3] = cent;

				clcd (key2_count);							//To display the LAP on the CLCD.
				key2_count++;								//Increment the 'key2_count' by 1.

				if (key2_count > 6)							//If the 'key2_count' is greater than 6, reset it.
				{
					key2_count = 1;
				}
			}
		}

		if (key == 3 && key1_count % 2 == 0)				//If the Timer is stopped (Even Press of SW1) and SW3 is pressed.
		{
			if (key2_count >= key3_count)					//If the 'key3_count' is less than 'key2_count', scroll UP the LAPs saved.
			{
				clcd (key3_count);							//To display the LAP on the CLCD.
				key3_count++;								//Increment the 'key3_count' by 1.
			}
			else											//Otherwise, reset the 'key3_count' to 1.
			{
				key3_count = 1;
			}
		}

		if (key == 4 && key1_count % 2 == 0)				//If the Timer is stopped (Even Press of SW1) and SW4 is pressed.
		{
			if (key2_count >= key3_count)					//If the 'key3_count' is less than 'key2_count', scroll DOWN the LAPs saved.
			{
				clcd (key3_count);							//To display the LAP on the CLCD.
				key3_count--;								//Decrement the 'key3_count' by 1.
			}
			else											//Otherwise, update the 'key3_count' to 'key2_count - 1'.
			{
				key3_count = key2_count - 1;
			}
		}

		if (key1_count % 2 == 1)							//If the Timer is ON (Odd Press of SW1).
		{
			if (flag == 1)									//If the 'flag' is 1, increment the Timer.
			{
				cent++;										//Increment the Centi-seconds.
				if (cent == 99)								//If the Centi-second reaches 99, reset it to 0 and increment the Seconds.
				{
					cent = 0;
					sec++;
					if (sec == 59)							//If the Seconds reaches 59, reset it to 0 and increment the Minutes.
					{
						sec = 0;
						min++;
						if (min == 59)						//If the Minutes reaches 59, reset it to 0 and increment the Hours.
						{
							min = 0;
							hr++;
							if (hr == 99)					//If the Hours reaches 99, reset it to 0.
							{
								hr = 0;
							}
						}
					}
				}
			}
			flag = 0;										//Reset the 'flag' to 0.
		}
	}
}

void clcd (int key2_count)
{
	if (key2_count > 1 && key2_count  < 6)					//If the 'key2_count' lies in between 1 to 6; display the LAP on the CLCD.
	{

		clcd_print ("LAP", LINE2(0));

		clcd_putch (key2_count + '0', LINE2(3));

		clcd_putch (((arr [key2_count][0] / 10) % 10) +'0', LINE2(5));
		clcd_putch ((arr [key2_count][0] % 10) +'0', LINE2(6));
		clcd_putch (':', LINE2(7));

		clcd_putch (((arr [key2_count][1] / 10) % 10) +'0', LINE2(8));
		clcd_putch ((arr [key2_count][1] % 10) +'0', LINE2(9));
		clcd_putch (':', LINE2(10));

		clcd_putch (((arr [key2_count][2] / 10) % 10) +'0', LINE2(11));
		clcd_putch ((arr [key2_count][2] % 10) +'0', LINE2(12));
		clcd_putch (':', LINE2(13));

		clcd_putch (((arr [key2_count][3] / 10) % 10) +'0', LINE2(14));
		clcd_putch ((arr [key2_count][3] % 10) +'0', LINE2(15));
	}
}
