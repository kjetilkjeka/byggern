#include <avr/io.h>
#ifndef F_CPU
#define F_CPU 8E6
#endif
#include <avr/delay.h>

void SERVO_init()
{
	DDRE = (1<<PE3);
	
	
	ICR3 = 20000; // this is 16bit must fix safe initialization
	OCR3A = 1500;
	
	// this register is correct
	
	TCCR3A = (1<<COM3A1)|(1<<WGM31); // toggle OC1A on comperator match (check wether its toggle or set)
	TCCR3B = (1<<WGM32)|(1<<WGM33)|(1<<CS31);
	
}

void SERVO_set(uint16_t posision)
{
	posision &= 0b1111111111; // mask out higher bits (only want values from 0 to 1023);
	OCR3A = 988 + posision;
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