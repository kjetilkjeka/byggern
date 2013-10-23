#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#include "../byggernlib/spi.h"
#include "../byggernlib/MCP2515.h"
#include "../byggernlib/can.h"
#include "../byggernlib/serialio.h"

void mainInit()
{
	USART_Init(MYUBRR);
	fdevopen(USART_Transmit, USART_Receive);
	SPI_Init();
	CAN_init();
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
	
	DDRE = (1<<PE3);
	
	ICR3 = 160000; // this is 16bit must fix safe initialization
	OCR3A = 160000/2;
	
	// this register is correct
	
	TCCR3A = (1<<COM3A1)|(1<<WGM31); // toggle OC1A on comperator match (check wether its toggle or set)
	TCCR3B = (1<<WGM32)|(1<<WGM33)|(1<<CS30);
	
	
	
    while(1)
    {
		
	}
}


ISR(CANINT_vect)
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
