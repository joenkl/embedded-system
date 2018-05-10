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
	float duration;
} note;

void wait_avrMicro(unsigned long microsec)
{
	TCCR0 = 2;
	while (microsec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 8) * 0.00001);
		SET_BIT(TIFR, TOV0);
		WDR();
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}

void play_song(note *song, unsigned int songDuration){
	
	for (volatile unsigned int i = 0; i < songDuration; ++i){
		play_note(song[i].freq, song[i].duration);
		wait_avrMicro(100); //wait 1ms
	}
}

void play_note(unsigned int freq, float duration){
	SET_BIT(DDRB, 3);
	//each wait is 10us
	//duration = 1s = 100 000
	//k = duration * 8 * 10000 because duration is multiple of 8
	int k = duration * 8 * 10000 / freq;
	
	for (int i = 0; i < k; ++i){
		SET_BIT(PORTB, 3);
		wait_avrMicro(freq);
		CLR_BIT(PORTB, 3);
		wait_avrMicro(freq);
	}
}