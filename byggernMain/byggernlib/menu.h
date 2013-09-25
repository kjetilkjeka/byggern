#ifndef MENU_H_
#define MENU_H_

typedef struct menu menu;

struct menu
{
	char* names[8];
	menu* submenu[8];
	menu* up;
	
};

//void MENU_init(menu *mainMenu);
void MENU_print(int selected, menu currentMenu);
void MENU_pollJoystick(int *selected, menu *currentMenu);


#endif