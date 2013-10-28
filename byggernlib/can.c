#include "MCP2515.h"
#include <avr/delay.h>
#include <avr/io.h>
#include <stdint.h>

void CAN_init()
{
	printf("CAN is initializing\n\r");
	// enabling the interupt pin
	// for atmega 162
	//MCUCR &= 0b11110000; // interupt on low
	//GICR = GICR | 0b01000000; // enable interupt on INT0
	
	/*
	//for atmega 128
	EICRB |= (1<<ISC51);
	EICRB &= 0xff ^ (1<<ISC50);
	EIMSK |= (1<<CANINT); //CANINT er INT4
	*/
	
	
	// for usb thingy
	EICRB |= (1<<ISC01);
	EIMSK |= (1<<CANINT);
	
	
	
	MCP_reset();
	
	
		
	MCP_write(CANINTE, (1<<RX0IE)|(1<<RX1IE)); //only interupt on RX
	
	MCP_write(CANINTF, 0x00);
	
	CAN_initRecieve();
	
	CAN_modeSelect(NORMAL_MODE);
	
	printf("CAN initialization is complete \n\r");
}

void CAN_modeSelect(int mode)
{
		
	MCP_bitModify(CANCTRL,0b11100000, mode);
	while((MCP_read(CANCTRL) & 0b11100000)^mode); // waiting for CAN to have entered correct mode
	printf("mode selected \n\r");
	
}

void CAN_initRecieve()
{
	MCP_bitModify(RXB0CTRL, 0b01100100, 0b01100100); //some receive filter stuff
	MCP_bitModify(RXB1CTRL, 0b01100000, 0b01100000);
}


void CAN_setID(int buffer, uint16_t cid)
{
	if(cid < 0 || cid > 0b11111111111)
	{
		printf("ID not allowed, %u", cid);
		return; //cid is out of range
	}	
	
	char SIDH = cid >> 3;
	char SIDL = (cid & 0b111) << 5;
	
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


void CAN_send(uint16_t cid, int dataByte, int* data)
{
	int buffer = 0;
	
	if(buffer < 0 || buffer > 2)
	{
		printf("Transmit buffer, %u, does not exist\n\r", buffer);
		return;
	}

	// wait for the TXBnCTRL.TXREQ to be cleared
	while((MCP_read(TXB0CTRL + 16*buffer) & (1<<TXREQ)));
	
	CAN_setID(buffer, cid);
	CAN_setData(buffer, dataByte, data);
		
	MCP_RTS(1<<buffer);
}

int CAN_readID(int buffer)
{
	char a = MCP_read(RXB0SIDH + 16*buffer);
	char b = MCP_read(RXB0SIDL + 16*buffer);
	
	int cid=((int)b>>5);
	cid =cid+ ((int)a<<3);
	
	return cid;
}

int CAN_recieve(int * dataByte, int * data)
{
	
	int buffer = 0;	
	while((MCP_read(CANINTF) & (1<<(RX0IF + buffer))) == 0) // wait untill the interupt flag in the buffer is one
		buffer = (buffer+1) %2 ;
	
	
	int cid= CAN_readID(buffer);
	*dataByte = (MCP_read(RXB0DLC + 16*buffer)&0b1111);
	
	for(int i = 0; i < *dataByte; i++)
	{
		data[i] = MCP_read(RXB0D0 + 16*buffer + i);
	}
	
	
	return cid;
	
}
