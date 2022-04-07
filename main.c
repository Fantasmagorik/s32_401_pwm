#include "stm32f4xx.h"                  // Device header
#include "hw_mcu.h"
#include "hw_ssd1306.h"
#include "hw_i2c.h"
#include "hw_dma.h"
#include "ws2812.h"
int CPU_FREQ =	84;	//Freq in MHz



extern struct protoFontInformation *font_arial16, *font_arial24;
extern char BLACK_COLOR;
char WHITE = 255;
												
char xPos = 0;
char yPos = 0;

int main(void)	{
	int returnCode = 0;
	int i = 0;
	periph_init();
	externalDevice_init();
	yPos = 7;
	xPos = 0;
	DMA_Print("555", 20, 3, font_arial24);
	//DMA_Print("W0z", 0, 0, font_arial16);
	DMA_Print("we here", 0, 0, font_arial16);
	
	while(1)	{
		ws2812_test();
		GPIOC->ODR ^= 1 << 13;
		SSD1306SetPixelColor(xPos, yPos);
		xPos += 1;
		//DMA_Fill(&BLACK_COLOR, 0, 50, 0, 2, 0);
		if(xPos > 126)	{
			xPos = 0;
			//SSD1306Fill(0, 127, 7, 1, 0);
			DMA_Fill(&BLACK_COLOR, 0, 127, yPos, 0, 0);
		}
		delay(200);
		//SSD1306Print("W0z", font_arial16, 0, 0);
		//DMA_Print("W0z", 0, 0, font_arial16);

	}
	return returnCode;
}

