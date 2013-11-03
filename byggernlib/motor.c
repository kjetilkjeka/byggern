#include "motor.h"
#define F_CPU 8E6
#include <avr/delay.h>

void MOTOR_init()
{
	DDRMJ2 = 0x00; //MJ2 inverted
	
	DDRMJ1 = 0b11111000; //MJ1 inverted
	MOTOR_enable(1);
	MOTOR_resetCounter();
	printf("motor is initiated\n\r");

}

int MOTOR_readEncoder()
{
	int value = 0;
	PORTMJ1 &= (0xff^(1<<MOTOR_OE));		// set OE low to enable output
	PORTMJ1 &= (0xff^(1<<MOTOR_SEL));	// set SEL low to get high byte
	_delay_us(20);						// delay 20 microseconds
	value = (PINMJ2<<8);				// read MSB
	PORTMJ1 |= (1<<MOTOR_SEL);			// set SEL high to get low byte
	_delay_us(20);						// wait 20 us
	value += PINMJ2;						// read LSB
	PORTMJ1 &= (0xff^(1<<MOTOR_RST));	// toggle reset to reset encoder
	PORTMJ1 |= (1<<MOTOR_RST);
	PORTMJ1 |= (1<<MOTOR_OE);			// set OE high to disable output
	return value;
}


void MOTOR_dir(uint8_t dir) // 1 er høyre
{
	
	if(dir)
		PORTMJ1 |= (1<<MOTOR_DIR);
	else
		PORTMJ1 &= (0xff ^ (1<<MOTOR_DIR));
	
	
}

void MOTOR_setSpeed(uint8_t speed)
{
	unsigned char messageBuf[4];
	
	messageBuf[0] = 0b01011110;
	messageBuf[1] = 0b00000000;
	messageBuf[2] = speed;
	
	TWI_Start_Transceiver_With_Data(messageBuf, 3);
}


void MOTOR_enable(uint8_t enable)
{
	
	if(enable)
		PORTMJ1 |= (1<<MOTOR_EN);
	else
		PORTMJ1 &= (0xff^(1<<MOTOR_EN));
	
}


void MOTOR_updatePos()
{
	int encoder = 0;
	//PORTMJ1 = PINMJ1 | (1<<MOTOR_SEL);
	/*
	for(int i = 0; i<8; i++)
	{
		encoder |= ((PINMJ2 & (DO0-i)) << i);	
	}
	*/
	encoder = PINMJ2;
	// high bits as well
	//MOTOR_resetCounter();
	
	MOTOR_setPos(((int8_t)encoder));
	if(encoder != 0)
		printf("encoder is %u \n\r", encoder);
		
}


void MOTOR_resetCounter()
{
	
	PORTMJ1 &= (0xff ^ (1<<MOTOR_RST));
	PORTMJ1 |= (1<<MOTOR_RST);
	
	
}


int MOTOR_setPos(int moved)
{
	static int position;
	position += moved;
	return position;
}

int MOTOR_getPos()
{
	return MOTOR_setPos(0);
}
