/*
Name         : Prabhat Kiran
Date         : 14th November 2022
Description  : Implement a 4 digit key press counter.
INPUT
1. DKS1 (Digital Keypad Switch 1) as Count Input.
2. DKS1 long press (2 secs) to reset the Count.
OUTPUT
1. Implement a 4 digit key press counter
2. On every key press counter value should increment by 1.
3. On a long key press (2 seconds), count should reset to zero.
*/

#include <xc.h>
#include "main.h"

static unsigned char digit [] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};	//MACRO array for lighting the Seven Segment Display for the particular digit.
unsigned char ssd [] = {ZERO, ZERO, ZERO, ZERO};												//Seven Segment Display data array.

static void init_config (void)
{
	ADCON1 = 0x0F;							//To make the Pins as Digital I/O.
	TRISD = 0x00;							//To make the PORTD as an Output port (Data Line for SSD).
	TRISA = TRISA & 0xF0;					//To make the PORTA as an Output port (Control Line for SSD).
	TRISC = TRISC | 0x01;					//To make the PORTC (1 Pin) as an Input pin.
	SSD_CTRL_PORT = SSD_CTRL_PORT | 0x0F;	//To switch on all the SSDs at the start.
}

void main()
{
	unsigned char flag, reset;
	static unsigned int count = 0, wait = 0;	//Initialize the Counter as '0' and Timer as '0'.
	init_config ();								//To configure the Ports and Pins initially.

	display (ssd);								//At the start, the default value shown on SSD is '0'.

	while (1)
	{
		flag = key_press ();					//To check if the Digital Key is pressed or not.
		if (flag == 1)							//If the Key is pressed.
		{
			wait += 1;							//Start the Timer to store the duration for which the Key is pressed.
		}
		if ((flag == 1) && (wait > 200))		//If the Key is pressed and the Timer value goes more than 200; it is a Long press.
		{
			count = 0;							//The Counter shall be reset.
			reset = 1;							//The Reset flag shall be set.
		}
		if ((flag == 0) && (reset == 1))		//If the Key is released and Reset flag is set, reset the Timer and Reset flag for the next Key press.
		{
			wait = 0;
			reset = 0;
		}
		if ((flag == 0) && (wait > 20 && wait < 200))	//If the Key is released and the Timer value lies in the range of 20-200; it is a Short press.
		{
			count += 1;							//Increment the 'count' by 1.
			wait = 0;							//Reset the Timer.
		}

		ssd [3] = digit [count % 10];			//Units place digit.
		ssd [2] = digit [(count / 10) % 10];	//Tenth place digit.
		ssd [1] = digit [(count / 100) % 10];	//Hundreth place digit.
		ssd [0] = digit [(count / 1000) % 10];	//Thousandth place digit.
		
		display (ssd);							//Display the Counter on Seven Segment Display.
		
		if (count == 9999)						//If the Counter reaches the maximum 4-digit number; reset the Counter.
			count = 0;
	}

}
