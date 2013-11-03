#ifndef MOTOR_H_
#define MOTOR_H_


#include <avr/io.h>
#include <stdio.h>



#define DDRMJ1 DDRC
#define DDRMJ2 DDRA
#define PORTMJ1 PORTC
#define PORTMJ2 PORTA
#define PINMJ1 PINC
#define PINMJ2 PINA

#define MOTOR_DIR PC3
#define MOTOR_EN PC4
#define MOTOR_SEL PC5
#define MOTOR_RST PC6
#define MOTOR_OE PC7

#define DO7 PA0
#define DO6 PA1
#define DO5 PA2
#define DO4 PA3
#define DO3 PA4
#define DO2 PA5
#define DO1 PA6
#define DO0 PA7





void MOTOR_init();
int MOTOR_readEncoder();
void MOTOR_dir(uint8_t dir);
void MOTOR_setSpeed(uint8_t speed);
void MOTOR_enable(uint8_t enable);
void MOTOR_updatePos();
int MOTOR_getPos();


#endif