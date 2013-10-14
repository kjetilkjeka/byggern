#ifndef CAN_H_
#define CAN_H_


void CAN_init();
void CAN_send(uint16_t ID, int dataByte, int* data);
int CAN_recieve(int* dataByte, int* data);


#endif 