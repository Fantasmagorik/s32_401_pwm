#include "stm32f4xx.h"
#include "hw_ssd1306.h"

int i2c1_DMA_init(void);

enum SSD1306_DMA_operation	{
	BLOCKED,
	PRINT,
	GRAPHIC,
	FREE
};

struct SSD1306_DMA_task{
	char operation;
	uint8_t posX;
	uint8_t posY;
	uint8_t lengthX;
	uint8_t heightY;
	char *ptr_data;
	char transaction_count_left;
	struct protoFontInformation *font;
};

typedef struct SSD1306_DMA_task SSD1306_DMA_Task;
void DMA1_Stream7_IRQHandler(void);
SSD1306_DMA_Task* SSD1306_get_DMA_task(char operation);
void DMA_Print(char *text, char xPos, char yPos, struct protoFontInformation *font);
void DMA_Fill(char *ptrData, char posX, char lengthX, char posY, char heightY, char MINC);