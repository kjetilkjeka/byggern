#include <avr/io.h>
#define F_CPU 8e6
#include <avr/delay.h>

void SOLENOID_init()
{
	DDRF |= (1<<PF0);

}

void SOLENOID_fire()
{
	PORTF |= (1<<PF0);
	_delay_ms(70);
	PORTF &= ~(1<<PF0);
}