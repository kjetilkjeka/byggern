
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#include "../byggernlib/serialio.h"
//#include "../byggernlib/sram.h"
#include "../byggernlib/extmem.h"
//#include "../byggernlib/adc.h"
//#include "../byggernlib/joystick.h"
//#include "../byggernlib/oled.h"
//#include "../byggernlib/menu.h"
#include "../byggernlib/MCP2515.h"
#include "../byggernlib/can.h"
#include "../byggernlib/spi.h"



void MAIN_init(void)
{
	USART_Init(MYUBRR);
	fdevopen(USART_Transmit, USART_Receive);
	//EXTMEM_init();
	//OLED_init();
	SPI_Init();
	
	CAN_init();
	
	sei();
}



int main(void)
{	
	MAIN_init();
	
	
	
	/*
	int dataBytes[8];
	dataBytes[0] = 12;
	dataBytes[1] = 72;
	dataBytes[2] = 95;
	CAN_send(11, 3, dataBytes);
	*/
	
	printf("END OF PROGRAM \n\r");
	while(1)
	{
		printf("still wake");
		_delay_ms(60000);
		
	}
}




ISR(USART0_RXC_vect)
{
	USART_Transmit(USART_Receive());
	PORTB = 0;
}

ISR(INT0_vect)
{
	int result[8];
	int dataByte;
	
	int ID = CAN_recieve(&dataByte, result);
	
	printf("ID is %u \n\r", ID);
	for(int i = 0; i < dataByte; i++)
	{
		printf("result[%u] = %u \n\r", i, result[i]);
	}
	
	MCP_write(CANINTF, 0x00); // turn off the interupt flag after reading
}
