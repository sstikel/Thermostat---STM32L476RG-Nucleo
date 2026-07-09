/*
 * Author: Sam Gay
 * Created: 7/9/26
 * Reference Sheet: ST RM0351 Reference Manual
 * Purpose: Handle I2C config and functionality
 */

#include "i2c_main.h"
#include "clock_config.h"

void i2c_config(void)
{
	// Enable peripheral clocks
	RCC->AHB2ENR  |= RCC_AHB2ENR_GPIOBEN; // (1 << 1); // GPIOB
	RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN; // I2C1

	// GPIOB config of pins PB8 and PB9
	//	MODER, OSPEEDR, PUPDR: PB8 -> bits 16 and 17; PB9 -> bits 18 and 19
	GPIOB->MODER   &= ~(3 << 16) & ~(3 << 18); // clear MODER bits
	GPIOB->MODER   |=  (2 << 16) |  (2 << 18);  // Set pins PB8 and PB9 to Alternate Function
	GPIOB->OTYPER  |=  (1 << 8)  |  (1 << 9);  // Output type -> open-drain
	GPIOB->OSPEEDR |=  (1 << 16) |  (1 << 18);  // Medium speed
	GPIOB->PUPDR   |=  (1 << 16) |  (1 << 18);  // Pull-up
	// AFR[1] == AFRH; PB8 -> bits 0 through 3; PB9 -> bits 4 through 7
	GPIOB->AFR[1]  |=  (4 << 0)  |  (4 << 4);  // Alternate Function AF4 (See datasheet; I2C1 column, PB8 and PB9 rows; PB8 -> SCL, PB9 -> SDA)


	// I2C Config
	I2C1->CR1 &= ~I2C_CR1_PE; // Disable/reset I2C peripheral

	// Peripheral timings
	//	reference sheet pg. 1290, Table 240, Standard-mode (Sm), 100 kHz
	I2C1->TIMINGR = (0x1 << 28); // PRESC
	I2C1->TIMINGR = (0xF << 8) | (0x13 << 0); // SCLH | SCLL
	I2C1->TIMINGR = (0x4 << 20) | (0x2 << 16); // SCLDEL | SDADEL

	I2C1->CR1 |= (1 << 0);  // Enable I2C peripheral
}

void i2c_start(void)
{
	I2C1->CR2 |= I2C_CR2_START;
}

void i2c_stop(void)
{
	while(!(I2C1->ISR & I2C_ISR_TC)); // wait for transfer to complete
	I2C1->CR2 |= I2C_CR2_STOP;
	while(I2C1->ISR & I2C_ISR_BUSY);
}

void i2c_address(uint8_t addr)
{

	while(I2C1->ISR & I2C_ISR_BUSY);
	I2C1->CR2 &= ~((0x3FF << 0) | (0xFF << 16)); // Clear SADD and NBYTES
	I2C1->CR2 |= (addr << 1); // address loaded into SADD (shifted 7 bit)
	I2C1->CR2 |= (4 << 16); // 4 bit operation (LCD) requires 2 sets of bytes (2 sets of 4 bits), total of 4 bytes
}

void i2c_write(uint8_t data)
{
	while (!(I2C1->ISR & I2C_ISR_TXIS)); // Reference manual, pg. 1283, Figure 407
	I2C1->TXDR = data;
}

// TODO i2c_read
