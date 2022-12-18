#ifndef MAIN_H
#define MAIN_H

/* Macro for the PORTS */
#define LED_ARRAY 	PORTB
#define KEY_PORT 	PORTC

/* Function calls for the Pattern */
unsigned char key_press (void);
void led_train (unsigned char);

#endif
