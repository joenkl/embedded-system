/*
* music.c
*
* Created: 5/9/2018 9:53:28 PM
*  Author: khadb
*/
#include "avr.h"
#include "music.h"

typedef struct Notes{
	unsigned int freq;
	unsigned int duration;
} note;

void wait_avrMicro(unsigned long microsec)
{
	TCCR0 = 2;
	while (microsec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 8) * 0.000001);
		SET_BIT(TIFR, TOV0);
		WDR();
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}

void play_song(note *song, int songDuration){
	
	for (volatile unsigned int i = 0; i < songDuration; ++i){
		play_note(song[i].freq, song[i].duration);
		wait_avrMicro(100);
	}
}

void play_note(int freq, int duration){
	SET_BIT(DDRB, 3);
	int k = duration * freq;
	
	for (volatile int i = 0; i < k; ++i){
		SET_BIT(PORTB, 3);
		wait_avrMicro(freq);
		CLR_BIT(PORTC, 3);
		wait_avrMicro(freq);
	}
}