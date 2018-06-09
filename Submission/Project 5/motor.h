/*
* motor.h
*
*/

#ifndef __motor__
#define __motor__
#include "avr.h"

void ini_motor();
void goForward();
void goBackward();
void stopMotor();
void turnLeft();
void turnRight();
void motorSpeed(unsigned int speed);

#endif