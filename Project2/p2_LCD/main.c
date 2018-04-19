/*
* p2_LCD.c
*
* Created: 4/17/2018 3:56:51 PM
* Author : khadb
*/

#include "avr.h"
#include "lcd.h"

unsigned char numToChar(int num){
	switch(num){
		case 1: return '1'; break;
		case 2: return '2'; break;
		case 3: return '3'; break;
		case 4: return 'A'; break;
		case 5: return '4'; break;
		case 6: return '5'; break;
		case 7: return '6'; break;
		case 8: return 'B'; break;
		case 9: return '7'; break;
		case 10: return '8'; break;
		case 11: return '9'; break;
		case 12: return 'C'; break;
		case 13: return '*'; break;
		case 14: return '0'; break;
		case 15: return '#'; break;
		case 16: return 'D'; break;
		default: return 0; break;
	}
}

//Need to fix
unsigned int is_pressed(int r, int c){
	c += 4;
	/*//Set row to output and STRONG 0
	SET_BIT(DDRC, r);
	CLR_BIT(PORTC, r);
	
	//Set column to input and WEAK 1
	CLR_BIT(DDRC, c);
	SET_BIT(PORTC, c);*/
	
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
	DDRC = 0x0F;
	PORTC = 0xF0;
	DDRB = 0x08; //set B3 output
	ini_lcd();
	/* Replace with your application code */
	while (1)
	{
		//Set to default
		//DDRC = 0x00;
		//PORTC = 0x00;
		
		//Keypad
		volatile unsigned int num = get_key();
		wait_avr(100); // wait to release button
		if(num){
			for (volatile int i = 0; i < num; ++i){
				SET_BIT(PORTB, 3); // Set LED On
				wait_avr(100);
				CLR_BIT(PORTB, 3);
				wait_avr(100);
			}
			//clear
			clr_lcd();
			//wait_avr(500);
			put_lcd(numToChar(num));

		} else
		{
			CLR_BIT(PORTB, 3);
		}
		
	}
}

