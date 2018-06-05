/*
* ultrasonic.c
*
*/

#include "ultrasonic.h"

unsigned int timerOverFlow = 0;

ISR(TIMER1_OVF_vect){
	++timerOverFlow;
}

void ini_ultrasonic(){
	//Ultrasonic connection
	//D6 = echo using ICP port
	//D7 = trig
	SET_BIT(DDRD, 7);
	CLR_BIT(DDRD, 6);
}

void wait_us(unsigned long microsec)
{
	TCCR0 = 2;
	while (microsec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 8) * 0.00001);
		SET_BIT(TIFR, TOV0);
		WDR();
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}


unsigned int getDistance(){
	unsigned long count;
	float distance;
	
	SET_BIT(PORTD, 7); //trigger Trig Pin
	wait_us(1);	//wait 10us
	CLR_BIT(PORTD, 7); //clear bit
	
	TCNT1 = 0;
	TCCR1B = 0x41;
	TIFR = 1 << ICF1; //clear ICP flag
	TIFR = 1 << TOV1; //clear Timer Overflow flag
	
	//wait for echo HIGH
	while((TIFR & (1 << ICF1)) == 0);
	TCNT1 = 0;
	TCCR1B = 0x01; //Capture on falling edge
	TIFR = 1<<ICF1; //Clear ICP flag
	TIFR = 1<<TOV1; //Clear TOF
	timerOverFlow = 0;
	
	//wait for echo LOW
	while((TIFR & (1 <<ICF1)) == 0);
	count = ICR1 + (65535 * timerOverFlow);

	//timer gets incremented after 0.125 us time elapse.
	//= 17150 x (TIMER value) x 0.125 x 10^-6 cm
	//= 0.125 x (TIMER value)/58.30 cm
	//= (TIMER value) / 466.47 cm
	distance = (double)count / 466.47;
	
	return distance;
}