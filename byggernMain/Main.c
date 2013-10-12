
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include "byggernlib/serialio.h"
//#include "byggernlib/sram.h"
#include "byggernlib/extmem.h"
//#include "byggernlib/adc.h"
//#include "byggernlib/joystick.h"
//#include "byggernlib/oled.h"
//#include "byggernlib/menu.h"
#include "byggernlib/can.h"



void MAIN_init(void)
{
	USART_Init(MYUBRR);
	fdevopen(USART_Transmit, USART_Receive);
	EXTMEM_init();
	OLED_init();
	SPI_Init();
	CAN_init();

	//fdevopen(USART_Transmit, USART_Receive);	
	//fdevopen(OLED_writeChar, USART_Receive); //probably unsafe
	sei();
}



int main(void)
{	
	MAIN_init();
	
	printf("initialization\n\r");
	
	CAN_send();
	
	_delay_ms(5000);
	
	printf("the number recieved was: %d \r\n", CAN_recieve());
	
	
	while(1)
	{
		
	}
}




ISR(USART0_RXC_vect)
{
	USART_Transmit(USART_Receive());
	PORTB = 0;
}

