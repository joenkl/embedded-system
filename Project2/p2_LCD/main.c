/*
* p2_LCD.c
*
*
* Author : khadb, luankn
*/

#include "avr.h"
#include "lcd.h"
#include "main.h"

/* define hour*/
#define h = 8;
#define m = 0;
#define s = 0;

/* define day*/
#define YYYY = 2018;
#define MM = 5;
#define DD = 1;
#define days_of_month [] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
/*note: no month 0*/

unsigned char numToChar(int num)
{
	switch (num)
	{
	case 1:
		return '1';
		break;
	case 2:
		return '2';
		break;
	case 3:
		return '3';
		break;
	case 4:
		return 'A';
		break;
	case 5:
		return '4';
		break;
	case 6:
		return '5';
		break;
	case 7:
		return '6';
		break;
	case 8:
		return 'B';
		break;
	case 9:
		return '7';
		break;
	case 10:
		return '8';
		break;
	case 11:
		return '9';
		break;
	case 12:
		return 'C';
		break;
	case 13:
		return '*';
		break;
	case 14:
		return '0';
		break;
	case 15:
		return '#';
		break;
	case 16:
		return 'D';
		break;
	default:
		return 0;
		break;
	}
}

//Need to fix
unsigned int is_pressed(int r, int c)
{
	c += 4;
	//Set row to output and STRONG 0
	SET_BIT(DDRC, r);
	CLR_BIT(PORTC, r);

	//Set column to input and WEAK 1
	CLR_BIT(DDRC, c);
	SET_BIT(PORTC, c);

	return (GET_BIT(PINC, c)) == 0 ? 1 : 0;
}

unsigned int get_key()
{
	int r, c;
	for (r = 0; r < 4; ++r)
	{
		for (c = 0; c < 4; ++c)
		{
			if (is_pressed(r, c))
				return r * 4 + c + 1;
		}
	}
	return 0;
}

char isLeapYear()
{
	return ((YYYY % 4 == 0 && YYYY % 100 != 0) || (YYYY % 400 == 0))
						 ? 1 /* true*/
						 : 0 /* false */;
}

void increaseDay()
{
	if (!(isLeapYear() && MM == 2))
	{
		if (++DD && DD > days_of_month[MM])
		{
			DD = 1;
			if (++MM && MM > 12)
			{
				MM = 1;
				++YYYY;
			}
		}
	}
	else
	{
		if (++DD && DD > 29)
		{
			DD = 1;
			if (++MM && MM > 12)
			{
				MM = 1;
				++YYYY;
			}
		}
	}
}

void increaseTime()
{
	++s;
	if (s > 59)
	{
		++m;
		s = 0;
	}
	if (m > 59)
	{
		++h;
		m = 0;
	}
	if (h > 23)
	{
		h = 0;
		increaseDay();
	}
}

char setDay(char day, char month, char year)
{
	if (month > 12 || month == 0 || year == 0 || day == 0)
		return 0; //Error

	if (day > days_of_month[month])
		if (month != 2)
			return 0; //need to check for leap year
		else
		{
			if (isLeapYear() && day > 29)
				return 0;
			if (!isLeapYear())
				return 0;
		}

	DD = day;
	MM = month;
	YYYY = year;
	return 1;
}

char setTime(char hour, char minute, char second)
{
	if (hour > 23 || minute > 59 || second > 59)
		return 0;

	h = hour;
	m = minute;
	s = second;
	return 1;
}

int main(void)
{
	DDRB = 0x08; //set B3 output
	ini_lcd();
	/* Replace with your application code */
	while (1)
	{
		//Set to default
		DDRC = 0x00;

		//Keypad
		unsigned int num = get_key();
		wait_avr(100); // wait to release button
		if (num)
		{
			//clear
			clr_lcd();
			//wait_avr(500);
			put_lcd(numToChar(num));
		}
	}
}
