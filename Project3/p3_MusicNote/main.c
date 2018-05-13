#include "music.h"

/*
_* for previous
_# for next
_0 to play selected song
_A to volume up
_B to volume down
_C to tempo up
_D to tempo down
*/

int main(void)
{
	ini_avr();
	ini_lcd();
	clr_lcd();

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
	songs l[3]={{"Jingle Bell", JingleBell, 51}, {"Happy Birthday", HappyBirthDay, 50}, {"Little Star", TwinkleLittleStar, 42}};
	
	unsigned int i = 0;
	unsigned int key = 0;
	
	sprintf(bufmsg, "Select Song");
	pos_lcd(0,0);
	puts_lcd2(bufmsg);
	
	clearBuf();
	sprintf(bufmsg, "%s", l[i].name);
	pos_lcd(1,0);
	puts_lcd2(bufmsg);
	
	while (1)
	{
		//default tempo and volume
		tempo = 1;
		volume = 1;
		
		key = get_key();
		wait_avr(200);
		if(key == 13){
			(i == 0) ? i = 2 : --i;
			clrLine(1);
			sprintf(bufmsg, "%s", l[i].name);
			pos_lcd(1,0);
			puts_lcd2(bufmsg);
		}
		else if(key == 15){
			(i == 2) ? i = 0 : ++i;
			clrLine(1);
			sprintf(bufmsg, "%s", l[i].name);
			pos_lcd(1,0);
			puts_lcd2(bufmsg);
		}
		else if(key == 14){
			play_song(l[i]);
			clr_lcd();
			
			clearBuf();
			sprintf(bufmsg, "Select Song");
			pos_lcd(0,0);
			puts_lcd2(bufmsg);
			
			clearBuf();
			sprintf(bufmsg, "%s", l[i].name);
			pos_lcd(1,0);
			puts_lcd2(bufmsg);
		}
	}
}
