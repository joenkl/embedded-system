/*
* motor.c
*
*/

//left motor
//Port C5 - backward
//Port C4 - forward
//right motor
//Port C7 - backward
//Port C6 - forward
#include "motor.h"

void ini_motor(){
	DDRC = 0xF0;
	PORTC = 0x00;
}

void goForward(){
	//left
	SET_BIT(PORTC, 4);
	CLR_BIT(PORTC, 5);
	//right
	SET_BIT(PORTC, 6);
	CLR_BIT(PORTC, 7);
}

void goBackward(){
	SET_BIT(PORTC, 5);
	CLR_BIT(PORTC, 4);
	
	SET_BIT(PORTC, 7);
	CLR_BIT(PORTC, 6);
}

void stopMotor(){
	//right
	CLR_BIT(PORTC, 4);
	CLR_BIT(PORTC, 5);
	//left
	CLR_BIT(PORTC, 6);
	CLR_BIT(PORTC, 7);
}

void turnLeft(){
	//stop left motor
	CLR_BIT(PORTC, 4);
	CLR_BIT(PORTC, 5);
	//go forward right motor
	SET_BIT(PORTC, 6);
	CLR_BIT(PORTC, 7);
	
	wait_avr(250);
	stopMotor();
}

void turnRight(){
	//stop right motor
	CLR_BIT(PORTC, 6);
	CLR_BIT(PORTC, 7);
	//go forward left motor
	SET_BIT(PORTC, 4);
	CLR_BIT(PORTC, 5);
	
	wait_avr(250);
	stopMotor();
}

//connect to B3
void motorSpeed(unsigned int speed){
		SET_BIT(DDRB, 3);
		TCCR0 = 0x75;
		TIMSK = 0x00;
		OCR0 = (255 - speed);
}