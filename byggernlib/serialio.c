#include <avr/io.h>
#include <stdlib.h>

#include "serialio.h"


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
	while ( !( UCSRnA & (1<<UDREn)) );
	// Put data into buffer, sends the data
	UDRn = data;
}


unsigned char USART_Receive( void )
{
	// Wait for data to be received
	while ( !(UCSRnA & (1<<RXCn)) );
	// Get and return received data from buffer
	return UDRn;
}


void USART_Init(unsigned int baud)
{
	//Set baud rate
	UBRRnH = (unsigned char)(baud>>8);
	UBRRnL = (unsigned char)baud;
	//Enable receiver and transmitter
	UCSRnB = MYUCSRnB;
	// Set frame format: 8data, 2stop bit
	UCSRnC = MYUCSRnC;
}


void USART_Flush( void )
{
	unsigned char dummy;
	while ( UCSRnA & (1<<RXCn) ) dummy = UDRn;
}





