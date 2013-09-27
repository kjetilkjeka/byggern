
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include "byggernlib/serialio.h"
//#include "byggernlib/sram.h"
#include "byggernlib/extmem.h"
#include "byggernlib/adc.h"
#include "byggernlib/joystick.h"
#include "byggernlib/oled.h"
#include "byggernlib/menu.h"



void MAIN_init(void)
{
	USART_Init(MYUBRR);
	EXTMEM_init();
	OLED_init();
	//MENU_init();

	fdevopen(USART_Transmit, USART_Receive);
	//fdevopen(OLED_writeChar, USART_Receive); //probably unsafe
	sei();
}



int main(void)
{	
	MAIN_init();
	
	MENU_start();
	
	while(1)
	{
		
	}
}




ISR(USART0_RXC_vect)
{
	USART_Transmit(USART_Receive());
	PORTB = 0;
}

