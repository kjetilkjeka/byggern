#ifndef MOTOR_H_
#define MOTOR_H_

#define PORTMJ1 PORTC
#define PORTMJ2 PORTF
#define PINMJ1 PINC
#include <avr/io.h>
#include <stdio.h>


#define PINMJ2 PINF
#define DDRMJ1 DDRC
#define DDRMJ2 DDRF

#define MOTOR_DIR PC3
#define MOTOR_EN PC4
#define MOTOR_SEL PC5
#define MOTOR_RST PC6
#define MOTOR_OE PC7

#define DO7 PF0
#define DO6 PF1
#define DO5 PF2
#define DO4 PF3
#define DO3 PF4
#define DO2 PF5
#define DO1 PF6
#define DO0 PF7





void MOTOR_init();
void MOTOR_dir(uint8_t dir);
void MOTOR_setSpeed(uint8_t speed);
void MOTOR_enable(uint8_t enable);


#endif