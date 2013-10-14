
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
#include "byggernlib/MCP2515.h"
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
	
	
	int dataBytes[8];
	dataBytes[0] = 12;
	dataBytes[1] = 72;
	dataBytes[2] = 95;
	CAN_send(11, 3, dataBytes);
	
	
	
	int result[8];
	int dataByte;
	
	int ID = CAN_recieve(&dataByte, result);
	
	printf("ID is %u \n\r", ID);
	for(int i = 0; i < dataByte; i++)
	{
		printf("result[%u] = %u \n\r", i, result[i]);
	}
	
	printf("END OF PROGRAM \n\r");
	while(1)
	{
		
		MCP_reset();
		_delay_us(100);
		//printf("LOLOLOLettyLOL");
	}
}




ISR(USART0_RXC_vect)
{
	USART_Transmit(USART_Receive());
	PORTB = 0;
}

