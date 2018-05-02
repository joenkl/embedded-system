/*
* p2_LCD.c
*
*
* Author : khadb, luankn
*/
#include "stdio.h"
#include "avr.h"
#include "lcd.h"

/* define default hour*/
char isCivil = 1;
char AM = 0;
char h = 0;
char civilH = 12;
char m = 59;
char s = 55;

/* define default day*/
int YYYY = 2016;
int MM = 2;
int DD = 29;
const int days_of_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
/*note: no month 0*/

char bufmsg[17];

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

unsigned char numToInt(int num)
{
	switch (num)
	{
	case 1:
		return 1;
		break;
	case 2:
		return 2;
		break;
	case 3:
		return 3;
		break;
	case 4:
		return 11;
		break;
	case 5:
		return 4;
		break;
	case 6:
		return 5;
		break;
	case 7:
		return 6;
		break;
	case 8:
		return 11;
		break;
	case 9:
		return 7;
		break;
	case 10:
		return 8;
		break;
	case 11:
		return 9;
		break;
	case 12:
		return 11;
		break;
	case 13:
		return 11;
		break;
	case 14:
		return 0;
		break;
	case 15:
		return 11;
		break;
	case 16:
		return 11;
		break;
	default:
		return 11;
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

void militaryToCivilTime()
{
	if (h == 0)
	{
		civilH = 12;
		AM = 1;
	}
	else if (h < 12 && h > 0)
	{
		civilH = h;
	}
	else if (h == 12)
	{
		civilH = h;
		AM = 0;
	}
	else if (h > 12)
	{
		civilH = h - 12;
		AM = 0;
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
	militaryToCivilTime();
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

void printMsg(const char *str)
{
	clr_lcd();
	sprintf(bufmsg, str);
	pos_lcd(0, 0);
	puts_lcd2(bufmsg);
}

unsigned int confirm()
{
	int key = 0;
	int pressed = 0;
	int check = 0;

	while (!pressed)
	{
		key = get_key();

		if (key == 12)
		{
			check = 0;
			pressed = 1;
		}
		else if (key == 16)
		{
			pressed = 1;
			check = 1;
		}
		wait_avr(100);
	}

	return check;
}

void getInputAndSetDay()
{
	printMsg("Set MM/DD/YYYY");

	//Set position to row 2:
	pos_lcd(1, 0);

	int in[10] = {0, 0, 10, 0, 0, 10, 0, 0, 0, 0};
	int current = 0;
	int n = 11;
	int n2;
	int dd, mm, yyyy;

	while (current < 10)
	{
		/*Print the dash MM/DD/YYYY*/
		if (current == 2 || current == 5)
		{
			pos_lcd(1, current);
			put_lcd('/');
			++current;
		}

		n = get_key();

		wait_avr(250);
		n2 = numToInt(n);

		if (n2 < 10)
		{
			in[current] = n2;
			pos_lcd(1, current);
			put_lcd(numToChar(n));
			++current;
		}
	}

	if (confirm() == 0)
	{
		printMsg("CANCELED");
	}
	else
	{
		/*MM/DD/YYYY*/
		mm = in[0] * 10 + in[1];
		dd = in[3] * 10 + in[4];
		yyyy = in[6] * 1000 + in[7] * 100 + in[8] * 10 + in[9];

		char c = setDay(dd, mm, yyyy);
		if (!c)
		{
			printMsg("Invalid Input");
		}
		else
		{
			printMsg("Date is set!");
		}
	}

	wait_avr(2000);
}

void getInputAndSetTime()
{
	printMsg("Set hh:mm:ss");

	//Set position to row 2:
	pos_lcd(1, 0);

	int in[8] = {0, 0, 10, 0, 0, 10, 0, 0};
	int current = 0;
	int n = 11;
	int n2;

	while (current < 8)
	{
		/*Print the dash hh:mm:ss*/
		if (current == 2 || current == 5)
		{
			pos_lcd(1, current);
			put_lcd(':');
			++current;
		}

		n = get_key();
		wait_avr(250);
		n2 = numToInt(n);

		if (n2 < 10)
		{
			in[current] = n2;
			pos_lcd(1, current);
			put_lcd(numToChar(n));
			++current;
		}
	}

	if (confirm() == 0)
	{
		printMsg("CANCELED");
	}
	else
	{
		/*hh:mm:ss*/
		char hh, mm, ss;
		hh = in[0] * 10 + in[1];
		mm = in[3] * 10 + in[4];
		ss = in[6] * 10 + in[7];

		char c = setTime(hh, mm, ss);
		if (!c)
		{
			printMsg("Invalid Input");
		}
		else
		{
			printMsg("Time is set!");
		}
	}

	wait_avr(2000);
}

void displayInfo()
{
	clr_lcd();
	char bufDate[17];
	char bufTime[17];
	//Print date format
	sprintf(bufDate, "%02i/%02i/%02i", MM, DD, YYYY);
	pos_lcd(0, 0);
	puts_lcd2(bufDate);
	//Print time
	if (isCivil)
	{
		if (AM)
			sprintf(bufTime, "%02i:%02i:%02i AM", civilH, m, s);
		else
			sprintf(bufTime, "%02i:%02i:%02i PM", civilH, m, s);
	}
	else
		sprintf(bufTime, "%02i:%02i:%02i", h, m, s);

	pos_lcd(1, 0);
	puts_lcd2(bufTime);
}

int main(void)
{
	/* Replace with your application code */
	ini_avr();
	ini_lcd();

	clr_lcd();

	/*init time*/
	//displayInfo();

	while (1)
	{
		displayInfo();

		//Keypad
		unsigned int num = get_key();
		wait_avr(50); // wait to release button

		if (num == 4 /*A: set day*/)
		{
			getInputAndSetDay();
			clr_lcd();
		}
		if (num == 8) /*B: set time*/
		{
			getInputAndSetTime();
			clr_lcd();
		}
		if (num == 13)
		{
			if (isCivil == 1)
				isCivil = 0;
			else
				isCivil = 1;
			displayInfo();
		}
		wait_avr(949);
		increaseTime();
	}
}
