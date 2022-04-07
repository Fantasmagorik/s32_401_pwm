

/**///---CONSTANTS-----------//
/**/#define SSD1306_Address	 0x78
/**/
/**/#define SSD1306_MODE_COM 	0x80
/**/#define SSD1306_MODE_DATA 0xC0
/**/#define SSD1306_MODE_DATs 0x40
/**/
/**/#define SSD1306_POS_HOR_NORM		0
/**/#define SSD1306_POS_HOR_INVERT	0
/**/#define SSD1306_POS_VERT_NORM		0
/**/#define SSD1306_POS_VERT_INVERT 0

int SSD1306Init(void);
int SSD1306SendCMD(int DATA_COUNT, char *DATA_ADDR);

int SSD1306SetWindow(char x_s, char x_e, char y_s, char y_e);
int SSD1306FillAll(char byte);

//void SSD1306Fill(char xS, char xE, char yS, char yE, char data);

#ifndef FONT_STRUCT
#define FONT_STRUCT

		struct protoFontInformation	{
		char height;
		char firstCharCode;
		char lastCharCode;
		const char *addrFontDataStart;
		const struct protoFontDescriptors *addrFontDescriptor;
	};


		struct protoFontDescriptors	{
		unsigned width : 6;
		unsigned position : 12;
	};

#endif
void SSD1306Print(char *text, struct protoFontInformation *font, char, char);
char SSD1306Fill(char xs, char xLen, char ys, char yLen, char data)	;
int SSD1306SetPixelColor(char xPosition, char yPosition);