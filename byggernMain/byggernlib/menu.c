#include "oled.h"
#include "joystick.h"
#include <avr/delay.h>
#include <avr/pgmspace.h>
#include "menu.h"



/*
void MENU_init(menu *mainMenu)
{
	(*mainMenu).names[0] = "nasdasdames0";
	(*mainMenu).names[1] = "names1";
	(*mainMenu).names[2] = "names2";
	(*mainMenu).names[3] = "names3";
	(*mainMenu).names[4] = "names4";
	(*mainMenu).names[5] = "names5";
	(*mainMenu).names[6] = "names6";
	(*mainMenu).names[7] = "names7";
	
}
*/

void MENU_pollJoystick(int *selected, menu *currentMenu)
{
	int menuLength = 8;
	
	int verPos = JOYSTICK_verPos();
	int horPos = JOYSTICK_horPos();
	//printf("hor joystick pos: %d ver pos: %d \r\n", horPos, verPos);
	
	int threashold = 5;
	
	if(horPos > threashold){
		currentMenu = ((*currentMenu).submenu[2]);
		printf("selected: %d", *selected);
		printf((*currentMenu).names[*selected]);
	}		
	
	
	if(verPos > threashold) *selected = *selected - 1 % menuLength;
	if(verPos < -threashold) *selected = *selected + 1 % menuLength;
	
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