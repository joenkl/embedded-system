/*
 * voltmeter.c
 *
 */ 

#include "voltmeter.h"

//reset display
void ini_meter(){
	currVol = 0.00;
	avgVol = 0.00;
	minVol = 0.00;
	maxVol = 0.00;
	count = 0;
	total = 0;
	
	clr_lcd();
	
	pos_lcd(0,0);
	sprintf(bufMsg, "Cur:_.__ Avg:_.__");
	puts_lcd2(bufMsg);
	
	pos_lcd(1,0);
	sprintf(bufMsg, "Min:____ Max:____");
	puts_lcd2(bufMsg);
}

//start to measure voltage
//return a value read from port
unsigned float startMeter(){
	return 0.0;
}

void displayCurrVol(){
	sprintf(bufChar, "%.2f", currVol);
	pos_lcd(4,0);
	puts_lcd2(bufChar);
}

void displayAvgVol(){
	sprintf(bufChar, "%.2f", avgVol);
	pos_lcd(11,0);
	puts_lcd2(bufChar);
}

void displayMinVol(){
	sprintf(bufChar, "%.2f", minVol);
	pos_lcd(4,0);
	puts_lcd2(bufChar);
}

void displayMaxVol(){
	sprintf(bufChar, "%.2f", maxVol);
	pos_lcd(11,0);
	puts_lcd2(bufChar);
}