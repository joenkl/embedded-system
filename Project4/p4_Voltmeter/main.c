/*
* p4_VoltMeter.c
*
* Created: 5/24/2018 3:13:46 PM
* Author : Kha Bui, Joseph Luan Nguyen
*/

#include <avr/io.h>
#include "stdio.h"
#include "avr.h"
#include "keypad.h"
#include "lcd.h"

char bufMsg[17];

void ini_meter(){
	sprintf(bufMsg, "Ins:____Avg:____");
	pos_lcd(0,0);
	puts_lcd2(bufMsg);
	
	sprintf(bufMsg, "Min:____Max:____");
	pos_lcd(1,0);
	puts_lcd2(bufMsg);
}

unsigned short get_A2D(){
	ADMUX |= (1<<REFS0);
	SET_BIT(ADCSRA, 7); //Set ADEN
	SET_BIT(ADCSRA, 6); //Set ADSC start conversion
	while(GET_BIT(ADCSRA, 6)); //wait to finish measure
	
	return ADC;
}

int main(void)
{
	ini_avr();
	ini_lcd();
	ini_meter();
	float curr = 0.0;
	float avg = 0.0;
	float min = 0.0;
	float max = 0.0;
	float total = 0.0;
	unsigned short count = 0;

	while (1)
	{
		if(get_key() == 4){
			while(1){
				if(get_key() == 8){
					ini_meter();
					curr = 0.0;
					avg = 0.0;
					min = 0.0;
					max = 0.0;
					total = 0.0;
					count = 0;
					break;
				}
				
				curr = (float)get_A2D() / 1023.0 * 5.0;
				++count;
				
				if(count == 1){
					min = curr;
					max = curr;
				}

				if (curr < min){
					min = curr;
				}
				
				if(curr > max){
					max = curr;
				}
				
				total += curr;
				avg = total / (float)count;
				
				sprintf(bufMsg, "Ins:%.2fAvg:%.2f", curr, avg);
				pos_lcd(0,0);
				puts_lcd2(bufMsg);
				
				sprintf(bufMsg, "Min:%.2fMax:%.2f", min, max);
				pos_lcd(1,0);
				puts_lcd2(bufMsg);
				
				wait_avr(500);
			}
		}
	}
}

