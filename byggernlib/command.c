#include "servo.h"
#include "can.h"
#include "command.h"
#include <stdio.h>
#include "servo.h"

void COMMAND_setServo(uint16_t angle)
{
	int data[2];
	data[0] = angle & 0xff;
	data[1] = (angle >> 8);
	CAN_send(SERVO, 2, data);
}


void COMMAND_doCommand(uint16_t cid, int dataByte, int* data)
{
	uint16_t angle;
	switch(cid)
	{
		case(SERVO):
			// check that dataBytes == 2
			angle = data[0];
			angle += (data[1] & 0b11)<<8;
			printf("angle is: %u \n\r", angle);
			SERVO_set(angle);
			
	}
	
}