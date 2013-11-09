#include <avr/io.h>
#include <avr/delay.h>

#include "board.h"



int main()
{
	LEDPORT.DIR = 0xff;
	LEDPORT.OUT = 0b01010101;
	
	while(1)
	{
		
	}
}