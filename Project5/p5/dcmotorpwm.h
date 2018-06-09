/*
dcmotorpwm lib 0x02

copyright (c) Davide Gironi, 2012

Released under GPLv3.
Please refer to LICENSE file for licensing information.
*/


#ifndef DCMOTORPWM_H
#define DCMOTORPWM_H
//set motor port
#define DCMOTORPWM_DDR DDRB
#define DCMOTORPWM_PORT PORTB
#define DCMOTORPWM_PIN1 PB1
#define DCMOTORPWM_PIN2 PB2

//set minimum velocity, depends on the motor
//must be less than DCMOTORPWM_ICR1
#define DCMOTORPWM_MINVEL 120

//freq = 1 / time
//pulse freq = FCPU / prescaler * ICR1
// 20000 = 8000000 / (1 * 400)
//try to set ICR1 as high as possible
#define DCMOTORPWM_ICR1 400
#define DCMOTORPWM_PRESCALER (1 << CS10)

//enable or disable slow start functions
#define DCMOTORPWM_SLOWENABLED 1

#if DCMOTORPWM_SLOWENABLED == 1
//the more ICR1 is bigger, the more you can step your speed
//DCMOTORPWM_1MSSTEP = pulse freq /1000
#define DCMOTORPWM_1MSSTEP 20
//minimum and maximim acceleration perdiod, set upon your preferences
#define DCMOTORPWM_ACCELLERATIONMAX 1200 //set maximum acceleration period, increase to slower acceleration
#endif

//direction
#define DCMOTORPWM_DIRECTIONFORWARD 'F'
#define DCMOTORPWM_DIRECTIONBACKWARD 'B'

//functions
extern void dcmotorpwm_init();
extern void dcmotorpwm_go(uint8_t direction, uint8_t speed);
extern void dcmotorpwm_gostop();
extern uint8_t dcmotorpwm_getspeed();
extern uint8_t dcmotorpwm_getdirection();
#if DCMOTORPWM_SLOWENABLED == 1
extern void dcmotorpwm_updateacceleration();
extern void dcmotorpwm_goslow(uint8_t direction, uint8_t speedactual, uint8_t speedtarget, uint8_t acceleration);
extern void dcmotorpwm_gostopslow(uint8_t acceleration);
#endif

#endif
