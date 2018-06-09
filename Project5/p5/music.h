#ifndef __music__
#define __music__

#include "avr.h"
#include <stdio.h>

//     note delay(freq)
#define A 114
#define As 108
#define B 101
#define C 96
#define Cs 90
#define D 85
#define Ds 81 
#define E 76
#define F 72
#define Fs 68
#define G 64
#define Gs 60

//      duration
#define W 1
#define H 0.5
#define Q 0.25
#define EI 0.125

//message
char bufmsg[17];
//default temp
unsigned int tempo;
//default volume
unsigned int volume;

typedef struct{
	unsigned int freq;
	float duration;
} note;

typedef struct {
	char name[17];
	note *melody;
	unsigned int duration;
}songs;

void wait_avrMicro(unsigned long microsec);
void play_note(unsigned int freq, float duration);

#endif