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


