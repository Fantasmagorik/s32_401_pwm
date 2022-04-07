#include "stm32f4xx.h"                  // Device header
#include "ws2812.h"
#define PIX_COUNT 5
extern int CPU_FREQ;
//TIMER 3 and its channel 1 (PB4) output  through DMA for ws2812 DI	4CHs

uint16_t test_mass[24 * PIX_COUNT];
uint8_t all_fill[24];
uint8_t all_blanc[24];
uint8_t flag;

union WS2812_Color{
	uint32_t intColor;
	uint8_t charColor[3];
	uint8_t blue;
	uint8_t green;
	uint8_t red;
};

void ws2812_dma_conf()	{
	int i;
	RCC->AHB1ENR				|=	RCC_AHB1ENR_DMA1EN;
	DMA1_Stream2->CR		 =	0;	//disable before cofigure

	DMA1_Stream2->PAR		 = (int) &TIM3->CCR1;
	DMA1_Stream2->CR		 = 5 << 25; //channel 5 switched
	DMA1_Stream2->CR		 |= DMA_SxCR_DIR_0	+	DMA_SxCR_MINC + DMA_SxCR_TCIE;
	/*+ DMA_SxCR_CIRC*/;
	for( i = 0; i < PIX_COUNT * 24; i++){
		test_mass[i] = (i%2)? WS2812_1: WS2812_0;
	}
	for(i = 0; i < 24; i++)	{
		all_fill[i] = WS2812_1;
		all_blanc[i] = WS2812_0;
	}
	DMA1_Stream2->NDTR = 200;
	DMA1_Stream2->M0AR = (int) test_mass;
}

void ws21812SendData(uint32_t color)	{
	#define tr	200
	#define fa	500
	union WS2812_Color _color;
	int i, x;
  _color.intColor	= color;
	for( i = 0; i < 24; i++)	{
		GPIOB->ODR |= 0x10;
		x = (color & 1 << i)? fa : tr;
		for(; x; x--);
		GPIOB->ODR &= ~0x10;
		x = (color & 1 << i)? tr : fa;
		for(; x; x--);
	}
	for(x = 15000; x; x--);
}

void ws2812_init()	{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;	//for insure if order or init would change
	//RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	//TIM11->DIER				 =		TIM_DIER_UIE;
	TIM3->ARR				 =		WS2812_1 + WS2812_0;
	TIM3->PSC				 =		0;
	TIM3->CCMR1 = (3 << 5) + TIM_CCMR1_OC1PE;	//channel 1 as output pwm mode 1
	
	GPIOB->AFR[0]	|=	0x20000; //B4 in AF2 mode
	GPIOB->MODER	|= (2 << 2*4);	//B4 on AF func
	GPIOB->OSPEEDR|= (2 << 2*4);	//B4 HIGH_SPEED
	//GPIOB->OTYPER	|=	1 << 4;	//	//B4 OPEN_DRAIN
	GPIOB->PUPDR	|=	(1 << 2*4);////B4 PULL_UP
	TIM3->CCR1 = WS2812_1;
	
	ws2812_dma_conf();
	TIM3->DIER = TIM_DIER_UDE;
	TIM3->CR2  = TIM_CR2_CCDS;
	TIM3->CCER = TIM_CCER_CC1E + TIM_CCER_CC1P ;	//tim3 channel enable
	TIM3->CR1 = TIM_CR1_CEN;
	
}

void ws2812_test()	{
	int i;
	#define WS_HI	300
	#define WS_LOW WS_HI * 2
	//GPIOB->BSRR = 0x10;
	GPIOB->MODER &= ~(1 << 9);
	GPIOB->ODR &= ~0x10;
	TIM3->CCER &= ~TIM_CCER_CC1E;
	//TIM3->CCR1 = 0;
	for(int i = 0; i < 15000; i++);
	ws21812SendData(0xff00ff);
	ws21812SendData(0xffffff);
	ws21812SendData(0xf0ff);
	/*
	GPIOB->MODER |= (1 << 9);
	DMA1_Stream2->CR &= ~DMA_SxCR_EN;

	flag  = !flag;
	DMA1_Stream2->NDTR = 20;
	DMA1_Stream2->M0AR = (int) test_mass;
	DMA1->LIFCR = DMA_LIFCR_CTCIF2;
	TIM3->CR1		|= TIM_CR1_URS;
	TIM3->SR = 0;
	TIM3->DIER = TIM_DIER_UDE;
	DMA1_Stream2->CR |= DMA_SxCR_EN;
	TIM3->DIER |= TIM_DIER_CC1DE;
	TIM3->CCER |= TIM_CCER_CC1E;
	//DMA1_Stream2->CR |= DMA_SxCR_EN;
	
	
	NVIC_EnableIRQ(DMA1_Stream2_IRQn);
	
	*/
	//GPIOB->ODR &= ~0x10;
	//for(int i = 0; i < 8000; i++);
}

void DMA1_Stream2_IRQHandler()	{
	DMA1->LIFCR		|=	DMA_LIFCR_CTCIF2;	//CLEAR interrupt bit
	TIM3->CCER &= ~TIM_CCER_CC1E;
	TIM3->CCR1 = 0;
	GPIOB->MODER &= ~(1 << 9);
	GPIOB->ODR &= ~0x10;
	for(int i = 0; i < 8000; i++);
	GPIOB->MODER |= (1 << 9);
	/*GPIOB->MODER &= ~(1 << 9);
	GPIOB->ODR &= ~0x10;
	for(int i = 0; i < 8000; i++);
	GPIOB->MODER |= (1 << 9);
	DMA1_Stream2->NDTR = 24 * 5;
	//TIM3->CCR1 = WS2812_1;
	
	DMA1_Stream2->CR |= DMA_SxCR_EN + DMA_SxCR_TCIE;*/
}