#ifndef MAIN_H
#define MAIN_H

/* Macro for the PORTS */
#define LED_ARRAY 		PORTB
#define KEY_PORT 		PORTC
#define SWITCH1 		0X0E
#define SWITCH2 		0x0D
#define SWITCH3 		0x0B
#define SWITCH4 		0X07

#define ALL_RELEASED 	0X0F

/* Function calls for the Patterns */
unsigned char key_press (void);
void led_train (void);
void led_L_to_R (void);
void led_alternate (void);
void led_nibble (void);

#endif
