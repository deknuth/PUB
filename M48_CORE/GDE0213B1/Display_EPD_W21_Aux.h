#ifndef _DISPLAY_EPD_W21_AUX_H_
#define _DISPLAY_EPD_W21_AUX_H_
#include "main.h"

#define EPD_W21_MOSI_0	PORTD&=~(1<<4)
#define EPD_W21_MOSI_1	PORTD|=1<<4

#define EPD_W21_CLK_0	PORTD&=~(1<<2)
#define EPD_W21_CLK_1	PORTD|=1<<2

#define EPD_W21_CS_0	PORTD&=~(1<<3)
#define EPD_W21_CS_1	PORTD|=1<<3

#define EPD_W21_DC_0	PORTD&=~(1<<6)
#define EPD_W21_DC_1	PORTD|=1<<6

#define EPD_W21_RST_0	PORTD&=~(1<<5)
#define EPD_W21_RST_1	PORTD|=1<<5

#define EPD_W21_BUSY_LEVEL 0
#define isEPD_W21_BUSY (PIND&0x80) 

void SPI_Write(unsigned char value);

#endif

