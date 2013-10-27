#include <avr/io.h>
#define F_CPU 16E6
#include <avr/delay.h>
#include <avr/interrupt.h>

#include "../byggernlib/serialio.h"
#include "../byggernlib/spi.h"
#include "../byggernlib/MCP2515.h"
#include "../byggernlib/can.h"

void mainInit()
{
	USART_Init(MYUBRR);
	
	fdevopen(USART_Transmit, USART_Transmit);
	SPI_Init();
	CAN_init();
	//SERVO_init();
	sei();
	
	
}



int main(void)
{
	mainInit();
	
	
	int dataBytes[8];
	dataBytes[0] = 13;
	dataBytes[1] = 72;
	dataBytes[2] = 95;
	CAN_send(8, 3, dataBytes);
	
	
	
	printf("finally shit is working as it should");



	
    while(1)
	{
		//MCP_write(CANCTRL, 0b00000000);
		//printf("CANTRL er: %u \n\r", MCP_read(CANINTF));
		
		//SPI_Transmit(0b01010101);
		//_delay_ms(1000);
	}
}

ISR(CANINT_vect)
{
	int result[8];
	int dataByte;
	
	uint16_t cid = CAN_recieve(&dataByte, result);
	
	printf("ID is %u \n\r", cid);
	for(int i = 0; i < dataByte; i++)
	{
		printf("result[%u] = %u \n\r", i, result[i]);
	}
	
	MCP_write(CANINTF, 0x00); // turn off the interupt flag after reading
}
