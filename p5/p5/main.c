/*
* p5_SomethingFun.c
*
*/

#include <avr/io.h>
#include "stdio.h"
#include "avr.h"
#include "motor.h"
#include "lcd.h"
#include "ultrasonic.h"


int main(void)
{
	ini_avr();
	ini_lcd();
	ini_ultrasonic();
	
	sei(); //enable global interrupt
	TIMSK = (1<<TOIE1); //Enable Timer1 overflow interrupt
	TCCR1A = 0; //Set all bit to zero Normal operation
	
	unsigned int v;
	
	char bufChar[17];

	while(1){
		v = getDistance();
		sprintf(bufChar, "%dcm", v);
		pos_lcd(0,0);
		puts_lcd2(bufChar);
		wait_avr(1000);
		clr_lcd();
	}
}

