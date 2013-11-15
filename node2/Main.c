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
#include "../byggernlib/motor.h"
#include "../byggernlib/solenoid.h"


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
	
	SOLENOID_init();
	MOTOR_init();
	
	sei();
		
	
}



int main(void)
{
	
	
	mainInit();	
	
	//USART_Init(MYUBRR);
	//fdevopen(USART_Transmit, USART_Receive);
	//printf("ROFL\n\r");

	//DDRB |= (1<<PB6);
	
	/*
	cli();
	
	
	sei();
	*/
	
	//printf("EFLG is: %u \n\r", MCP_read(EFLG));
	//MCP_write(CANINTF, 0x00); // turn off the interupt flag after reading
	/*
	MOTOR_enable(1);
	MOTOR_setSpeed(100);
	int speed = 10;
	*/
	
	
	
	printf("test");
	
	int i = 0;
	uint8_t first;
	uint8_t second;
	
    while(1)
    {
		
		first = 0;
		second = 0;
		
		first = (uint8_t)USART_Receive();
		if(first != 0xff && first != 0xaa && first != 0x00) continue;
		
		second = (uint8_t)USART_Receive();
		if(first == 0xff)
			SERVO_set(second << 2);
		if(first == 0xaa)
			MOTOR_setRef(second);
		if(first == 0x00 && second == 0x00)
			SOLENOID_fire();
			
		//SERVO_set(second << 2);
		
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

ISR(TIMER3_CAPT_vect)
{
	MOTOR_updateSpeed();
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



