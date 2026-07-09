/**
  ******************************************************************************

  Timer Setup for Delay in STM32F446RE
  Author:   ControllersTech
  Updated:  2nd Aug 2020
  Repository: https://github.com/controllerstech/STM32-HAL/blob/master/LCD1602_I2C_NOHAL/Delay.c

  ******************************************************************************
  Copyright (C) 2017 ControllersTech.com

  This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
  of the GNU General Public License version 3 as published by the Free Software Foundation.
  This software library is shared with public for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
  or indirectly by this software, read more about this on the GNU General Public License.

  ******************************************************************************
*/


#include "Delay.h"
// Modified by Sam Gay on 7/9/26: include file to STM32L476 clock config
#include "clock_config.h"

void TIM6Config (void)
{
	/************** STEPS TO FOLLOW *****************
	1. Enable Timer clock
	2. Set the prescalar and the ARR
	3. Enable the Timer, and wait for the update Flag to set
	************************************************/

// 1. Enable Timer clock
	// --- Modified by Sam Gay on 7/9/26: edited to be usable with an STM32L476RG ---
	RCC->APB1ENR1 |= (1 << 4); // RCC->APB1ENR |= (1 << 4);  // Enable the timer6 clock

// 2. Set the prescalar and the ARR
	TIM6->PSC = 90-1;  // 90MHz/90 = 1 MHz ~~ 1 uS delay
	TIM6->ARR = 0xffff;  // MAX ARR value

// 3. Enable the Timer, and wait for the update Flag to set
	TIM6->CR1 |= (1 << 0); // Enable the Counter
	while (!(TIM6->SR & (1 << 0)));  // UIF: Update interrupt flag..  This bit is set by hardware when the registers are updated
}

void Delay_us (uint16_t us)
{
	/************** STEPS TO FOLLOW *****************
	1. RESET the Counter
	2. Wait for the Counter to reach the entered value. As each count will take 1 us,
		 the total waiting time will be the required us delay
	************************************************/
	TIM6->CNT = 0;
	while (TIM6->CNT < us);
}

void Delay_ms (uint16_t ms)
{
	for (uint16_t i = 0; i < ms; i++)
	{
		Delay_us (1000); // delay of 1 ms
	}
}
