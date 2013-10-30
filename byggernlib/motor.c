#include "motor.h"

void MOTOR_init()
{
	DDRMJ2 = 0xff; //MJ2 inverted
	DDRMJ1 = 0b00011111; //MJ1 inverted
	MOTOR_enable(1);
}


void MOTOR_dir(uint8_t dir) // 1 er høyre
{
	if(dir)
	PORTMJ1 = PINMJ1 | (1<<MOTOR_DIR);
	else
	PORTMJ1 = PINMJ1 & (0xff ^ (1<<MOTOR_DIR));
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
	PORTMJ1 = PINMJ1 | (1<<MOTOR_EN);
	else
	PORTMJ1 = PINMJ1 & (0xff ^ (1<<MOTOR_EN));
	
}

/*
uint8_t MOTOR_read()
{
	
}
*/