#include "font_5x7.h"
#include "serialio.h"
#include <avr/pgmspace.h>

volatile char *OLEDcommand = 0x1000;
volatile char *OLEDdata = 0x1200;


void write_c(char c)
{
	*OLEDcommand = c;
	
}

void OLED_writeData(char c)
{
	*OLEDdata = c;
}

void OLED_writeChar(char c)
{
		
	for(int j = 0; j < 5; j++)
	{
		OLED_writeData(pgm_read_byte(&myfont[(int)c - 32][j]));
	}
		
}

void OLED_setPage(int page)
{
	if(page >= 0 && page < 8)
	{
		write_c(0xB0 + page);	
	}
}

void OLED_setCursor(int cursor)
{
	if(cursor >= 0 && cursor < 128)
	{
		write_c(0x00 + (cursor & 0b00001111));
		write_c(0x10 + (cursor & 0b11110000));
	}		
}

void OLED_blankScreen(void)
{
	for(int i = 0; i < 8; i++)
	{
		write_c(0x00);
		write_c(0x10);
		write_c(0xB0 + i);
		for(int j = 0; j < 128; j++)
		{		
			OLED_writeData(0x00);
		}
	}		
}


void OLED_writeString(char* s)
{
	int i = 0;
	while(s[i] != (char)0)
	{
		OLED_writeChar(s[i]);
		i++;		
	}
}




void OLED_init(void)
{
	write_c(0xae); // display off
	write_c(0xa1); //segment remap
	write_c(0xda); //common pads hardware: alternative
	write_c(0x12);
	write_c(0xc8); //common output scan direction:com63~com0
	write_c(0xa8); //multiplex ration mode:63
	write_c(0x3f);
	write_c(0xd5); //display divide ratio/osc. freq. mode
	write_c(0x80);
	write_c(0x81); //contrast control
	write_c(0x50);
	write_c(0xd9); //set pre-charge period
	write_c(0x21);
	write_c(0x20); //Set Memory Addressing Mode
	write_c(0x02); //Set page adressing mode
	write_c(0xdb); //VCOM deselect level mode
	write_c(0x30);
	write_c(0xad); //master configuration
	write_c(0x00);
	write_c(0xa4); //out follows RAM content
	write_c(0xa6); //set normal display
	write_c(0xaf); // display on
	
	
}
