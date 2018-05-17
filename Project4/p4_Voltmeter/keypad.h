#ifndef __keypad__
#define __keypad__

#include "avr.h"

unsigned int is_pressed(int r, int c);
unsigned int get_key();

#endif