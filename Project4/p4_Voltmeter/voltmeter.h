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
unsigned int count;
unsigned int total;

void ini_meter();
unsigned float startMeter();
void displayCurrVol();
void displayAvgVol();
void displayMinVol();
void displayMaxVol();