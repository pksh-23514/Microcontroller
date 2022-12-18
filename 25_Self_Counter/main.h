#ifndef MAIN_H
#define MAIN_H

/* MACRO for the PORTS and STATES */
#define SSD_DATA_PORT PORTD
#define SSD_CTRL_PORT PORTA
#define KEY_PORT PORTC

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
#define DOT		0x10
#define BLANK	0x00

/* Function declarations */
void display (unsigned char data[]);
unsigned char key_press (void);
void write_internal_eeprom (unsigned char address, unsigned char data);
unsigned char read_internal_eeprom (unsigned char address);

#endif
