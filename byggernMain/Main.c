
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include "byggernlib/serialio.h"

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




ISR(USART0_RXC_vect)
{
	USART_Transmit(USART_Receive());
	PORTB = 0;
}


