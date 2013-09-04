/*
 * GccApplication2.c
 *
 * Created: 02.09.2013 13:35:33
 *  Author: kjetibk
 */ 
#define FOSC 4915200UL		// Clock Speed
#define BAUD 9600			
#define MYUBRR FOSC/16/BAUD-1

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

void USART_Init( unsigned int ubrr );
unsigned char USART_Receive( void );
void USART_Transmit( unsigned char data );
void USART_Flush();
void USART_Transmit_String(unsigned char *transmitString );

int main(void)
{
	
	USART_Init(MYUBRR);	
	fdevopen(USART_Transmit, USART_Receive);
	sei();
	
	USART_Transmit_String("sending fungerer, ");
	printf("tester mottak\n");
	
	while(1)
	{
		
	}		
}


/* this wont work
unsigned char * USART_Receive_String()
{
	unsigned char receiveString[256];
		
	// first wait for string
	while(!(UCSR0A & (1<<RXC0)));
	
	for(int i = 0; i < 256;i++)
	{
		receiveString[i] = UDR0;
		_delay_ms(1000);	
		while(!(UCSR0A & (1<<RXC0)));
		
	}
	
	return receiveString;
}
*/

ISR(USART0_RXC_vect)
{
	USART_Transmit(USART_Receive());
	PORTB = 0;
}

void USART_Transmit_String(unsigned char * transmitString )
{
	int i;
	for (i=0; transmitString[i] != NULL; i++)
	{
		USART_Transmit(transmitString[i]);
	}
	
}

void USART_Transmit( unsigned char data )
{
	//Wait for empty transmit buffer
	while ( !( UCSR0A & (1<<UDRE0)) ); // while(!UDRE0)
	// Put data into buffer, sends the data
	UDR0 = data;
}

unsigned char USART_Receive( void )
{
	// Wait for data to be received
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	// Get and return received data from buffer
	return UDR0;
}


void USART_Init( unsigned int ubrr )
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
}


void USART_Flush( void )
{
	unsigned char dummy;
	while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}
