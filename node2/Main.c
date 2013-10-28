#include <avr/io.h>
#define F_CPU 8E6
#include <avr/delay.h>
#include <avr/interrupt.h>

#include "../byggernlib/spi.h"
#include "../byggernlib/MCP2515.h"
#include "../byggernlib/can.h"
#include "../byggernlib/serialio.h"
#include "../byggernlib/command.h"

void mainInit()
{
	USART_Init(MYUBRR);
	fdevopen(USART_Transmit, USART_Receive);
	SPI_Init();
	CAN_init();
	SERVO_init();
	sei();
		
	
}





int main(void)
{
	
	mainInit();	
	
	
	int dataBytes[8];
	dataBytes[0] = 13;
	dataBytes[1] = 72;
	dataBytes[2] = 95;
	CAN_send(11, 3, dataBytes);
	
	
	printf("EFLG is: %u \n\r", MCP_read(EFLG));
	//MCP_write(CANINTF, 0x00); // turn off the interupt flag after reading
	
	
    while(1)
    {
		//SERVO_test();
	}
}


ISR(CANINT_vect)
{
	
	printf("lol");
	int result[8];
	int dataByte;
	
	uint16_t cid = CAN_recieve(&dataByte, result);
	
	COMMAND_doCommand(cid, dataByte, result);
	
	MCP_write(CANINTF, 0x00); // turn off the interupt flag after reading
}


/*
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
*/