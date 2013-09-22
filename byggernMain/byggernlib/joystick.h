#ifndef JOYSTICK_H_
#define JOYSTICK_H_

typedef enum {LEFT, RIGHT, UP, DOWN, NEUTRAL} direction;

int JOYSTICK_horPos();
int JOYSTICK_verPos();
int GLIDER_rightPos();
int GLIDER_leftPos();
direction JOYSTICK_direction();


#endif