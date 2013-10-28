// this file defines the CAN commands

#ifndef COMMAND_H_
#define COMMAND_H_

#define FIRE 100
#define POSITION 101
#define SERVO 102 // gives 2 byte 10 LSB give servo pos (0-1023)

void COMMAND_doCommand(uint16_t cid, int dataByte, int* data);
void COMMAND_setServo(uint16_t angle);

#endif 