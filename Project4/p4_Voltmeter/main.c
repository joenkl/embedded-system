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
	unsigned int val = 0;
	float temp = 0.0;
    while (1) 
    {
		//start meter
		if(get_key() == 12){
			while(1){
				//Reset meter
				if(get_key() == 16){
					ini_meter();
					break;
				}
				
				++count;
				//A2D is 1023 max at 5Volt
				val = (get_A2D()/ 1024.0 * 5.0);
				
				//1st time reading data
				if(count == 1){
					minVol = val;
					maxVol = val;
					currVol = val;
				}
				
				//Calculate min
				if (currVol < minVol){
					minVol = currVol;
				}
				
				//Calculate max
				if(currVol > maxVol){
					maxVol = currVol;
				}
				
				total += val;
				avgVol = total/(float)count;
				
				displayAvgVol();
				displayCurrVol();
				displayMaxVol();
				displayMinVol();
				
				//wait 500ms
				wait_avr(500);
			}
		}
		
		
    }
}

