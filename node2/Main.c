#include <avr/io.h>
#define F_CPU 8E6
#include <avr/delay.h>
#include <avr/interrupt.h>

#include "../byggernlib/spi.h"
#include "../byggernlib/MCP2515.h"
#include "../byggernlib/can.h"
#include "../byggernlib/serialio.h"
#include "../byggernlib/command.h"
#include "../byggernlib/IR.h"
#include "../byggernlib/TWI_Master.h"








#define TWI_GEN_CALL         0x00  


#define TWI_CMD_MASTER_WRITE 0x10
#define TWI_CMD_MASTER_READ  0x20


#define SEND_DATA             0x01
#define REQUEST_DATA          0x02
#define READ_DATA_FROM_BUFFER 0x03


void mainInit()
{
	USART_Init(MYUBRR);
	fdevopen(USART_Transmit, USART_Receive);
	SPI_Init();
	
	CAN_init();
	SERVO_init();
	

	TWI_Master_Initialise();
	
	MOTOR_init();
	
	sei();
		
	
}



int main(void)
{
	
	
	mainInit();	
	

	
	//printf("EFLG is: %u \n\r", MCP_read(EFLG));
	//MCP_write(CANINTF, 0x00); // turn off the interupt flag after reading
	MOTOR_enable(1);
	MOTOR_setSpeed(50);
	
    while(1)
    {
		
		//_delay_ms(1000);
		//printf("still wake \n\r");
		
		MOTOR_dir(0);
		_delay_ms(2000);
		MOTOR_dir(1);
		_delay_ms(2000);
		
	}
}


ISR(CANINT_vect)
{
	cli();
	int result[8];
	int dataByte;
	
	uint16_t cid = CAN_recieve(&dataByte, result);
	
	COMMAND_doCommand(cid, dataByte, result);
	
	MCP_write(CANINTF, 0x00); // turn off the interupt flag after reading
	sei();
}



ISR(IRINT_vect)
{
	cli();
	// want 3 correct measurement
	_delay_ms(20);
	if(!(PINE & (1<<INT7)))
	{
		_delay_ms(20);
		if(!(PINE & (1<<INT7)))
		{
			printf("count is %u \n\r", IR_count());		
			do{
				_delay_ms(500);
			} while(!(PINE & (1<<INT7)));
		}			
	}
	sei();
}



