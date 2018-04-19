/*
* p2_LCD.c
*
* Created: 4/17/2018 3:56:51 PM
* Author : khadb
*/

#include "avr.h"
#include "lcd.h"


unsigned int is_pressed(int r, int c){
	if (!GET_BIT(PINC, c))
		return 1;
	else
		return 0;
}

unsigned int get_key(){
	int r,c;
	for(r = 0; r < 4; ++r){
		for(c = 0; c < 4; ++c){
			if (is_pressed(r,c))
			return r*4+c+1;
		}
	}
	return 0;
}


int main(void)
{
	DDRC = 0xF0; //set C0-3 input(column), C4-7 output(row)
	PORTC = 0x0F; //set C0-3 to high(column), C4-7 to low(row)
	DDRB = 0x08; //set B3 output
	
	/* Replace with your application code */
	while (1)
	{
		volatile int num = get_key();
		if(num != 0){
			SET_BIT(PORTB, 3);
			wait_avr(250);
			CLR_BIT(PORTB, 3);
			wait_avr(250);
		} else 
			CLR_BIT(PORTB, 3);
	}
}

