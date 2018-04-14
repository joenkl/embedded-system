#include <avr/io.h>
#include "avr.h"


#define WAITTIME 500
void ini_avr(void)
{
  //Define PORTA and input
  PORTA = 0x00;
  DDRA = 0x00;

  //Define PORTB and output
  PORTB = 0x00;
  DDRB = 0x01;

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
  //init
  ini_avr();

	
  while(1){
	  if (!GET_BIT(PINB,1)){
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
	  }
	  
  }
}
