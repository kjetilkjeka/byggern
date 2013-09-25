
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include "byggernlib/serialio.h"
//#include "byggernlib/sram.h"
#include "byggernlib/extmem.h"
#include "byggernlib/adc.h"
#include "byggernlib/joystick.h"
#include "byggernlib/oled.h"
#include "byggernlib/menu.h"



void MAIN_init(void)
{
	USART_Init(MYUBRR);
	EXTMEM_init();
	OLED_init();
	//MENU_init();

	fdevopen(USART_Transmit, USART_Receive);
	//fdevopen(OLED_writeChar, USART_Receive); //probably unsafe
	sei();
}



int main(void)
{	
	MAIN_init();
	
	menu mainMenu;
	menu gamesMenu;
	menu *currentMenu;
	//MENU_init(&mainMenu);
	
	mainMenu.names[0] = "names0";
	mainMenu.names[1] = "asdasdnames1";
	mainMenu.names[2] = "Games";
	mainMenu.names[3] = "names3";
	mainMenu.names[4] = "names4";
	mainMenu.names[5] = "names5";
	mainMenu.names[6] = "names6";
	mainMenu.names[7] = "names7";
	
	
	mainMenu.submenu[2] = &gamesMenu;
	gamesMenu.names[0] = "PingPong";
	gamesMenu.names[1] = "snake";
	gamesMenu.names[2] = "";
	gamesMenu.names[3] = "";
	gamesMenu.names[4] = "";
	gamesMenu.names[5] = "";
	gamesMenu.names[6] = "";
	gamesMenu.names[7] = "";
	
	
	currentMenu = &mainMenu;
	
	int selected = 0;
	
	MENU_print(selected, *currentMenu);
	
	while(1)
	{
		
		MENU_pollJoystick(&selected, currentMenu);
		MENU_print(selected, *currentMenu);
		_delay_ms(1000);
		
		
	}		
}




ISR(USART0_RXC_vect)
{
	USART_Transmit(USART_Receive());
	PORTB = 0;
}

