#include <avr/io.h>
#include "IR.h"

/*
void IR_init()
{
	EICRB |= (1<<ISC71);
	EICRB &= 0xff ^ (1<<ISC70);
	EIMSK |= (1<<INT7); //CANINT er INT4

}
*/


void IR_init()

{
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	
	ADMUX = ((1 << REFS0) | (1 << ADLAR));
	
	ADCSRA |= ((1 << ADFR) | (1 << ADEN) | (1 << ADSC) | (1 << ADIE));

}



int IR_count(void)
{
	static int count = 0;
	count++;
	return count;
}