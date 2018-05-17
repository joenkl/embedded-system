/*
 * voltmeter.c
 *
 */ 

#include "voltmeter.h"

//convert analog to digital
float A2D(unsigned int analogVal){
	
}

//reset display
void ini_meter(){
	currVol = 0.00;
	avgVol = 0.00;
	minVol = 0.00;
	maxVol = 0.00;
	
	pos_lcd(0,0);
	sprintf(bufMsg, "V: %.2f A: %.2f", currVol, avgVol);
	puts_lcd2(bufMsg);
	
	pos_lcd(1,0);
	sprintf(bufMsg, "L: %.2f H: %.2f", minVol, maxVol);
	puts_lcd2(bufMsg);
}

//start to measure voltage
void startMeter(){
	
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