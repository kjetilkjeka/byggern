#include "MCP2515.h"
#include <avr/delay.h>


void CAN_init()
{
	MCP_reset();
	printf("CAN is initilizing\n\r");	
	
	MCP_write(CANINTF, 0x00);
	MCP_bitModify(CANINTE, 1<<TX0IE, 0x00); // set the interupt off. (maybe put this in init?)
	CAN_initRecieve();
	
	CAN_modeSelect(010);
	
	printf("CAN initialization is compelete \n\r");
}

void CAN_modeSelect(int mode)
{
	switch (mode)
	{
		case 010: //loopback mode
			MCP_bitModify(CANCTRL,0b11100000, 0b01000000);
			while((MCP_read(CANCTRL) & 0b11100000)^0b01000000); // waiting for CAN to have entered loopback mode
			break;
		default:
			printf("mode select failed");
	}		
}

void CAN_initRecieve()
{
	MCP_bitModify(RXB0CTRL, 0b01100100, 0b01100100); //some recieve filter stuff
	MCP_bitModify(RXB1CTRL, 0b01100000, 0b01100000);
}

void CAN_setID(int buffer, uint16_t ID)
{
	if(ID < 0 || ID > 0b11111111111)
	{
		printf("ID not allowed, %u", ID);
		return; //ID is out of range
	}	
	
	char SIDH = ID >> 3;
	char SIDL = (ID & 0b111) << 5;
	
	MCP_write(TXB0SIDH + 16*buffer, SIDH);
	MCP_write(TXB0SIDL + 16*buffer, SIDL);
}



void CAN_setData(int buffer, int dataByte, int* data)
{
	
	if(dataByte < 0 || dataByte > 8)
	{
		printf("wrong num of data bytes: %u", dataByte);
		return; // to many dataBytes
	}		
	
	MCP_write(TXB0DLC + 16*buffer, dataByte);
	
	for(int i = 0; i < dataByte; i++)
	{
		MCP_write(TXB0D0 + 16*buffer + i, data[i]);
	}
}


void CAN_send(uint16_t ID, int dataByte, int* data)
{
	int buffer = 0;
	
	if(buffer < 0 || buffer > 2)
	{
		printf("Transmit buffer, %u, does not exist\n\r", buffer);
		return;
	}

	// wait for the TXBnCTRL.TXREQ to be cleared
	while((MCP_read(TXB0CTRL + 16*buffer) & (1<<TXREQ)));
	
	CAN_setID(buffer, ID);
	CAN_setData(buffer, dataByte, data);
		
	MCP_RTS(1<<buffer);
}

int CAN_readID(int buffer)
{
	char a = MCP_read(RXB0SIDH + 16*buffer);
	char b = MCP_read(RXB0SIDL + 16*buffer);
	
	int ID =((int)b>>5);
	ID = ID + ((int)a<<3);
	
	return ID;
}

int CAN_recieve(int * dataByte, int * data)
{
	int buffer = 0;
	if(buffer < 0 || buffer > 1)
	{
		printf("Recieve buffer, %u, does not exist\n\r", buffer);
		return;
	}
	
	
	while((MCP_read(CANINTF) & (1<<RX0IF)) == 0); // wait untill the interupt flag in the buffer is one
	
	
	
	int ID = CAN_readID(buffer);
	*dataByte = (MCP_read(RXB0DLC + 16*buffer)&0b1111);
	
	for(int i = 0; i < *dataByte; i++)
	{
		data[i] = MCP_read(RXB0D0 + 16*buffer + i);
	}
	
	

	MCP_bitModify(CANINTF, 1<<RX0IF, 0x00); // turn off the interupt flag after reading
	return ID;
	
}