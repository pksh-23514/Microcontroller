/*
Name         : Prabhat Kiran
Date         : 15th November 2022
Description  : Implement the Time Separator with Timer 0, Timer 1 and Timer 2. The system should generate the time separator (half-second blink) of the Digital Clock with Multiple timers.
1. All three LEDs assigned to specific Timer should toggle at frequency of 0.5 Hz (500 msecs) as soon as the board is powered ON or Reset.
2. There should be Time synchronization between all LEDs on longer runs greater than hours (No drifts in the output should be seen).
*/

#include <xc.h>
#include "main.h"

static void init_config (void)
{
	ADCON1 = 0x0F;		//To make the pins as Digital I/O.
	TRISB = 0x00;		//To make the PORTB as an Output port.
	PORTB = 0x00;		//To turn OFF the LEDs when the Power is ON.

	TMR0ON = 1;			//To enable the Timer0.
	T08BIT = 1;			//To enable the Timer0 in 8-bit configuration.
	T0CS = 0;			//To set the Instruction Cycle Clock (Fosc/4) as the Clock source of Timer0.
	TMR0 = 6;			//To set the Timer0 register value from '6'. The calculation will set the Frequency required.
	TMR0IF = 0;			//To clear the Timer0 Overflow Interrupt Flag Bit.
	TMR0IE = 1;			//To set the Timer0 Overflow Interrupt Enable Bit.

	TMR1ON = 1;			//To enable the Timer1.
	TMR1 = 3036;		//To set the Timer1 register value from '3036'. The calculation will set the Frequency required.
	TMR1IF = 0;			//Initially, Interrupt flag can contain any garbage value. So, reset it before enabling the Interrupt.
	TMR1IE = 1;			//To set the Timer1 Overflow Interrup Enable Bit.

	TMR2ON = 1;			//To enable the Timer2.
	PR2 = 250;			//To set the Timer2 Period register value as '250' for the Overflow to happen after that particular count.
	TMR2IF = 0;			//To clear the Timer2 Overflow Interrupt Flag Bit.
	TMR2IE = 1;			//To set the Timer2 Overflow Interrupt Enable Bit.

	GIE = 1;			//To set the Global Interrupt Enable bit.
	PEIE = 1;			//To set the Peripheral Interrupt Enable bit.
}

void main()
{
	init_config ();		//To initialize the ports and registers with the default values.

	while (1)
	{
						//Empty Infinite loop.
	}
}
