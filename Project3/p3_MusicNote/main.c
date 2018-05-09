/*
*
*
* Author : khadb, luankn
*/
#include "stdio.h"
#include "avr.h"
#include "lcd.h"
#include "keypad.h"

char bufmsg[17];

void
wait_avrMicro(unsigned long microsec)
{
	TCCR0 = 2;
	while (microsec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 8) * 0.000001);
		SET_BIT(TIFR, TOV0);
		WDR();
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}


int main(void)
{
	/* Replace with your application code */
	ini_avr();
	ini_lcd();

	clr_lcd();

	/*init time*/
	//displayInfo();
	unsigned int i = 0;
	
	while (1)
	{
		sprintf(bufmsg, "%d", i);
		pos_lcd(0,0);
		puts_lcd2(bufmsg);
		//wait_avrMicro(1000000);
		//wait_avr(998);
		++i;
	}
}
