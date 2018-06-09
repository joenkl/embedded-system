//Source: https://halfbyteblog.wordpress.com/2015/11/29/using-a-max7219-8x8-led-matrix-with-an-attiny85-like-trinket-or-digispark/

#include "LedMatrix.h"


void SPI_send(char data)
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

void led_write(char high_byte, char low_byte)
{
	CS_LOW();
	SPI_send(high_byte);
	SPI_send(low_byte);
	CS_HIGH();
}

void led_clear(void)
{
	char i;
	for (i = 0; i < 8; i++)
	{
		led_write(i+1, 0);
	}
}

void led_init(void)
{
	INIT_PORT();
	// Decode mode: none
	led_write(0x09, 0);
	// Intensity: 3 (0-15)
	led_write(0x0A, 1);
	// Scan limit: All "digits" (rows) on
	led_write(0x0B, 7);
	// Shutdown register: Display on
	led_write(0x0C, 1);
	// Display test: off
	led_write(0x0F, 0);
	led_clear();
}


char display[8];

void update_display(void)
{
	unsigned short i;

	for (i = 0; i < 8; i++)
	{
		led_write(i+1, display[i]);
	}
}

void image(char im[8])
{
	unsigned short i;

	for (i = 0; i < 8; i++)
	display[i] = im[i];
}