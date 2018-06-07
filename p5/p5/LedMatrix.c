//Source: https://halfbyteblog.wordpress.com/2015/11/29/using-a-max7219-8x8-led-matrix-with-an-attiny85-like-trinket-or-digispark/

#include "LedMatrix.h"


void spi_send(char data)
{
	char i;

	for (i = 0; i < 8; i++, data <<= 1)
	{
		CLK_LOW();
		if (data & 0x80)
		DATA_HIGH();
		else
		DATA_LOW();
		CLK_HIGH();
	}
	
}

void max7219_writec(char high_byte, char low_byte)
{
	CS_LOW();
	spi_send(high_byte);
	spi_send(low_byte);
	CS_HIGH();
}

void max7219_clear(void)
{
	char i;
	for (i = 0; i < 8; i++)
	{
		max7219_writec(i+1, 0);
	}
}

void max7219_init(void)
{
	INIT_PORT();
	// Decode mode: none
	max7219_writec(0x09, 0);
	// Intensity: 3 (0-15)
	max7219_writec(0x0A, 1);
	// Scan limit: All "digits" (rows) on
	max7219_writec(0x0B, 7);
	// Shutdown register: Display on
	max7219_writec(0x0C, 1);
	// Display test: off
	max7219_writec(0x0F, 0);
	max7219_clear();
}


char display[8];

void update_display(void)
{
	unsigned short i;

	for (i = 0; i < 8; i++)
	{
		max7219_writec(i+1, display[i]);
	}
}

void image(char im[8])
{
	unsigned short i;

	for (i = 0; i < 8; i++)
	display[i] = im[i];
}

void set_pixel(unsigned short r, char c, char value)
{
	switch (value)
	{
		case 0: // Clear bit
		display[r] &= (char) ~(0x80 >> c);
		break;
		case 1: // Set bit
		display[r] |= (0x80 >> c);
		break;
		default: // XOR bit
		display[r] ^= (0x80 >> c);
		break;
	}
}
