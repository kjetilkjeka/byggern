
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include "byggernlib/serialio.h"
#include "byggernlib/sram.h"
#include "byggernlib/extmem.h"
#include "byggernlib/adc.h"
//#include "byggernlib/joystick.h"
#include "byggernlib/oled.h"



void MAIN_init(void)
{
	USART_Init(MYUBRR);
	EXTMEM_init();
	OLED_init();

	fdevopen(USART_Transmit, USART_Receive);
	sei();
}



int main(void)
{	
	MAIN_init();
	
	/*
	for(int i = 0; i < 1024; i++)
	{
		//_delay_ms(500);
		//(i % 2 == 0 ? OLED_writeData(0x00) : OLED_writeData(0xff));
		OLED_writeData(0x00);
	}
	*/

	OLED_writeChar(33);
	OLED_writeData(0x00);
	
	/*
	for(int i = 0; i < 27; i++)
	{
		OLED_writeChar(33 + i);
		OLED_writeData(0x00);
			
	}
	*/
	
	
	
	
	
	
	
	while(1)
	{
		//OLED_writeData(0xff);
		//OLED_writeData(0x00);
		//_delay_ms(100);
	}		
}




ISR(USART0_RXC_vect)
{
	USART_Transmit(USART_Receive());
	PORTB = 0;
}

