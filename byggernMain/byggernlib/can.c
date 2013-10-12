#include "MCP2515.h"
#include <avr/delay.h>


void CAN_init()
{
	MCP_reset();
	MCP_write(CANCTRL, 0b01010000); // enable controller in loopback mode
	printf ("CANCTRL: %u \r\n", MCP_read(CANCTRL));
	MCP_write(CANINTF, 0x00);
	printf ("CANINTF: %u \r\n", MCP_read(CANINTF));
	MCP_bitModify(CANINTE, 1<<TX0IE, 0x00); // set the interupt off. (maybe put this in init?)
	CAN_initRecieve();
}

void CAN_initRecieve()
{
	MCP_bitModify(RXB0CTRL, 0b01100100, 0b01100100); //some recieve filter stuff
	printf ("RXB0CTRL: %u \r\n", MCP_read(RXB0CTRL));
	MCP_bitModify(RXB1CTRL, 0b01100000, 0b01100000);
}

void CAN_send(uint16_t ID, int dataByte, int* data)
{
	// need to figure out the SIDH and SIDL based on ID (expect 11 bit ID)
	if(ID < 0 || ID > 0b11111111111)
		return; //ID is out of range
	if(dataByte < 0 || dataByte > 8)
		return; // to many dataBytes
		
	for(int i = 0; i < 9; i++)
	{
		printf("result[%d] is: %d \n\r", i, data[i]);
	}
	
	
	char SIDH = ID >> 3;
	char SIDL = (ID & 0b111) << 5; 
	printf("SIDL and SIDH are: %d, %d \r\n", SIDL, SIDH);
	
	
	// wait for the TXBnCTRL.TXREQ to be cleared
	while((MCP_read(TXB0CTRL) & (1<<TXREQ)));
	


	// write stuff to regsiters
	MCP_write(TXB0SIDH, SIDH);
	MCP_write(TXB0SIDL, SIDL);
	
	
	
	// ///////////////////////////////////////////////
	// Everything to this point works in this function
	// ///////////////////////////////////////////////
	
	
	
	MCP_write(TXB0DLC, dataByte);
	
	for(int i = 0; i < dataByte; i++)
		MCP_write(TXB0D0+i, data[i]);
	
	
	printf ("TXB0CTRL: %u \r\n", MCP_read(TXB0CTRL));
	
	// set TXB0CTRL.TXREQ
	MCP_bitModify(CANINTE, 1<<TX0IE, 0xff); // set the interupt off. (maybe put this in init?)
	//MCP_RTS(1); // this function is weird
	MCP_bitModify(TXB0CTRL, (1<<TXREQ), (1<<TXREQ));
	printf ("TXB0CTRL: %u \r\n", MCP_read(TXB0CTRL));	
	
	
}

int* CAN_recieve()
{
	printf ("CANINTF: %u \r\n", MCP_read(CANINTF));
	
	while((MCP_read(CANINTF) & (1<<RX0IF)) == 0);
	
	printf ("CANINTF: %u \r\n", MCP_read(CANINTF));
	
	
	// guess its just to read the buffers then
	char a = MCP_read(RXB0SIDH);
	char b = MCP_read(RXB0SIDL);
	
	printf ("CANINTF: %u \r\n", MCP_read(CANINTF));
	printf("char a is: %u, char b is %u: \n\r", a, b);
	
	MCP_bitModify(CANINTF, 1<<RX0IF, 0x00);
	
	int ID = 0;
	
	ID = ID + ((int)b>>5);
	ID = ID + ((int)a<<3);

	volatile int data[9]; //waste of space to have lots of ints, well, well.
	data[0] = ID;
	for(int i = 1; i < 9; i++)
	{
		data[i] = MCP_read((RXB0D0-1 + i));
		
	}
	
	for(int i = 0; i < 9; i++)
	{
		printf("result[%d] is: %d \n\r", i, data[i]);
	}

	return data;
	
}