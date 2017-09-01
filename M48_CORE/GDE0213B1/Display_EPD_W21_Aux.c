#include "Display_EPD_W21_Aux.h"

void SPI_Write(unsigned char value)                                    
{                                                           
    unsigned char i;
    for(i=0; i<8; i++)   
    {
        EPD_W21_CLK_0;
        if(value & 0x80)
        	EPD_W21_MOSI_1;
        else
        	EPD_W21_MOSI_0;	
        value = (value << 1);
		_delay_us(5);
        EPD_W21_CLK_1;
		_delay_us(5);
    }
}
