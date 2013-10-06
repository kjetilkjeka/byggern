#include "MCP2515.h"


void CAN_init()
{
	MCP_write(CANCTRL, 0b01000110) // enable controller in loopback mode
}

void CAN_send()
{
	// wait for the TXBnCTRL.TXREQ to be cleared
	while(MCP_read(TXB0CTRL) & (1<<TXREQ));


	// write stuff to regsiters
	MCP_write(TXB0SIDH, 0b00001111);
	MCP_write(TXB0SIDL, 0x00);
	MCP_write(TXB0DLC, 0x01);
	MCP_write(TXB0D0, 0b01010101);
	
	// set TXB0CTRL.TXREQ
	
	


	
	
	// init CANINTE:TXlnE 
	
}

void CAN_recieve()
{
	
}