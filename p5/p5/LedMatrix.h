/*
 * LedMatrix.h
 *
 * Created: 6/6/2018 5:13:24 PM
 *  Author: khadb
 */ 

#ifndef __LEDMATRIX__
#define __LEDMATRIX__

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


#define CLK_HIGH()  PORTB |= (1<<PB7)
#define CLK_LOW()   PORTB &= ~(1<<PB7)
#define CS_HIGH()   PORTB |= (1<<PB4)
#define CS_LOW()    PORTB &= ~(1<<PB4)
#define DATA_HIGH() PORTB |= (1<<PB5)
#define DATA_LOW()  PORTB &= ~(1<<PB5)
#define INIT_PORT() DDRB |= (1<<PB4) | (1<<PB5) | (1<<PB7)

void spi_send(char data);
void max7219_writec(char high_byte, char low_byte);
void max7219_clear(void);
void max7219_init(void);
void update_display(void);
void image(char im[8]);
void set_pixel(unsigned short r, char c, char value);

#endif