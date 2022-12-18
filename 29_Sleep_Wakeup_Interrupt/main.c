/*
Name         : Prabhat Kiran
Date         : 4th December 2022
Description  : Implement System Sleep and Wake-up while Interrupt on change.
1. As soon as the board is powered up or reset, a message (say 1234) should be displayed in SSD.
2. A LED is toggled  every second.
3. System should go into sleep mode if no activity is detected.
4. System should wake up from sleep on detecting interrupt key.
*/

#include <xc.h>
#include "main.h"
#include "external_interrupt.h"
#include "isr.h"
#include "ssd_display.h"
#include "timer0.h"

bit key_detected;
unsigned char ssd[4];					//To declare the SSD array.

static void init_config (void)
{
	ADCON1 = 0x0F;						//Setting the PORT as Digital.
	TRISB6 = 0;							//Setting the PORT as Output Port.
	TRISB0 = 1;							//Setting the PORT as Input Port.

	init_external_interrupt ();
	init_ssd_control ();
	init_timer0 ();

	/* Enabling Interrupt */
	GIE = 1;
	PEIE = 1;
}

int a=0;

void main(void)
{
	unsigned short flag = 0;
	RB6 = 0;

	init_config ();						//To initialize the Basic Configuration.

	while (1)
	{
		if (key_detected) 				//To check the External Interupt.
		{
			//Reinitialise Interupt flag and LED Blink.
			key_detected = 0;
			a = 0;
			flag = 0;
			RB6 = 0;
		}

		if (flag == 0)					//If the 'flag' is 0, dispaly the SSD again.
		{
			ssd[0]=ONE;
			ssd[1]=TWO;
			ssd[2]=THREE;
			ssd[3]=FOUR;
			
			display(ssd);
			if (a == 5) 				//If the 'a' is 5, make the 'flag' as 1 and change to Sleep mode.
			{
				flag = 1;
				SLEEP ();				//To make the Controller to Sleep.
			}
		}
	}
}
