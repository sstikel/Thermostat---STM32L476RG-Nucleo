/*
 * Author: Sam Gay
 * Created: 7/10/26
 */

#include "usart_main.h"

void usart_config(void)
{
	// Enable peripheral clocks
	RCC->AHB2ENR  |= RCC_AHB2ENR_GPIOAEN;   // GPIOA
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN; // USART2

	// GPIOA config
	GPIOA->MODER &= ~(3 << 4); // clear bits 4 and 5
	GPIOA->MODER |= (2 << 4);  // set pin PA2 to alternate function
	GPIOA->AFR[0] = (7 << 8); // pin PA2 AF7 (USART2_TX)

	// USART config
	//		Viewer: Tera Term VT (COM6)
	//		PCLK -> USART fck == 8 MHz (8,000,000 Hz)
	//		fck / USARTDIV = Baud
	//		8,000,000 Hz / 833 = 9603 Baud
	USART2->BRR = 0x341;

	USART2->CR1 |= USART_CR1_UE; // USART enable
	USART2->CR1 |= USART_CR1_TE; // Transmit enable
}

void usart_write(char letter)
{
	while(!(USART2->ISR & USART_ISR_TXE));
	USART2->TDR = (letter);
}

void usart_write_string(char *str)
{
	while (*str)
	{
		usart_write(*str);
		str++;
	}
}

void delay(int delayms){
	volatile int i;
	for(; delayms > 0; delayms--){
		for(i = 0; i < 3192; i++);
	}
}
