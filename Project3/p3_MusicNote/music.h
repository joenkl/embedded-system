/*
 * music.h
 *
 * Created: 5/9/2018 10:03:40 PM
 *  Author: khadb
 */ 
#ifndef __music__
#define __music__

//     note delay(freq)
#define A 1135
#define As 1075
#define B 1010
#define C 955
#define Cs 900
#define D 850
#define Ds 805 
#define E 760
#define F 715
#define Fs 675
#define G 640
#define Gs 600

//      duration
#define WH 1
#define HF 1/2
#define QT 1/4
#define ET 1/8

void wait_avrMicro(unsigned long microsec);
void play_music();
void play_note(int freq, int duration);

#endif