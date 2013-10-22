#ifndef SERIALIO_H
#define SERIALIO_H

#if defined (__AVR_ATmega128__)
#define FOSC 8000000UL
#define MYUCSR0C ((1<<USBS0)|(3<<UCSZ00))
#define MYUSCR0B (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)
#elif defined(__AVR_ATmega162__)
#define FOSC 4915200UL		// Clock Speed
#define MYUCSR0C ((1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00))
#define MYUSCR0B (1<<RXEN0)|(1<<TXEN0)
#endif


#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init( unsigned int ubrr );
unsigned char USART_Receive( void );
void USART_Transmit( unsigned char data );
void USART_Flush();
void USART_Transmit_String(unsigned char *transmitString );


#endif