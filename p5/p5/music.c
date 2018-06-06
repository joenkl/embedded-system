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

void clearBuf(){
	sprintf(bufmsg,"                 ");
}

void clrLine(unsigned int r){
	clearBuf();
	pos_lcd(r,0);
	puts_lcd2(bufmsg);
}

void play_song(songs song){
	clr_lcd();
	
	//display song name
	clearBuf();
	sprintf(bufmsg, "%s", song.name);
	pos_lcd(0,0);
	puts_lcd2(bufmsg);
	
	//temp and volume
	clearBuf();
	sprintf(bufmsg, "V: %d ", volume);
	pos_lcd(1,0);
	puts_lcd2(bufmsg);
	
	clearBuf();
	sprintf(bufmsg, "T: %d ", tempo);
	pos_lcd(1,8);
	puts_lcd2(bufmsg);
	
	unsigned int key = 0;
	char change = 0;
	for (volatile unsigned int i = 0; i < song.duration; ++i){
		key = get_key();
		wait_avrMicro(5);
		if(key){
			switch(key){
				case 4: if(volume < 4){++volume; change = 1;} break;	//volumeUp key A
				case 8: if(volume > 1){--volume; change = 1;} break;	//volumeDown key B
				case 12: if(tempo < 10){++tempo; change = 1;} break;	//tempoUp key C
				case 16: if(tempo > 1){--tempo; change = 1;} break;		//tempoDown key D
				default: break;
			}
			
			if(change){
				clearBuf();
				sprintf(bufmsg, "%d ", volume);
				pos_lcd(1,3);
				puts_lcd2(bufmsg);
				
				clearBuf();
				sprintf(bufmsg, "%d ", tempo);
				pos_lcd(1,11);
				puts_lcd2(bufmsg);
			}
		}
		
		play_note(song.melody[i].freq, song.melody[i].duration);
		wait_avrMicro(100); //wait 1ms
	}
}

void play_note(unsigned int freq, float duration){
	SET_BIT(DDRB, 3);
	//each wait is 10us
	//duration = 1s = 100 000
	//k = duration * 8 * 10000 because duration is multiple of 8
	//tempo is increasing from .1 to 2
	int k = duration * 8 * 10000 / ((float)(tempo+10)/10) / freq;
	
	//change volume
	unsigned int Th = freq * (volume / 5.0);
	unsigned int Tl = freq - Th;
	
	
	for (int i = 0; i < k; ++i){
		SET_BIT(PORTB, 3);
		wait_avrMicro(Th); //TH
		CLR_BIT(PORTB, 3);
		wait_avrMicro(Tl); //TL
	}
}