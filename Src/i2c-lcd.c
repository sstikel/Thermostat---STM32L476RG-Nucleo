/**
  ******************************************************************************

  LCD1602.c For STM32F446RE
  Author:   ControllersTech
  Updated:  31st Jan 2020

  ******************************************************************************
  Copyright (C) 2017 ControllersTech.com

  This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
  of the GNU General Public License version 3 as published by the Free Software Foundation.
  This software library is shared with public for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
  or indirectly by this software, read more about this on the GNU General Public License.

  ******************************************************************************
*/

// Additional comments added throughout by Sam Gay on 7/9/26
// Datasheet: https://academy.cba.mit.edu/classes/output_devices/44780.pdf


#include "i2c-lcd.h"
// Modified by Sam Gay on 7/9/26: include file to STM32L476 I2C config
#include "i2c_main.h"
#include "delay.h"

// Modified by Sam Gay on 7/9/26: address of 1602LCD
#define SLAVE_ADDRESS_LCD 0x27

// Modified by Sam Gay on 7/9/26: To use STM32L476RG I2C config
void LCD_Write (uint8_t Address, uint8_t *Data, int size)
{
	i2c_address(Address);
	i2c_start();

	for (int i = 0; i < size; i++)
	{
		i2c_write(*Data++);
	}

	i2c_stop();
}

void lcd_send_cmd (char cmd)
{
	char data_u, data_l;
	uint8_t data_t[4];

	// split 8 bit into 4 bit - upper and lower
	// 0xF0 - 1111 0000
	data_u = (cmd & 0xf0); // upper 4 bits
	data_l = ((cmd << 4) & 0xf0); // lower 4 bits

	//
	data_t[0] = data_u | 0x0C;  //en=1, rs=0
	data_t[1] = data_u | 0x08;  //en=0, rs=0
	data_t[2] = data_l | 0x0C;  //en=1, rs=0 // 0x0C - 0000 1100
	data_t[3] = data_l | 0x08;  //en=0, rs=0 // 0x08 - 0000 1000

	LCD_Write (SLAVE_ADDRESS_LCD, (uint8_t *) data_t, 4);
}

void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data & 0xf0);
	data_l = ((data << 4) & 0xf0);
	data_t[0] = data_u | 0x0D;  //en=1, rs=1
	data_t[1] = data_u | 0x09;  //en=0, rs=1
	data_t[2] = data_l | 0x0D;  //en=1, rs=1
	data_t[3] = data_l | 0x09;  //en=0, rs=1
	LCD_Write (SLAVE_ADDRESS_LCD, (uint8_t *) data_t, 4);
}

void lcd_clear (void)
{
	lcd_send_cmd (0x80);
	for (int i=0; i < 70; i++)
	{
		lcd_send_data (' ');
	}
}

void lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    lcd_send_cmd (col);
}

void lcd_init (void)
{
	// lcd initialization // see pg. 46 of HD44780U
	Delay_ms(50);  // wait for >40ms
	lcd_send_cmd (0x30); // 0011 0000 --> Init Function Set pt. 1/3
	Delay_ms(5);  // wait for >4.1ms
	lcd_send_cmd (0x30); // 0011 0000 --> Init Function Set pt. 2/3
	Delay_us(150);  // wait for >100us
	lcd_send_cmd (0x30); // 0011 0000 --> Init Function Set pt. 3/3
	Delay_ms(10);
	// NOTE: Display Lines (N) and Character Font (F) can't be changed after this line of code.
	lcd_send_cmd (0x20);  // 4bit mode // 0010 0000 --> DL=0 (4 bit mode), N=1 (2 line), F=0 (5x8 dot matrix)
	Delay_ms(10);

  // 4 bit initialization
	lcd_send_cmd (0x28); // Function set  0010 1000 --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 dot matrix)
	Delay_ms(1);
	lcd_send_cmd (0x08); //Display on/off control --> D=0, C=0, B=0  ---> display off, cursor off, cursor blink off
	Delay_ms(1);
	lcd_send_cmd (0x01);  // clear display
	Delay_ms(1);
	Delay_ms(1);
	lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor right) & S = 0 (no shift)
	Delay_ms(1);

	// display on
	lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C=0, B = 0  ---> display on, cursor off, cursor blink off
}

void lcd_send_string (char *str)
{
	while (*str)
	{
		lcd_send_data (*str++);
	}
}
