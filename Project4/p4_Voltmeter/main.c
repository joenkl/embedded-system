/*
 * p4_Voltmeter.c
 *
 */ 

#include <avr/io.h>
#include "avr.h"
#include "lcd.h"
#include "keypad.h"
#include "voltmeter.h"

int main(void)
{
    ini_avr();
	ini_lcd();
	ini_meter();
	int val;
	
    while (1) 
    {
		//start meter
		if(get_key() == 12){
			while(1){
				if(get_key() == 16){
					ini_meter();
					break;
				}
				++count;
				//A2D is 1023 max at 5Volt
				val = (startMeter()/ 1023.0 * 5.0)*100;
				
				if(count == 1){
					minVol = val;
					maxVol = val;
					currVol = val;
				}
				
				total += val;
				avgVol = (float)total/(float)count;
				
				displayAvgVol();
				displayCurrVol();
				displayMaxVol();
				displayMinVol();
				
				wait_avr(500);
			}
		}
		
		
    }
}

