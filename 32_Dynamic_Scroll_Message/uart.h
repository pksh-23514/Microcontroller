#ifndef SCI_H
#define SCI_H

/* MACRO for the PORTS */
#define RX_PIN				TRISC7
#define TX_PIN				TRISC6

/* Function declarations */
void init_uart (void);
void putch (unsigned char byte);
int puts (const char *s);
unsigned char getch (void);
unsigned char getch_with_timeout (unsigned short max_time);
unsigned char getche (void);

#endif
