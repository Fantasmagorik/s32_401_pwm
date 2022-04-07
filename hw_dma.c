#include "stm32f4xx.h"
#include "hw_ssd1306.h"
#include "hw_dma.h"
#include "hw_i2c.h"
#include <string.h>


#define SSD1306_MAX_TASKS		6

extern char currentX, currentY;

char currentXPosition = 0, currentYPosition = 0;
char BLACK_COLOR;


//SSD1306 
SSD1306_DMA_Task	task_query[SSD1306_MAX_TASKS];
uint8_t currentTaskN;	//private.. served only by DMA_handler

uint8_t i2c_dma_operation;

void DMA_Fill(char *ptrData, char posX, char lengthX, char posY, char heightY, char MINC)	{
	SSD1306_DMA_Task *task = SSD1306_get_DMA_task(FREE);
	if(task == 0)
		return;
	task->posX 										= posX;
	task->posY 										= posY;
	task->lengthX 								= lengthX;
	task->heightY 								= heightY;
	task->transaction_count_left 	= 1;
	task->ptr_data								= ptrData;
	task->font										= (struct protoFontInformation*) MINC;
	task->operation								= GRAPHIC;
	if(!(DMA1_Stream7->CR & DMA_SxCR_EN))
		NVIC_SetPendingIRQ(DMA1_Stream7_IRQn);
}	


void DMA_Print(char *text, char xPos, char yPos, struct protoFontInformation *font)	{
	SSD1306_DMA_Task *task = SSD1306_get_DMA_task(FREE);
	if(task == 0)
		return;
	//task->count = strlen(text);
	task->font 										= font;
	task->posX 										= xPos;
	task->posY 										= yPos;
	task->ptr_data 								= text;
	task->transaction_count_left 	= strlen(text);
	task->operation 							= PRINT;
	/*if(!(DMA1_Stream7->CR & DMA_SxCR_EN))
			DMA1_Stream7_IRQHandler();
	//*/
	if(!(DMA1_Stream7->CR & DMA_SxCR_EN))
		NVIC_SetPendingIRQ(DMA1_Stream7_IRQn);
}


SSD1306_DMA_Task* SSD1306_get_DMA_task(char operation)	{	//should disable irq
	int i;
	char taskN = currentTaskN;	//works only with copy
	SSD1306_DMA_Task *task = task_query + taskN;
	__disable_irq();
	for(i = 0; i < SSD1306_MAX_TASKS; i++)	{
		if(task->operation == operation)
			break;
		if(++taskN >= SSD1306_MAX_TASKS)
			taskN = 0;
		task = task_query + taskN;
	}
	if(task->operation == operation)	{
		if(operation == FREE)
			task->operation = BLOCKED;
	}
	else
		task = 0;
	
	__enable_irq();
	return task;
}


void DMA1_Stream7_IRQHandler(void)	{
	SSD1306_DMA_Task *task = task_query + currentTaskN;
	uint8_t *ptrByte;
	char *currentSymbol;
	struct protoFontDescriptors *charInfo;
	int width, w_byte, count_of_data;

	DMA1->HIFCR		|=	DMA_HIFCR_CTCIF7;	//CLEAR interrupt bit
	i2c1_stop();			
	
	if(task->transaction_count_left == 0)	{
		task->operation = FREE;
		//search for another task
		if(++currentTaskN >= SSD1306_MAX_TASKS)
			currentTaskN = 0;
		task = SSD1306_get_DMA_task(GRAPHIC);
		if(task == 0)	{
			task = SSD1306_get_DMA_task(PRINT);
			if(task == 0)	//no more task
				return;
		}
	}
	if(task->operation == PRINT)	{
		currentSymbol = task->ptr_data;
		
		if(*currentSymbol == ' ')	{	//SPACE
			//call fill dma_transaction
			i2c1_sendAddress(SSD1306_Address);
			count_of_data = SSD1306SetWindow(task->posX, task->font->height/3, task->posY, task->font->height/8 - 1);
			task->posX += task->font->height/3;
			DMA1_Stream7->M0AR = (int) &BLACK_COLOR;
			DMA1_Stream7->CR	&= ~DMA_SxCR_MINC;
		}
		//that block should be corrected
		else if( (*currentSymbol < task->font->firstCharCode ) || (*currentSymbol > task->font->lastCharCode) ) {	//out of range
			while(*(++currentSymbol) != 0)	{
				if( (*currentSymbol >= task->font->firstCharCode) && (*currentSymbol <= task->font->firstCharCode) )
					break;
			}
			if( (*currentSymbol < task->font->firstCharCode ) || (*currentSymbol > task->font->lastCharCode) ) {	//still out of range
			task->transaction_count_left = 0;	//emulate end of task
			DMA1_Stream7_IRQHandler();							//and recall func
			}
		}

		else	{	//simple printable character
			DMA1_Stream7->CR	|= DMA_SxCR_MINC;
			charInfo = (struct protoFontDescriptors*) task->font->addrFontDescriptor + *(task->ptr_data) - task->font->firstCharCode;
			width		= charInfo->width;
			//w_byte	= width / 8+ ((width % 8)? 1 : 0); 
			ptrByte = (uint8_t*) (task->font->addrFontDataStart + charInfo->position);	//address of image
			i2c1_sendAddress(SSD1306_Address);
			count_of_data = SSD1306SetWindow(task->posX, charInfo->width - 1, task->posY, task->font->height/8 - 1);
			//count_of_data = width * task->font->height/8;
			task->posX	+=	width + 3;
			DMA1_Stream7->M0AR = (int) ptrByte;
		}
		
		task->ptr_data++;
	}
	
	else if(task->operation == GRAPHIC)	{
		i2c1_sendAddress(SSD1306_Address);
		count_of_data = SSD1306SetWindow(task->posX, task->lengthX, task->posY, task->heightY); //change to return a count of data need to be transfered via the window
		DMA1_Stream7->M0AR = (int)task->ptr_data;
		if(task->font)
			DMA1_Stream7->CR	|= DMA_SxCR_MINC;
		else
			DMA1_Stream7->CR	&= ~DMA_SxCR_MINC;
	}
	i2c1_sendByte(SSD1306_MODE_DATs);
	DMA1_Stream7->NDTR = count_of_data;
	DMA1_Stream7->CR	|= DMA_SxCR_EN;
	task->transaction_count_left--;
}

int i2c1_DMA_init(void)	{
	int returnCode = 0;
	int i;
	struct SSD1306_DMA_task *current_task;
	RCC->AHB1ENR				|=	RCC_AHB1ENR_DMA1EN;
	DMA1_Stream7->CR		 =	0;	//disable before cofigure
	while(I2C1->SR2	&		I2C_SR2_BUSY);
	I2C1->CR2 					|= I2C_CR2_DMAEN;
	DMA1_Stream7->PAR		 = (int) &I2C1->DR;
	DMA1_Stream7->CR		 = 1 << 25; //channel 1 switched
	DMA1_Stream7->CR		+= DMA_SxCR_DIR_0	+	DMA_SxCR_MINC + DMA_SxCR_TCIE;
	NVIC_SetPriority(DMA1_Stream7_IRQn, 10);
	NVIC_EnableIRQ(DMA1_Stream7_IRQn);
	currentXPosition = 0;
	currentYPosition = 0;
	for(i = 0, current_task = task_query; i < SSD1306_MAX_TASKS; i++, current_task++)
		current_task->operation = FREE;	//CLEAR DMA query
	currentTaskN = 0;
	return returnCode;
}