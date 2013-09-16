#ifndef INCFILE1_H_
#define INCFILE1_H_

typedef enum {LEFT, RIGHT, UP, DOWN, NEUTRAL} direction;

int JOYSTICK_horPos();
int JOYSTICK_verPos();
direction JOYSTICK_direction();


#endif