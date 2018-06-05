/*
 * ultrasonic.h
 *
 */ 

#ifndef __ultrasonic__
#define __ultrasonic__

#include "avr.h"

void ini_ultrasonic();
void wait_avrMicro(unsigned long microsec);
unsigned int getDistance();
#endif