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

#buzzer
C3

#Led Matrix
B5 - DIN
B4 - CS
B7 - CLK

#operation:
1 - goForward
2 - goBackward
3 - turnLeft
4 - turnRight
5 - slown down
6 - speed up
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
#include "LedMatrix.h"


char sad[8] = {
	0b10000001,
	0b01000010,
	0b00100100,
	0b00011000,
	0b00011000,
	0b00100100,
	0b01000010,
	0b10000001
};


char smile01[8] = {
	0b00001000,
	0b00010000,
	0b00100000,
	0b00100000,
	0b00100000,
	0b00100000,
	0b00010000,
	0b00001000
};

unsigned short horn(float distance){
	if(distance <= 15.0){
		stopMotor();
		play_note(278, Q);
		wait_avr(10);
		play_note(278, Q);
		
		if(distance <= 10.0){
			image(sad);
			update_display();
			
			goBackward();
			wait_avr(1000);
			stopMotor();
			
			image(smile01);
			update_display();
		}
		USART_SendString("\nObject Detected");
		return 1;
	}
	return 0;
}

int main(void)
{
	ini_avr();
	ini_motor();
	ini_ultrasonic();
	USART_Init(9600);
	max7219_init();

	image(smile01);
	update_display();

	//Ultrasonic
	sei(); //enable global interrupt
	TIMSK = (1<<TOIE1); //Enable Timer1 overflow interrupt
	TCCR1A = 0; //Set all bit to zero Normal operation
	

	char cmd;
	unsigned short speed = 255;
	unsigned short count;
	
	char bufC[10];
	
	while(1){
		cmd = USART_RxChar();
		wait_avr(100);

		switch(cmd){
			case '0':
			USART_SendString("\nDistance: ");
			sprintf(bufC,"%d", (int)(getDistance()));
			USART_SendString(bufC);
			break;
			case '1':
			if(horn(getDistance()) == 0)
			{
				USART_SendString("\nForward");
				goForward();
				wait_avr(1000);
				stopMotor();
			}
			break;
			case '2':
			USART_SendString("\nReverse");
			goBackward();
			wait_avr(1000);
			stopMotor();
			break;
			case '3':
			turnLeft();
			USART_SendString("\nTurn left");
			break;
			
			case '4':
			turnRight();
			USART_SendString("\nTurn right");
			break;
			
			case '5': //Slow Down
			if(speed < 230){
				speed = speed + 25;
			}
			sprintf(bufC, "Speed: %d", speed);
			USART_SendString(bufC);
			break;
			
			case '6': //Speed Up
			if (speed > 25){
				speed = speed - 25;
			}
			sprintf(bufC, "Speed: %d", speed);
			USART_SendString(bufC);
			motorSpeed(speed);
			break;
			
			case '7':
			count = 0;
			for(;;){
				++count;
				if(horn(getDistance()) == 0){
					goForward();
					} else{
					
					stopMotor();
					wait_avr(250);
					(rand() % 2) == 0 ? turnLeft() : turnRight();
				}
				sprintf(bufC, "\n%d", count);
				USART_SendString(bufC);

				if(count > 3000){
				break;}
			}
			break;
			
			case 'a':
			image(sad);
			update_display();
			break;
			
			case 'b':
			image(smile01);
			update_display();
			break;
			
			default:
			stopMotor();
			break;
		}
	}
}


