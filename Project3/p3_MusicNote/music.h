/*
 * music.h
 *
 * Created: 5/9/2018 10:03:40 PM
 *  Author: khadb
 */ 
#ifndef __music__
#define __music__

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
#define WHOLE 1
#define HALF 0.5
#define QUARTER 0.25
#define EIGHT 0.125

void wait_avrMicro(unsigned long microsec);
void play_music();
void play_note(unsigned int freq, float duration);

#endif