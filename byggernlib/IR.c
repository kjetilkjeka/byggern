#include <avr/io.h>
#include "IR.h"

void IR_init()
{
	EICRB |= (1<<ISC71);
	EICRB &= 0xff ^ (1<<ISC70);
	EIMSK |= (1<<INT7); //CANINT er INT4

}

int IR_count(void)
{
	static int count = 0;
	count++;
	return count;
}