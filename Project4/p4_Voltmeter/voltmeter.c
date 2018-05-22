/*
* voltmeter.c
*
*/

#include "voltmeter.h"
/*
ADC interface in ATMEGA32 include all PORTA (0-7)
It is using AREF as reference voltage when set ADMUX to REFS0

Procedure:
Input read 0 - 5V from Port A0 (which is ADC)
when ADC turn on 0-5V will be converted into 0 to 1023= 2^10 because our ADC is 10-bit with 8 registers

example: 0V input = 0(Digital value)
		 5V input = 1023
		 2.5V input = 512
		 
For reference read: http://maxembedded.com/2011/06/the-adc-of-the-avr/
*/

//inital meter
void ini_meter(){
	//Set ADC register
	//Using AREF port as reference value for voltage
	//Set ADMUX to REFS0 = Internal Vref turned off and using AREF port
	ADMUX |= (1 << REFS0) 
	
	//Enable ADC 
	//ADEN = ADC Enable
	ADCSRA	|= (1 << ADEN);
	
	//Set default value
	currVol = 0.00;
	avgVol = 0.00;
	minVol = 0.00;
	maxVol = 0.00;
	count = 0;
	total = 0;
	
	clr_lcd();
	
	pos_lcd(0,0);
	sprintf(bufMsg, "Cur:____ Avg:____");
	puts_lcd2(bufMsg);
	
	pos_lcd(1,0);
	sprintf(bufMsg, "Min:____ Max:____");
	puts_lcd2(bufMsg);
}

unsigned short get_A2D(){
	//Start Conversion by write 1 to ADSC bit in ADCSRA
	//ADSC = ADC Start Conversion
	ADCSRA |= (1 << ADSC);
	
	//This bit stays high as long as the conversion is in progress and will be cleared by hardware
	//when the conversion is completed.
	//Wait till the ADSC is turned off
	while(ADCSRA & (1 << ADSC));
	
	return ADC;
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