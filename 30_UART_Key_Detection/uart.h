#ifndef SCI_H
#define SCI_H

/* Macro for the Ports */
#define RX_PIN		TRISC7
#define TX_PIN		TRISC6

/* Function declarations */
void init_uart (void);
void putch (unsigned char byte);
int puts (const char *s);

#endif
