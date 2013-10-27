#ifndef SERIALIO_H
#define SERIALIO_H

#include <avr/sfr_defs.h>

#if defined (__AVR_ATmega128__)
#define FOSC 8000000UL

#define UDRn UDR0
#define UDREn UDRE0
#define UBRRnH UBRR0H
#define UBRRnL UBRR0L
#define UCSRnA UCSR0A
#define UCSRnB USCR0B
#define UCSRnC UCSR0C

#define RXC RXC0

#define MYUCSRnC ((1<<USBS0)|(3<<UCSZ00))
#define MYUCSRnB (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)
#elif defined(__AVR_ATmega162__)
#define FOSC 4915200UL		// Clock Speed

#define UDRn UDR0
#define UDREn UDRE0
#define UBRRnH UBRR0H 
#define UBRRnL UBRR0L
#define UCSRnA UCSR0A
#define UCSRnB UCSR0B
#define UCSRnC UCSR0C

#define RXCn RXC0

#define MYUCSRnC ((1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00))
#define MYUCSRnB (1<<RXEN0)|(1<<TXEN0)
#elif defined(__AVR_AT90USB1287__)
#define FOSC 16E6

#define UDRn UDR1
#define UDREn UDRE1
#define UBRRnH UBRR1H
#define UBRRnL UBRR1L
#define UCSRnA UCSR1A
#define UCSRnB UCSR1B
#define UCSRnC UCSR1C

#define RXCn RXC1

#define MYUCSRnB (1<<RXEN1)|(1<<TXEN1)
#define MYUCSRnC (1<<USBS1)|(3<<UCSZ10)
#endif


#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


void USART_Init(unsigned int baud);
unsigned char USART_Receive( void );
void USART_Transmit( unsigned char data );
void USART_Flush();
void USART_Transmit_String(unsigned char *transmitString );


#endif