/*
Name         : Prabhat Kiran
Date         :
Description  :
*/

#include <xc.h>
#include "external_interrupt.h"

void init_external_interrupt (void)
{
	//To select the Edge.
	INTEDG0 = 1;
	//Clear the Interrupt flag.
	INT0F = 0;
	//Enable External interrupt.
	INT0E = 1;
}
