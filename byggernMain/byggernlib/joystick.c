#include "adc.h"
#include <avr/io.h>
#include "joystick.h"

int JOYSTICK_horPos()
{
	char pos = ADC_read(1);
	return (int)((((int) pos) * 200.0) / 256.0) - 100.0;
}

int JOYSTICK_verPos()
{
	char pos = ADC_read(0);
	return (int)((((int)pos) * 200.0) / 256.0) - 100.0;
}

int GLIDER_rightPos()
{
	char pos = ADC_read(2);
	return (int)((((int)pos) * 200.0) / 256.0) - 100.0;
}

int GLIDER_leftPos()
{
	char pos = ADC_read(3);
	return (int)((((int)pos) * 200.0) / 256.0) - 100.0;
}



direction JOYSTICK_direction()
{
	int horPos = JOYSTICK_horPos();
	int verPos = JOYSTICK_verPos();
	int horPos2 = horPos * horPos;
	int verPos2 = verPos * verPos;
	
	if((horPos > 0) && (horPos2 >= verPos2)) return RIGHT;
	if((verPos > 0) && (verPos2 >= horPos2)) return UP;
	if((horPos < 0) && (horPos2 >= verPos2)) return LEFT;
	if((verPos < 0) && (verPos2 >= horPos2)) return DOWN;
	
	return NEUTRAL;
}