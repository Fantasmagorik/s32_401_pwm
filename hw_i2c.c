#include "stm32f4xx.h"
#include "hw_mcu.h"
#include "hw_i2c.h"

#define CPU_FREQ	84	//Freq in MHz


int i2c1_init(void)	{	
	int returnCode = 0;
	RCC->APB1ENR		|=	RCC_APB1ENR_I2C1EN;
	RCC->AHB1ENR	|=	RCC_AHB1ENR_GPIOBEN;
	GPIOB->AFR[0]	|=	0x44000000; //B6 & B7 in AF4 mode
	GPIOB->MODER	|=	( (2 << 2*7) + (2 << 2*6) );	//B7 & B6 on AF func
	GPIOB->OSPEEDR|=	(	(2 << 2*7) + (2 << 2*6) );	//B7 & B6 HIGH_SPEED
	GPIOB->OTYPER	|=	3 << 6;	//										//B6 & B7 OPEN_DRAIN
	GPIOB->PUPDR	|=	5 << 12;//										//B6 & B7 PULL_UP
	I2C1->CR2			 =	CPU_FREQ / 2;
	I2C1->CCR			 =	/*208;//*/I2C_CCR_DUTY + I2C_CCR_FS + 23;
	I2C1->TRISE		 =	14;
	I2C1->CR1			|=	I2C_CR1_PE;
	return returnCode;
}



int i2c1_reset()	{
		I2C1->CR1 |= I2C_CR1_SWRST;
		delay(10);
		I2C1->CR1 &= ~I2C_CR1_SWRST; //remove reset flag
		if (wait_for_event((short unsigned *) &I2C1->CR1, I2C_CR1_SWRST, 0, 500) > 0)	{
			return 128;	//PERIPH_BASE RESTART FAULT, -->full reset (with power?)
		}
		return i2c1_init(); //reinint periph
}
	

int i2c1_sendAddress(char address)	{
	if (wait_for_event( (short unsigned *) &I2C1->SR2, I2C_SR2_BUSY, 0, 100))	 
			if (i2c1_reset() > 0)
				return 128;	//BusFault_IRQn: BUS FATAL ERRO

	//	while ((I2C1->SR2 & I2C_SR2_BUSY)){};  //wait for i2c free
    I2C1->CR1 |= I2C_CR1_START;						 //START
    if (wait_for_event ((short unsigned *) &I2C1->SR1, I2C_SR1_SB, 1, 100) > 0)	{
			if (i2c1_reset() > 0)
				return 64;		//no START_BIT detected
			else 
				i2c1_sendAddress(address);
		}
    I2C1->DR = address ;						 //send Address
    if (wait_for_event ((short unsigned *) &I2C1->SR1, I2C_SR1_ADDR, 1, 100) > 0)	
			return 32;		//no device with that address
    /* wait set transmit mode */
		
		(void) I2C1->SR1;											//CLEAR
		(void) I2C1->SR2;											//ADDR bit
		
			return 0;
}


int i2c1_sendByte(char data)	{
	if(wait_for_event((short unsigned *) &I2C1->SR1, I2C_SR1_TXE, 1, 50))
		return 1;
		//while (!(I2C1->SR1 & I2C_SR1_TXE)){};
		I2C1->DR= data;
			return 0;
}


int i2c1_stop()	{
		//while (!(I2C1->SR1 & I2C_SR1_TXE)){}; //wait end of transfer
		if( (I2C1->SR2 & I2C_SR2_BUSY) == 0)
				return 0;
		wait_for_event((short unsigned *) &I2C1->SR1, I2C_SR1_TXE, 1, 300); //wait end of transfer
		I2C1->CR1|= I2C_CR1_STOP;		
		while(I2C1->SR2& I2C_SR2_MSL);
		return 0;
	}
	
	