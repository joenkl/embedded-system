/*
dcmotorpwm lib 0x02

copyright (c) Davide Gironi, 2012

Released under GPLv3.
Please refer to LICENSE file for licensing information.
*/

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "dcmotorpwm.h"

volatile uint8_t dcmotorpwm_speedactual = 0;
volatile uint8_t dcmotorpwm_direction = 0;

#if DCMOTORPWM_SLOWENABLED == 1
volatile uint8_t dcmotorpwm_slowenabled = 0;
volatile uint8_t dcmotorpwm_slowspeedtarget = 0;
volatile uint8_t dcmotorpwm_slowincrease = 0;
volatile uint16_t dcmotorpwm_slowacceleration = 0;
volatile uint16_t dcmotorpwm_slowaccelerationstep = 0;
#endif

/*
 * init a motor
 */
void dcmotorpwm_init() {
	//set ports
	DCMOTORPWM_DDR |= (1<<DCMOTORPWM_PIN1);
	DCMOTORPWM_DDR |= (1<<DCMOTORPWM_PIN2);

	ICR1 = DCMOTORPWM_ICR1; //fixed top value

	TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<COM1A0) | (1<<COM1B0); //inverting mode

	TCCR1A |= (1<<WGM11); //fast pwm mode on top of ICR1
	TCCR1B |= (1<<WGM13) | (1<<WGM12);

	TCCR1B |= DCMOTORPWM_PRESCALER; //set prescaler

	#if DCMOTORPWM_SLOWENABLED == 1
	TIMSK = (1 << TOIE1); //enable interrupt
	#endif
}

/*
 * stop the motor
 */
void dcmotorpwm_stop() {
	TCCR1A |= (1<<COM1A0);
	OCR1A = DCMOTORPWM_ICR1;
	TCCR1A |= (1<<COM1B0);
	OCR1B = DCMOTORPWM_ICR1;
}

/*
 * make the motor go forward
 * set speed (0..100)
 */
void dcmotorpwm_forward(uint8_t speed) {
	//limit velocity
	if(speed == 0) {
		//stop the motor
		dcmotorpwm_stop();
	} else {
		if(speed >= 100) {
			//set to max speed
			TCCR1A &= ~(1<<COM1A0);
			OCR1A = DCMOTORPWM_ICR1;
		} else {
			//set orc
			uint16_t orctop = ((uint32_t)(DCMOTORPWM_ICR1 - DCMOTORPWM_MINVEL) * (uint32_t)(speed - 1) / (uint32_t)(100 - 1)) + DCMOTORPWM_MINVEL;
			TCCR1A |= (1<<COM1A0);
			OCR1A = DCMOTORPWM_ICR1 - orctop;
		}
		TCCR1A |= (1<<COM1B0);
		OCR1B = DCMOTORPWM_ICR1;
	}
}

/*
 * make the motor go backward
 * set speed (0..100)
 */
void dcmotorpwm_backward(uint8_t speed) {
	if(speed == 0) {
		//stop the motor
		dcmotorpwm_stop();
	} else {
		//limit velocity
		if(speed >= 100) {
			//set to max speed
			TCCR1A &= ~(1<<COM1B0);
			OCR1B = DCMOTORPWM_ICR1;
		} else {
			//set orc
			uint16_t orctop = ((uint32_t)(DCMOTORPWM_ICR1 - DCMOTORPWM_MINVEL) * (uint32_t)(speed - 1) / (uint32_t)(100 - 1)) + DCMOTORPWM_MINVEL;
			TCCR1A |= (1<<COM1B0);
			OCR1B = DCMOTORPWM_ICR1 - orctop;
		}
		TCCR1A |= (1<<COM1A0);
		OCR1A = DCMOTORPWM_ICR1;
	}
}


/*
 * stop the motor
 */
void dcmotorpwm_gostop() {
	#if DCMOTORPWM_SLOWENABLED == 1
	//disable slow
	dcmotorpwm_slowenabled = 0;
	#endif

	dcmotorpwm_speedactual = 0;
	//update motor speed
	dcmotorpwm_stop();
}

/*
 * make the motor spin
 * set direction ('F'|'B') and speed from and to (0..100)
 * non slow mode
 */
void dcmotorpwm_go(uint8_t direction, uint8_t speed) {
	if(direction == DCMOTORPWM_DIRECTIONFORWARD || direction == DCMOTORPWM_DIRECTIONBACKWARD) {
		if(speed >= 100) //sanitize speed
			speed = 100;

		#if DCMOTORPWM_SLOWENABLED == 1
		//disable slow
		dcmotorpwm_slowenabled = 0;
		#endif

		//set direction
		dcmotorpwm_direction = direction;
		//set speed
		dcmotorpwm_speedactual = speed;
		//update motor speed
		if(direction == DCMOTORPWM_DIRECTIONFORWARD) {
			dcmotorpwm_forward(speed);
		} else if(direction == DCMOTORPWM_DIRECTIONBACKWARD) {
			dcmotorpwm_backward(speed);
		}
	}
}

/*
 * get the actual motor speed
 */
uint8_t dcmotorpwm_getspeed() {
	return dcmotorpwm_speedactual;
}

/*
 * get the actual motor direction
 */
uint8_t dcmotorpwm_getdirection() {
	return dcmotorpwm_direction;
}

#if DCMOTORPWM_SLOWENABLED == 1

/*
 * make the motor spin
 * set direction ('F'|'B'), speed from and to (0..100) and acceleration (0..100)
 * slow mode
 */
void dcmotorpwm_goslow(uint8_t direction, uint8_t speedactual, uint8_t speedtarget, uint8_t acceleration) {
	if(direction == DCMOTORPWM_DIRECTIONFORWARD || direction == DCMOTORPWM_DIRECTIONBACKWARD) {
		if(acceleration > 100) //sanitize acceleration
			acceleration = 100;
		if(acceleration < 1)
			acceleration = 1;
		if(speedactual == 0) //sanitize speed
			speedactual = 1;
		if(speedactual >= 100) //sanitize speed
			speedactual = 100;
		if(speedtarget >= 100) //sanitize speed
			speedtarget = 100;
		//do not use slow mode if acceleration is zero or speed are the same
		if(speedactual == speedtarget || acceleration == 0) {
			dcmotorpwm_go(direction, speedtarget);
		} else {
			//enabled slow
			dcmotorpwm_slowenabled = 0;
			//set pwm direction
			if(speedactual < speedtarget)
				dcmotorpwm_slowincrease = 1;
			else
				dcmotorpwm_slowincrease = 0;
			//set speed
			dcmotorpwm_speedactual = speedactual;
			dcmotorpwm_slowspeedtarget = speedtarget;
			//set direction
			dcmotorpwm_direction = direction;
			//set acceleration
			dcmotorpwm_slowacceleration = (uint32_t)DCMOTORPWM_ACCELLERATIONMAX - 1 - ((uint32_t)acceleration - 1) * ((uint32_t)DCMOTORPWM_ACCELLERATIONMAX - 1) / ((uint32_t)100 - 1) + 1;
			dcmotorpwm_slowaccelerationstep = 0;
			//enabled slow
			dcmotorpwm_slowenabled = 1;
		}
	}

}

/*
 * stop the motor spin
 * slow mode
 */
void dcmotorpwm_gostopslow(uint8_t acceleration) {
	dcmotorpwm_goslow(dcmotorpwm_direction, dcmotorpwm_speedactual, 0, acceleration);
}

/*
 * update the motor acceleration
 */
void dcmotorpwm_updateacceleration() {
	if(dcmotorpwm_slowenabled) {
		dcmotorpwm_slowaccelerationstep++;
		//do acceleration speed
		if(dcmotorpwm_slowaccelerationstep == dcmotorpwm_slowacceleration) {

			//update speed
			dcmotorpwm_slowaccelerationstep = 0;
			if(!dcmotorpwm_slowincrease) {
				if(dcmotorpwm_speedactual > dcmotorpwm_slowspeedtarget) {
					//decrement speed
					dcmotorpwm_speedactual--;
				}
			} else {
				if(dcmotorpwm_speedactual < dcmotorpwm_slowspeedtarget) {
					//increment speed
					dcmotorpwm_speedactual++;
				}
			}
			//update motor speed
			if(dcmotorpwm_direction == DCMOTORPWM_DIRECTIONFORWARD) {
				dcmotorpwm_forward(dcmotorpwm_speedactual);
			} else if(dcmotorpwm_direction == DCMOTORPWM_DIRECTIONBACKWARD) {
				dcmotorpwm_backward(dcmotorpwm_speedactual);
			}
			//disable slow
			if(dcmotorpwm_speedactual == dcmotorpwm_slowspeedtarget || dcmotorpwm_speedactual == 0)
				dcmotorpwm_slowenabled = 0;
		}
	}

}

/*
 * motor interrupt
 */
ISR(TIMER1_OVF_vect) {
	static uint16_t slowstep = 0;

	slowstep++;
	if(slowstep == DCMOTORPWM_1MSSTEP) {
		//we are here every 1ms
		slowstep = 0;

		dcmotorpwm_updateacceleration(); //update acceleration
	}
}

#endif



