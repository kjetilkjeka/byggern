#include <avr/io.h>
#define F_CPU 16E6
#include <avr/delay.h>
#include <avr/interrupt.h>

#include "../byggernlib/serialio.h"
#include "../byggernlib/spi.h"
#include "../byggernlib/MCP2515.h"
#include "../byggernlib/can.h"
#include "../byggernlib/command.h"



void mainInit()
{
	USART_Init(MYUBRR);
	
	fdevopen(USART_Transmit, USART_Transmit);
	SPI_Init();
	CAN_init();
	OLED_init();
	SLIDER_init();
	sei();
	
	
}



int main(void)
{
	mainInit();
	
	OLED_blankScreen();
	OLED_writeString("lolletylol");
	
	unsigned char ls;
	unsigned char rs;
	unsigned char lb;
	unsigned char rb;
	
	
    while(1)
	{
		
		
		//touch_measure(&ls, &rs, &lb, &rb);
		SLIDER_poll();
		//printf("ls is %u, rs is %u, lb is %u, rb is %u", ls, rs, lb, rb);
		_delay_ms(10);
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
