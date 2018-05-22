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
float total;
unsigned int count;

unsigned short get_A2D();
void ini_meter();
void displayCurrVol();
void displayAvgVol();
void displayMinVol();
void displayMaxVol();