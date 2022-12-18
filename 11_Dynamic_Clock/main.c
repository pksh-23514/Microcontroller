/*
Name         : Prabhat Kiran
Date         : 9th November 2022
Description  : Implement dynamic clock on SSD using Internal Timer.
1. As soon as the board is powered on or reset, the clock should start at 00.00.
2. The decimal point of the hours field (one’s place) should blink every 500 msecs (0.5 Hz).
3. The clock format should be 24Hrs
4. The clock enters into configuration mode by pressing Set / Edit Key.
5. The configuration mode is indicated by a blink on the minute field every 500 msecs
6. The fields can be selected with Choose Field Key, The selected field should blink at the rate of 500 mses indicating the selection
7. The Increment Key could be used to increment and the Decrement Key could be used to decrement the value of selected field, It should be level triggered
8. Once the time is set you may use the Set / Edit Key to start the clock and this mode is called a run mode.
9. No key except Set / Edit key should sensitive in run mode
*/

#include <xc.h>
#include "main.h"

static unsigned char digit [] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};	//MACRO array for lighting the Seven Segment Display for the particular digit.
unsigned char ssd [] = {ZERO, ZERO, ZERO, ZERO};												//Seven Segment Display data array.
unsigned char count = 0;

static void init_config (void)
{
	ADCON1 = 0x0F;							//To make the Pins as Digital I/O.
	TRISD = 0x00;							//To make the PORTD as an Output port (Data Line for SSD).
	TRISA = TRISA & 0xF0;					//To make the PORTA as an Output port (Control Line for SSD).
	SSD_CTRL_PORT = SSD_CTRL_PORT | 0x0F;	//To switch on all the SSDs at the start.

	TMRON = 1;								//To enable the Timer0.
	T08BIT = 1;								//To enable the Timer0 in 8-bit configuration.
	T0CS = 0;								//To set the Instruction Cycle Clock (Fosc/4) as the Clock source of Timer0.
	PSA = 1;								//No Prescaler Assignment bit.
	TMR0 = 6;								//To set the Timer0 register value from '6'. The calculation will set the Frequency required.
	TMR0IE = 1;								//To set the Timer0 Overflow Interrupt Enable Bit.
	TMR0IF = 0;								//To clear the Timer0 Overflow Interrupt Flag Bit.

	GIE = 1;								//To set the Global Interrupt Enable bit.
	PEIE = 1;								//To set the Peripheral Interrupt Enable bit.
}

void main()
{
	init_config ();

	unsigned char hour = 0, min = 0, flag;
	unsigned int wait = 1;

	while (1)
	{
		display (ssd);

		if (wait++ == 200)			//To prevent the Bouncing effect on the Digital key.
		{
			flag = key_press ();	//To detect the Key Press.
			wait = 0;
		}

		if (count % 2 == 1)			//Alternatively blink the 'dot'.
		{
			//Display with dot. Toggle the 4th bit of the Macro in SSD3.
			ssd [1] = digit [(hour % 10)] | DOT;
		}
		else
			ssd [1] = digit [(hour % 10)];

		if (count == 120)			//If the 'count' becomes 120; 60 seconds have passed and increment the 'min' by 1.
		{
			min += 1;
			count = 0;
		}

		if (min == 60)				//If the 'min' becomes 60; reset to 0 and increment the 'hour' by 1.
		{
			hour += 1;
			min = 0;
		}

		if (hour == 24)				//If the 'hour' becomes 24; reset to 0 as 24-hr format has range from 0 to 23.
		{
			hour = 0;
		}

		ssd [3] = digit [min % 10];
		ssd [2] = digit [(min / 10) % 10];
		ssd [0] = digit [(hour / 10) % 10];
	}
}
