#include "font_5x7.h"
#include "serialio.h"

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

void OLED_writeChar(int i)
{
	
	//i = 33;
	
	USART_Transmit(i);
	
	
	OLED_writeData(myfont[i][0]);
	OLED_writeData(myfont[i][1]);
	OLED_writeData(myfont[i][2]);
	OLED_writeData(myfont[i][3]);
	OLED_writeData(myfont[i][4]);
	
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
	write_c(0x00);
	write_c(0xdb); //VCOM deselect level mode
	write_c(0x30);
	write_c(0xad); //master configuration
	write_c(0x00);
	write_c(0xa4); //out follows RAM content
	write_c(0xa6); //set normal display
	write_c(0xaf); // display on
	
	
}
