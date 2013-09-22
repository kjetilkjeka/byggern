
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

	//fdevopen(USART_Transmit, USART_Receive);
	fdevopen(OLED_writeChar, USART_Receive); //probably unsafe
	sei();
}



int main(void)
{	
	MAIN_init();
	
	OLED_blankScreen();
	OLED_setPage(0);
	OLED_setCursor(0);
	OLED_writeString("lol");

	
	/*
	SRAM_test();
	
	for(int i = 0; i < 2048; i++)
		SRAM_test2(i);
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

