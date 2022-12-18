#ifndef MAIN_H
#define MAIN_H

/* MACRO for the PORTS */
#define SSD_DATA_PORT PORTD
#define SSD_CTRL_PORT PORTA
#define KEY_PORT PORTC

/* MACRO for the STATES */
#define ZERO	0xE7
#define ONE		0x21
#define TWO		0xCB
#define THREE	0x6B
#define FOUR	0x2D
#define FIVE	0x6E
#define SIX		0xEE
#define SEVEN	0x23
#define EIGHT	0xEF
#define NINE	0x6F
#define UNDER	0x40

/* Function decalrations */
unsigned char key_press (void);
void display (unsigned char data[]);

#endif
