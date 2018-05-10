/*
*
*
* Author : khadb, luankn
*/
#include "stdio.h"
#include "avr.h"
#include "lcd.h"
#include "keypad.h"
#include "music.h"

char bufmsg[17];

int main(void)
{
	note JingleBell[51]={
		{E,Q},{E,Q},{E,H},{E,Q},{E,Q},{E,H},{E,Q},{G,Q},{C,Q + EI},{D,EI},
		{E,H},{F,Q},{F,Q},{F,Q},{F,EI},{F,Q},{E,Q},{E,Q},{E,EI},{E,EI},
		{E,Q},{D,Q},{D,Q},{E,Q},{D,H},{G,H},{E,Q},{E,Q},{E,H},{E,Q},{E,Q},{E,H},
		{E,Q},{G,Q},{C,Q+EI},{D,EI},{E,W},{F,Q},{F,Q},{F,Q},{F,Q},{F,Q},
		{F,Q},{E,Q},{E,EI},{E,EI},{G,Q},{G,Q},{F,Q},{D,Q},{C,W}
	};
	
	note HappyBirthDay[50]={
		{A,EI},{A,EI},{B,Q},{A,Q},{D,Q},{Cs,H},
		{A,EI},{A,EI},{B,Q},{A,Q},{E,Q},{D,H},
		{A,EI},{A,EI},{A,Q},{Fs,Q},{D,Q},{Cs,Q},{B,Q},
		{G,EI},{G,EI},{Fs,Q},{D,Q},{E,Q},{D,H},
			
		{A,EI},{A,EI},{B,Q},{A,Q},{D,Q},{Cs,H},
		{A,EI},{A,EI},{B,Q},{A,Q},{E,Q},{D,H},
		{A,EI},{A,EI},{A,Q},{Fs,Q},{D,Q},{Cs,Q},{B,Q},
		{G,EI},{G,EI},{Fs,Q},{D,Q},{E,Q},{D,H},
	};
	
	note TwinkleLittleStar[42]={
		{D,Q},{D,Q},{A,Q},{A,Q},{B,Q},{B,Q},{A,H},{G,Q},{G,Q},{Fs,Q},{Fs,Q},{E,Q},{E,Q},{D,H},
		{A,Q},{A,Q},{G,Q},{G,Q},{Fs,Q},{Fs,Q},{E,H},{A,Q},{A,Q},{G,Q},{G,Q},{Fs,Q},{Fs,Q},{E,H},
		{D,Q},{D,Q},{A,Q},{A,Q},{B,Q},{B,Q},{A,H},{G,Q},{G,Q},{Fs,Q},{Fs,Q},{E,Q},{E,Q},{D,H}
	};
	
	/* Replace with your application code */
	ini_avr();
	ini_lcd();
	clr_lcd();

	
	while (1)
	{
		puts_lcd2("Welcome");
		int n = get_key();
		wait_avr(5);
		if(n == 1){
			puts_lcd2("Jingle Bell");
			play_song(JingleBell, 51);
		} 
		
		if(n == 2){
			puts_lcd2("Happy Birthday");
			play_song(HappyBirthDay, 50);
		}
		
		if(n == 3){
			puts_lcd2("Twinkle Little Star");
			play_song(TwinkleLittleStar, 42);
		}
	}
}
