#include "spi.h"

void MCP_reset(void)
{
	SPI_CS(1);
	SPI_Transmit(0b11000000);
	SPI_CS(0);
}

char MCP_read(char adr)
{
	SPI_CS(1);
	SPI_Transmit(0b00000011);
	SPI_CS(0);
	SPI_CS(1);
	SPI_Transmit(adr);
	char data = SPI_trasmit(0x00);
	SPI_CS(0);
	return data;
}


char MCP_readRxBuffer(int location)
{
	if(location < 0 || location > 3)
		return '\0';
		
	
	SPI_CS(1);
	SPI_Transmit(0b10010000 + location*2)
	char data = SPI_Transmit(0x00);
	SPI_CS(0);
	return data;
}


void MCP_write(char adr, char data)
{
	SPI_CS(1);
	SPI_Transmit(0b00000010);
	SPI_Transmit(adr);
	SPI_Transmit(data);
	SPI_CS(0);
}


void MCP_loadTxBuffer(int abc)
{
	// not suported yet
	return;
}

void MCP_RTS(int nnn)
{
	SPI_CS(1);
	if(nnn < 0 || nnn > 7)
		return;
		
	SPI_Transmit(0b10000000 + nnn);
	
}

void MCP_readStatus()
{
	// no support yet
	return;
}

void MCP_rxStatus()
{
	// no support yet
	return;
}

void MCP_bitModify()
{
	// no support yet
	return;
}

