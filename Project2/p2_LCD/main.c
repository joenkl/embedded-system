/*
* p2_LCD.c
*
* Created: 4/17/2018 3:56:51 PM
* Author : khadb
*/

#include "avr.h"
#include "lcd.h"


unsigned int is_pressed(int r, int c){
	switch(r){
		case 0:
		CLR_BIT(PORTC, 0);
		break;
		case 1:
		CLR_BIT(PORTC, 1);
		break;
		case 2:
		CLR_BIT(PORTC, 2);
		break;
		case 3:
		CLR_BIT(PORTC, 3);
		break;
	}
	
	switch(c){
		case 0:
		if(GET_BIT(PINC, 4))
		return 0;
		else
		return 1;
		break;
		case 1:
		if(GET_BIT(PINC, 5))
		return 0;
		else
		return 1;
		break;
		case 2:
		if(GET_BIT(PINC, 6))
		return 0;
		else
		return 1;
		break;
		case 3:
		if(GET_BIT(PINC, 7))
		return 0;
		else
		return 1;
		break;
	}
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
	DDRC = 0xF0; //set C0-3 input, C4-7 output
	
	DDRB = 0x08; //set B3 output
	
	/* Replace with your application code */
	while (1)
	{
		int num = get_key();
		if(num){
			SET_BIT(PORTB, 3);
		} else 
			CLR_BIT(PORTB, 3);
	}
}

