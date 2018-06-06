/*
* p5_SomethingFun.c

#Bluetooth module
D1 - module Rx connect to MC Tx
D0 - module Tx connect to MC Rx

#ultrasonic connection
D6 - ICP - echo
D5 - trig

#motor connection
B3 - OC0 - pwm motor speed
C4 - left
C5 - left
C6 - right
C7 - right

#operation:
1 - goForward
2 - goBackward
3 - turnLeft
4 - turnRight
5 - speedUp
6 - slowDown
7 - change mode
*/

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "USART_RS232_H_file.h"		/* include USART library */
#include "stdio.h"
#include "avr.h"
#include "motor.h"
#include "lcd.h"
#include "music.h"
#include "remote.h"
#include "ultrasonic.h"

unsigned short horn(float distance){
	if(distance <= 5.0){
		play_note(A, W);
		return 1;
	}
	return 0;
}

void manualMode(){
	char cmd;
	unsigned short speed = 0;
	motorSpeed(speed);
	
	while(1){
		cmd = USART_RxChar();
		if (cmd == 's'){
			break;
		}
		
		switch(cmd){
			case '1':
			if(horn(getDistance()) == 0)
			{
				goForward();
				wait_avr(250);
				stopMotor();
			}
			break;
			case '2':
			if(horn(getDistance()) == 0)
			{
				goBackward();
				wait_avr(250);
				stopMotor();
			}
			break;
			case '3':
			turnLeft();
			break;
			case '4':
			turnRight();
			break;
			case '5': //speed up
			if(speed < 220){
				speed += 25;
			}
			motorSpeed(speed);
			break;
			case '6': //slow down
			if (speed > 25){
				speed -= 25;
			}
			motorSpeed(speed);
			
			default:
			stopMotor();
			break;
		}
	}
}

void autoMode(){
	char cmd;
	unsigned short speed = 0;
	unsigned short num;
	motorSpeed(speed);
	
	while(1){
		cmd = USART_RxChar();
		
		if (cmd == 'c'){
			break;
		}
		
		if(horn(getDistance()) == 1){
			stopMotor();
			num = rand() % 2;
			
			num == 0? turnLeft() : turnRight();
		} else {
			goForward();
		}
	}
}

int main(void)
{
	ini_avr();
	ini_motor();
	ini_ultrasonic();
	USART_Init(9600);
	
	//Ultrasonic
	sei(); //enable global interrupt
	TIMSK = (1<<TOIE1); //Enable Timer1 overflow interrupt
	TCCR1A = 0; //Set all bit to zero Normal operation
	
	char cmd;
	unsigned short mode = 0; //manual by default
	
	while(1){
		cmd = USART_RxChar();
		
		if(cmd == '7'){
			if(mode == 0){
				mode = 1;
			} else if (mode == 1){
				mode = 0;
			}
		}
		
		if (mode == 1){
			autoMode();
		} 
		
		manualMode();
	}
}

