#include <avr/io.h>
#ifndef F_CPU
#define F_CPU 8E6
#endif
#include <avr/delay.h>
#include <avr/interrupt.h>

void SERVO_init()
{
	
	DDRB |= (1<<PB6);
	
	cli();
	ICR1 = 20000; // this is 16bit must fix safe initialization
	OCR1B = 1500;
	
	// this register is correct
	
	TCCR1A = (1<<COM1B1)|(1<<WGM11); // toggle OC1B on comperator match (check wether its toggle or set)
	
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS11);
	printf("lol1\n\r");
	sei();
	printf("lol2\n\r");
}

void SERVO_set(uint16_t posision)
{
	cli();
	posision &= 0b1111111111; // mask out higher bits (only want values from 0 to 1023);
	OCR1B = 988 + posision;
	sei();
}


void SERVO_test()
{
	
	for(int i = 0; i < 1023; i++)
	{
		SERVO_set(i);
		_delay_ms(10);
	}
	
	for(int i = 0; i < 1023; i++)
	{
		SERVO_set(1023-i);
		_delay_ms(10);
	}
	
}