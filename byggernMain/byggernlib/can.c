#include "MCP2515.h"


void CAN_init()
{
	MCP_write(CANCTRL, 0b01010000); // enable controller in loopback mode
	printf ("CANCTRL: %u \r\n", MCP_read(CANCTRL));
	MCP_write(CANINTF, 0x00);
	printf ("CANINTF: %u \r\n", MCP_read(CANINTF));
	CAN_initRecieve();
}

void CAN_initRecieve()
{
	MCP_bitModify(RXB0CTRL, 0b01100100, 0b01100100); //some recieve filter stuff
	MCP_bitModify(RXB1CTRL, 0b01100000, 0b01100000);
}

void CAN_send()
{
	
	printf ("CANINTF: %u \r\n", MCP_read(CANINTF));
	// wait for the TXBnCTRL.TXREQ to be cleared
	while(!(MCP_read(TXB0CTRL) & (1<<TXREQ)));


	// write stuff to regsiters
	MCP_write(TXB0SIDH, 0b00001111);
	MCP_write(TXB0SIDL, 0x00);
	MCP_write(TXB0DLC, 0x00); // no data
	//MCP_write(TXB0D0, 0b01010101);
	
	MCP_bitModify(CANINTE, 1<<TX0IE, 0x00); // set the interupt off. (maybe put this in init?)
	
	// set TXB0CTRL.TXREQ
	MCP_RTS(1); // this function is weird	
	
	
}

int CAN_recieve()
{
	printf ("CANINTF: %u \r\n", MCP_read(CANINTF));
	while(!(MCP_read(CANINTF) & (1<<RX0IF)));
	
	// guess its just to read the buffers then
	char a = MCP_read(RXB0SIDH);
	char b = MCP_read(RXB0SIDL);
	
	printf ("CANINTF: %u \r\n", MCP_read(CANINTF));
	printf("char a is: %u, char b is %u: \n\r", a, b);
	
	MCP_bitModify(CANINTF, 1<<RX0IF, 0x00);
	
	int result = 0;
	
	result = result + ((int)b)>>5;
	result = result + ((int)a)<<3;
	
	return result;
	
	
}