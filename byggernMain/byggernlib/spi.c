#include <avr/io.h>
#include "spi.h"

void SPI_Init(void)
{
	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<MOSI)|(1<<SCK)|(1<<SS);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	SPI_CS(0);
}


char SPI_Transmit(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

void SPI_CS(int ss)
{
	//printf("SS is: %u \n\r", SS);
	if(ss)
	{
		PORTB = PINB&(~(1<<SS)); //set SS low		
	} else 
	{
		PORTB = PINB|(1<<SS); // set SS high again	
	}
}