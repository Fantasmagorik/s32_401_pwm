#include "stm32f4xx.h"
#include "hw_mcu.h"
#include "hw_i2c.h"
#include "hw_ssd1306.h"
#include "hw_dma.h"
#include "ws2812.h"
uint64_t timeAfterReset = 0;

uint64_t millis()	{
	return timeAfterReset;
}



void delay(int ms)	{
	uint64_t start_time = millis();
	while(millis() - start_time < ms);
}



int wait_for_event(short unsigned *byte_addr, short unsigned mask, char expected_value, unsigned int timeout)	{
	uint64_t start_time = millis();
 	while(millis() - start_time < timeout)	{
   		if( ((*byte_addr) & mask )> 0 ==( expected_value > 0) ) //black humor(
				return 0;
		}

	return 1;
}




int RCC_init(void)	{
	int returnCode 	=	0;
	RCC->CR				 |=		RCC_CR_HSEON;
	RCC->PLLCFGR		=		25 + (168 << 6) + (1 << 26) + (1 << 22);	//PLLM = 25, PLLN = 168, PLLQ = 4, PLLSRC = HSE
	RCC->CFGR 		 |=		1 << 12;	//APB1PERIPH_BASE divided by 2 (42 MHz)
	while(!RCC->CR & RCC_CR_HSERDY);
	RCC->CR				 |=		RCC_CR_PLLON;
	while(!RCC->CR & RCC_CR_PLLRDY);
	FLASH->ACR			=		2;
	RCC->CFGR			 |=		2;
	return returnCode;
}




int userDelayTimer_init(void)	{
	int returnCode 	=	0;	
	RCC->APB2ENR			|=  	RCC_APB2ENR_TIM11EN;
	TIM11->DIER				 =		TIM_DIER_UIE;
	TIM11->ARR				 =		10;
	TIM11->PSC				 =		8399;
	TIM11->CR1				 =		TIM_CR1_CEN;
	timeAfterReset		 = 		0;
	NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);
	return returnCode;
}




void TIM1_TRG_COM_TIM11_IRQHandler(void)	{
	TIM11->SR		=		0;
	timeAfterReset++;
}




int statusLed_init(void)	{
	int returnCode = 0;
	RCC->AHB1ENR			|=	  RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER 			|=    1 << 2 * 13;
	GPIOC->BSRR				 = 		1 << 13;
	return returnCode;
}




int system_init(void)	{
	RCC_init();
	statusLed_init();
	userDelayTimer_init();
	
}




int periph_init(void)	{
	int returnCode = 0;
	i2c1_init();

	return returnCode;
}



int externalDevice_init(void)	{
	int returnCode = 0;
	SSD1306Init();
	i2c1_DMA_init();
	ws2812_init();
	return returnCode;
}