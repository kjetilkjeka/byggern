#ifndef SERIALIO_H
#define SERIALIO_H

#define FOSC 4915200UL		// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init( unsigned int ubrr );
unsigned char USART_Receive( void );
void USART_Transmit( unsigned char data );
void USART_Flush();
void USART_Transmit_String(unsigned char *transmitString );


#endif