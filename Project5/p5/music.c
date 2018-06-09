#include "music.h"

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

void play_note(unsigned int freq, float duration){
	SET_BIT(DDRC, 3);
	//each wait is 10us
	//duration = 1s = 100 000
	//k = duration * 8 * 10000 because duration is multiple of 8
	//tempo is increasing from .1 to 2
	int k = duration * 8 * 10000 / ((float)(tempo+10)/10) / freq;
	
	for (int i = 0; i < k; ++i){
		SET_BIT(PORTC, 3);
		wait_avrMicro(freq); //TH
		CLR_BIT(PORTC, 3);
		wait_avrMicro(freq); //TL
	}
}