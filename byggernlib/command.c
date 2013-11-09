#include "servo.h"
#include "can.h"
#include "command.h"
#include <stdio.h>
#include "servo.h"
#include "motor.h"

#define F_CPU 8E6
#include <avr/delay.h>

void COMMAND_setServo(uint16_t angle)
{
	int data[2];
	data[0] = angle & 0xff;
	data[1] = (angle >> 8);
	CAN_send(SERVO, 2, data);
}

void COMMAND_setMotor(uint8_t pos)
{
	int data[1];
	data[0] = pos;
	CAN_send(MOTOR, 1, data);
}

void COMMAND_triggerSolenoid()
{
	int data[1];
	CAN_send(FIRE, 0, data);
}


void COMMAND_doCommand(uint16_t cid, int dataByte, int* data)
{
	uint16_t angle;
	uint8_t pos;
	switch(cid)
	{
		case(SERVO):
			// check that dataBytes == 2
			angle = data[0];
			angle += (data[1] & 0b11)<<8;
			
			SERVO_set(angle);
			break;
			
		case(MOTOR):
			// check that dataBytes == 1
			pos = data[0];
			pos = 255 - pos;
			MOTOR_setRef((int16_t)pos);
			break;
			
		case(FIRE):
			SOLENOID_fire();
			break;
			
	}

}

