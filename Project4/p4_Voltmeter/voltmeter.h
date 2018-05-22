/*
* voltmeter.h
*/

#include "avr.h"
#include "stdio.h"
#include "keypad.h"
#include "lcd.h"

char bufMsg[17];
char bufChar[4];

unsigned short currVol;
unsigned short maxVol;
unsigned short minVol;
unsigned short avgVol;
unsigned int total;
unsigned int count;

unsigned short get_A2D();
void ini_meter();
void displayCurrVol();
void displayAvgVol();
void displayMinVol();
void displayMaxVol();