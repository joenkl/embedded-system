#ifndef main
#define main

unsigned char numToChar(int num);
unsigned int is_pressed(int r, int c);
unsigned int get_key();
void increaseDay();
void increaseTime();
char isLeapYear();
void setDay(char day, char month, char year);
void setTime(char hour, char minutes, char second);
void civilToMilitaryTime();
void militaryToCivilTime();

#endif