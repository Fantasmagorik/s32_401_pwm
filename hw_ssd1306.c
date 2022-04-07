#include "stm32f4xx.h"
#include "hw_ssd1306.h"
#include "hw_i2c.h"


struct protoFontInformation* Arial16Init(void);
struct protoFontInformation* Arial24Init(void);

struct protoFontInformation *font_arial16, *font_arial24;
	
#define SSD1306_MAX_STRING	20

char currentX, currentY;
char t0 = 0, t255 = 255;

int SSD1306_fonts_setup(void)	{
	font_arial16 = Arial16Init();
	font_arial24 = Arial24Init();
}

int SSD1306Init()	{
	char return_code;
	//char command_list[]=  {
	//0x2E, 0xA8, 0x3F/*0x3f*/, 0xD3, 0x00, 0x40, 0xA0/*1*/, 0xC0/*8*/, 0xDA, 0x12/*0x2*/,
	//0xdb, 0x40, 0x81, 0xfF, 0xA4, 0xA6, 0x20, 0, 0xD5, 0x80, 0x8D, 0x14, 0xAF 
	//};
		
	
	//0xae, 0xc8, 0, 0x10, 0x40, 0x81, 0xa1, 0xa6, 0xa8, 0x3f\
				//,0xa4, 0xd3, 0, 0xd5, 0xf0, 0xd9, 0xda, 0x12, 0xd8, 0x20, 0x8d, 0x14, 0xaf};
	char command_list[]=  {0x2E, 0xA8, 0x3F/*0x3f*/, 0xD3, 0x00, 0x40, 0xA1, 0xC8, 0xDA, 0x12/*0x2*/,
												0xdb, 0x40, 0x81, 0xfF, 0xA4, 0xA6, 0x20, 0, 0xD5, 0x80, 0x8D, 0x14, 0xAF };
	//char command_list[]= {0xa8, 0x3f, 0xd3, 0x00, 0x40, 0xA1, 0xC8, 0xDA, 0x2 , 0x81, 0xFF, 0xA4, 0xA6, 0xD5, 0x80, 0x8D, 0x14, 0xAF};
												/*	a8- Set Multiplex Ratio (0x3f); d3- Set Display Offset (0); 40- RAM Start Line Register; a1- Set Segment Remap (1- ENABLE); c8- Scan Direction REMAP; 
												DA- COM Pins Configuration (12): Alternative; 81- Contrast Control (ff): FULL; a4- Entire Display OFF, THROUGH RAM; a6- NORMAL / INVERSE : NORMAL; 
		20- Memory Addressing Mode (0): HORIZONTAL; d5- Clock Divide (80): ?; 8d- Charge Pump (14): ENABLE; af- Display ON;*/
												
	i2c1_sendAddress(SSD1306_Address);
	SSD1306SendCMD(sizeof(command_list)/*22*/, command_list);
	i2c1_stop();	
	currentX = 0;
	currentY = 0;
	SSD1306_fonts_setup();
	SSD1306FillAll(0);
	return return_code;											
} 

int SSD1306SendCMD(int counter, char *data)	{
	while(counter--)
	{
		i2c1_sendByte(SSD1306_MODE_COM);
		i2c1_sendByte(*data++);
	}
	return 0;
}

int SSD1306SetPixelColor(char xPosition, char yPosition)	{
	i2c1_sendAddress(SSD1306_Address);
	int byteCount = SSD1306SetWindow(xPosition, 0, yPosition, 1);
	i2c1_sendByte(SSD1306_MODE_DATA);
	i2c1_sendByte(128);
	i2c1_stop();
	return 0;
}

int SSD1306SetWindow(char xs, char x_length, char ys, char y_length)	{ //collumn Start, End  (0-127) and Page Start, End(0-7)
	char data[]= {0x21, xs, xs + x_length, 0x22, ys, ys + y_length};
	SSD1306SendCMD(6, data);
	return (x_length + 1) * (y_length + 1);
}

char SSD1306Fill(char xs, char xLen, char ys, char yLen, char data)	{
	long unsigned int counter;
	
	i2c1_sendAddress(SSD1306_Address);
	counter = SSD1306SetWindow(xs, xLen, ys, yLen); //change to return a count of data need to be transfered via the window
	i2c1_sendByte(SSD1306_MODE_DATs);
	while(counter--)
		i2c1_sendByte(data);
	i2c1_stop();
	return 0;
}

int SSD1306FillAll(char byte)	{
	int counter= (128*64) /8;	
	i2c1_sendAddress(SSD1306_Address);
	SSD1306SetWindow(0, 127, 0, 7);
	i2c1_sendByte(SSD1306_MODE_DATs);
	while(counter--)
		i2c1_sendByte(byte);
	i2c1_stop();
	return 0;
}

void SSD1306Print(char *text, struct protoFontInformation *font, char xPos, char yPos)	{
	int charCnt = 0;
	uint8_t *ptrByte;
	struct protoFontDescriptors *charInfo;
	int width, w_byte, bytesInLetter;
	currentX = xPos;
	currentY = yPos;
	while(*(text + charCnt) && charCnt < SSD1306_MAX_STRING)	{
		charInfo = (struct protoFontDescriptors*) font->addrFontDescriptor + *(text + charCnt) - font->firstCharCode;
		width		= charInfo->width;
		//w_byte	= width / 8+ ((width % 8)? 1 : 0); 
		ptrByte = (uint8_t*) (font->addrFontDataStart + charInfo->position);
		i2c1_sendAddress(SSD1306_Address);
		SSD1306SetWindow(currentX, charInfo->width - 1, currentY, font->height/8);
		bytesInLetter = width * font->height/8;
		currentX	+=	width + 3;

		i2c1_sendByte(SSD1306_MODE_DATs);
		while(bytesInLetter)	{
			i2c1_sendByte(*ptrByte++);
			bytesInLetter--;
		}
		i2c1_stop();
		charCnt++;
	}
}
