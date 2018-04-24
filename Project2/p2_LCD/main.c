/*
* p2_LCD.c
*
*
* Author : khadb, luankn
*/
#include "stdio.h"
#include "avr.h"
#include "lcd.h"

/* define hour*/
char isCivil = 0;
char AM = 1;
char h = 23;
char m = 59;
char s = 50;

/* define day*/
int YYYY = 2016;
int MM = 2;
int DD = 29;
const int days_of_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
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
	//Set to default
	DDRC = 0;
	
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

int setDay(int day, int month, int year)
{
	if (month > 12 || month == 0 || year == 0 || day == 0)
		return 0; //Error

	if (day > days_of_month[month])
	{
		if (month != 2)
			return 0; //need to check for leap year
		else
		{
			if (isLeapYear() && day > 29)
				return 0;
			if (!isLeapYear())
				return 0;
		}
	}
	DD = day;
	MM = month;
	YYYY = year;
	return 1;
}

int setTime(char hour, char minute, char second)
{
	if (hour > 23 || minute > 59 || second > 59)
		return 0;

	h = hour;
	m = minute;
	s = second;
	return 1;
}

void civilToMilitaryTime()
{
	if (!AM)
	{
		h += 12;
	}

	isCivil = 0;
}
void militaryToCivilTime()
{
	if (h > 11)
	{
		if (h > 12)
			h = h - 12;
		AM = 0;
	}
	isCivil = 1;
}

int main(void)
{
	/* Replace with your application code */
	ini_avr();
	ini_lcd();

	clr_lcd();
	char bufDate[17];
	char bufTime[17];
	//Print date format
	sprintf(bufDate, "%02i/%02i/%02i", MM, DD,YYYY);
	pos_lcd(0,0);
	puts_lcd2(bufDate);
	
	//Print time
	sprintf(bufTime, "%02i:%02i:%02i", h, m, s);
	pos_lcd(1,0);
	puts_lcd2(bufTime);
	
	while (1)
	{
		////Keypad
		//unsigned int num = get_key();
		//wait_avr(100); // wait to release button
		//if (num)
		//{
			////clear
			//clr_lcd();
			////wait_avr(500);
			//put_lcd(numToChar(num));
		//}
		increaseTime();
		//Print date format
		sprintf(bufDate, "%02i/%02i/%02i", MM, DD,YYYY);
		pos_lcd(0,0);
		puts_lcd2(bufDate);
		
		//Print time
		sprintf(bufTime, "%02i:%02i:%02i", h, m, s);
		pos_lcd(1,0);
		puts_lcd2(bufTime);
		wait_avr(1000);
	}
}
