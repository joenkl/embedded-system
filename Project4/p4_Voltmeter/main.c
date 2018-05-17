/*
 * p4_Voltmeter.c
 *
 */ 

#include <avr/io.h>
#include "avr.h"
#include "lcd.h"
#include "keypad.h"
#include "voltmeter.h"

int main(void)
{
    ini_avr();
	ini_lcd();
	ini_meter();
	
	int key = 0;
	
    while (1) 
    {
		key = get_key();
		
		
    }
}

