/*
* motor.c
*
*/

//left motor
//Port 5 - backward
//Port 6 - forward
//right motor
//Port 3 - backward
//Port 4 - forward
#include "motor.h"

void goForward(){
	//left
	SET_BIT(PORTD, 6);
	CLR_BIT(PORTD, 5);
	//right
	SET_BIT(PORTD, 4);
	CLR_BIT(PORTD, 3);
}

void goBackward(){
	SET_BIT(PORTD, 5);
	CLR_BIT(PORTD, 6);
	
	SET_BIT(PORTD, 3);
	CLR_BIT(PORTD, 4);
}

void stopMotor(){
	//right
	CLR_BIT(PORTD, 3);
	CLR_BIT(PORTD, 4);
	//left
	CLR_BIT(PORTD, 5);
	CLR_BIT(PORTD, 6);
}

void turnLeft(){
	//stop left motor
	CLR_BIT(PORTD, 5);
	CLR_BIT(PORTD, 6);
	//go forward right motor
	SET_BIT(PORTD, 4);
	CLR_BIT(PORTD, 3);
}

void turnRight(){
	//stop right motor
	CLR_BIT(PORTD, 3);
	CLR_BIT(PORTD, 4);
	//go forward left motor
	SET_BIT(PORTD, 6);
	CLR_BIT(PORTD, 5);
}