#include "oled.h"
#include "joystick.h"
#include <avr/delay.h>
#include <avr/pgmspace.h>
#include "menu.h"
#include <stdlib.h>




void MENU_init(menu *currentMenu)
{
		for(int i = 0; i < 8; i++)
		{
			(*currentMenu).names[i] = "";
			(*currentMenu).submenu[i] = NULL;
		}
		(*currentMenu).up = NULL;
}


void MENU_pollJoystick(int *selected, menu **currentMenu)
{
	int menuLength = (**currentMenu).length;
	
	int verPos = JOYSTICK_verPos();
	int horPos = JOYSTICK_horPos();
	
	int threashold = 5;
	
	if(horPos > threashold){
		if((**currentMenu).submenu[*selected] != NULL)
		{
			*currentMenu = ((**currentMenu).submenu[*selected]);
			*selected = 0;
		} else 
		{
			printf("selected: %d\n\r", *selected);
		}			
	} else if(horPos < -threashold)
	{
		if((**currentMenu).up != NULL)
		{
			*currentMenu = ((**currentMenu).up);
		}		
	}
	
	
	if(verPos > threashold) *selected = (*selected + menuLength - 1) % menuLength;
	if(verPos < -threashold) *selected = (*selected + 1) % menuLength;
	
}	

void MENU_start()
{
	menu *currentMenu;
	
	
	menu mainMenu;
	MENU_init(&mainMenu);
	
	mainMenu.length = 3;
	mainMenu.names[0] = "names0";
	mainMenu.names[1] = "lol";
	mainMenu.names[2] = "Games";
	
	
	menu gamesMenu;
	MENU_init(&gamesMenu);
	gamesMenu.up = &mainMenu;
	
	mainMenu.submenu[2] = &gamesMenu;
	gamesMenu.length = 2;
	gamesMenu.names[0] = "PingPong";
	gamesMenu.names[1] = "snake";
	
	
	menu lolMenu;
	MENU_init(&lolMenu);
	lolMenu.length = 2;
	lolMenu.names[0] = "lol0";
	lolMenu.names[1] = "lol1";
	lolMenu.up = &mainMenu;
	
	mainMenu.submenu[1] = &lolMenu;
	
	currentMenu = &mainMenu;
	
	int selected = 0;
	
	MENU_print(selected, *currentMenu);
	
	while(1)
	{
		
		MENU_pollJoystick(&selected, &currentMenu);
		MENU_print(selected, *currentMenu);
		_delay_ms(1000);
	}
}


void MENU_print(int selected, menu currentMenu)
{
		
	OLED_blankScreen();
	
	for(int i = 0; i < 8; i++)
	{
		
		OLED_setPage(i);
		OLED_setCursor(0);
		OLED_writeString(currentMenu.names[i], (i==selected));
	}			
}