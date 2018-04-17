/*
	Joseph Luan Nguyen 50997891
	Kha Bui 18187793
*/

#include <avr/io.h>
#include "avr.h"

#define WAITTIME 500
void ini_avr(void)
{
	SET_BIT(DDRB, 0);
	CLR_BIT(DDRB, 1);
}

void wait_avr(unsigned short msec)
{
	TCCR0 = 3;
	while (msec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.001);
		SET_BIT(TIFR, TOV0);
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}

int main (void)
{
	/*init*/
	ini_avr();

	while(1){
		
		//Blinking LED with EXTERNAL CRYSTAL
		//Using: Medium Freq: Start-up time: 16 CK + 64ms
		if (!GET_BIT(PINB, 1))
		{
			SET_BIT(PORTB, 0);
			wait_avr(WAITTIME);
			CLR_BIT(PORTB, 0);
			wait_avr(WAITTIME);
		}
		else
		CLR_BIT(PORTB, 0);
		
		//BLinking LED Without external crystal
		/*if (!GET_BIT(PINB,1)){
		volatile long i = 0;
		SET_BIT(PORTB, 0);
		while (i < 14000){
		++i;
		}
		i =0;
		CLR_BIT(PORTB, 0);
		while (i < 14000){
		++i;
		}
		
		}
		else {
		CLR_BIT(PORTB, 0);
		}*/
	}
}
