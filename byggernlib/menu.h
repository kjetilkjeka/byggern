#ifndef MENU_H_
#define MENU_H_

typedef struct menu menu;

struct menu
{
	char* names[8];
	menu* submenu[8];
	menu* up;
	int length; // max 8
	
};

void MENU_init(menu *currentMenu);
void MENU_print(int selected, menu currentMenu);
void MENU_pollJoystick(int *selected, menu **currentMenu);
void MENU_start();


#endif