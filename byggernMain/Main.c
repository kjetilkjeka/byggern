
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include "byggernlib/serialio.h"
#include "byggernlib/sram.h"
#include "byggernlib/extmem.h"
#include "byggernlib/adc.h"
#include "byggernlib/joystick.h"


void MAIN_init(void)
{
	USART_Init(MYUBRR);
	EXTMEM_init();

	fdevopen(USART_Transmit, USART_Receive);
	sei();
}

int main(void)
{	
	MAIN_init();
	
	//USART_Transmit_String("sending fungerer, ");
	//printf("tester mottak    \n");
	
		
	//SRAM_test();
	
	while(1)
	{
		
		printf("%d", (int)JOYSTICK_direction());
		
		_delay_ms(1000);
	}		
}




ISR(USART0_RXC_vect)
{
	USART_Transmit(USART_Receive());
	PORTB = 0;
}
