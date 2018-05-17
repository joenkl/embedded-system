/*
* voltmeter.h
*/

#include "avr.h"
#include "stdio.h"

char bufMsg[17];
unsigned char bufChar[4];

	float currVol;
	float maxVol;
	float minVol;
	float avgVol;

float A2D(unsigned int analogVal);
void ini_meter();
void startMeter();
void displayCurrVol();
void displayAvgVol();
void displayMinVol();
void displayMaxVol();