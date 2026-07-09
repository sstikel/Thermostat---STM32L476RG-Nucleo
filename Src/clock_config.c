/*
 * Author: Sam Gay
 * Created: 7/9/26
 * Purpose: Clock config for STM32L476RG
 */


/*
 * Clock Configuration:
 * SYSCLK  		  = 32 MHz
 * HCLK 		  = 32 MHz
 * HSI 			  = 16 MHz
 * PLLM 		  = 1
 * PLLN 		  = 12
 * PLLR           = 6
 * AHB  prescaler = 1
 * APB1 prescaler = 4
 * APB2 prescaler = 2
 */


void clock_config(void)
{
	// Enable HSI16 clock
	RCC->CR |= RCC_CR_HSION;
	while (!(RCC->CR & RCC_CR_HSIRDY));

	// Clock power
	RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
	PWR->CR1 |= PWR_CR1_VOS; // Range 1

	// Flash memory
	FLASH->ACR = FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN; // instr. cache | data cache | prefetch
	FLASH->ACR = FLASH_ACR_LATENCY_4WS; // 4 wait states for Range 1 (PWR) and <= 80 MHz HCLK, pg 101


	// PLL (Phase-Locked Loop clock control system)
	//	Multiplies clock frequency to enable additional peripherals that require higher frequencies than the clock can support
	// 	PLL/M = 1 -- regulate input clock (HSI) speed by dividing by this value. PLL must be between 4MHz and 16MHz (ex.: 32MHz (clock) / 4 (PLLM) = 8MHz)
	// 	PLL*N = 12 -- multiply clock (HSI) speed
	// 	PLL/R = 6, represented as 2 -- (HSI / M) * N / R -> PLLCLK
	RCC->PLLCFGR = (12 << 8) | (2 << 25) | (RCC_PLLCFGR_PLLREN) | (RCC_PLLCFGR_PLLSRC_HSI); // PLL*N | PLL/R | PLLCLK EN | PLLSRC HSI
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY));

	// Pre-scalers
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;  // AHB  prescaler -- SYSCLOCK / 1 -> HCLK
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4; // APB1 prescaler -- HCLK     / 4 -> PCLK1
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2; // APB2 prescaler -- HCLK     / 2 -> PCLK2

	// Clock source
	RCC->CFGR |= RCC_CFGR_SW_PLL; // sets PLL as system clock
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}
