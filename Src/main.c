/*
 * Author: Sam Gay
 * Created: 7/9/26
 * Purpose:
 */


#include "clock_config.h"
#include "i2c_main.h"
#include "i2c-lcd.h"
 #include "i2c_dht20.h"
#include "Delay.h"
#include <stm32l476xx.h>

int main()
{
	// TODO: add console logging to attached computer

	// Clock
	clock_config();
	TIM6Config();

	// I2C
	i2c_config();

	// LCD
	lcd_init();

	// Temperature
	// TODO

	while (1)
	{
		lcd_send_string("hello world!");
		Delay_ms(100);
		lcd_send_string("A");
		Delay_ms(100);
		lcd_send_string("B");
		Delay_ms(100);
		lcd_send_string("C");
		Delay_ms(100);
		lcd_send_string("1");
		Delay_ms(100);
		lcd_send_string("2");
		Delay_ms(100);
		lcd_send_string("3");
		Delay_ms(100);
	}
}
