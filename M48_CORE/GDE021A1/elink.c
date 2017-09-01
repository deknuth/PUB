#include "main.h"
unsigned char init_data[90]={
	0x82,0x00,0x00,0x00,0xAA,0x00,0x00,0x00,
	0xAA,0xAA,0x00,0x00,0xAA,0xAA,0xAA,0x00,
	0x55,0xAA,0xAA,0x00,0x55,0x55,0x55,0x55,
	0xAA,0xAA,0xAA,0xAA,0x55,0x55,0x55,0x55,
	0xAA,0xAA,0xAA,0xAA,0x15,0x15,0x15,0x15,
	0x05,0x05,0x05,0x05,0x01,0x01,0x01,0x01,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x41,0x45,0xF1,0xFF,0x5F,0x55,0x01,0x00,
	0x00,0x00,
};

void SPI4W_WRITECOM(unsigned char data)
{
	unsigned char i;
	nCS_H; 
	nCS_L;
	SCLK_L;
	nDC_L;
	for(i=0; i<8; i++)
	{
		if(data&0x80)
			SDA_H;
		else
			SDA_L;
		_delay_us(1);
		SCLK_H;
		_delay_us(1);
		SCLK_L;
		data <<= 1;
	}
	nCS_H;
}

void SPI4W_WRITEDATA(unsigned char data)
{
	unsigned char i;
	nCS_H; 
	nCS_L;
	SCLK_L; 
	nDC_H;
	for(i=0; i<8; i++)
	{
		if(data&0x80)
			SDA_H;
		else
			SDA_L;
		_delay_us(1);
		SCLK_H;
		_delay_us(1);
		SCLK_L;
		data <<= 1;
	}
	nCS_H;
//	LED_BLINK;
}

void image_a10(void)
{
	int i;
	SPI4W_WRITECOM(0x24);
	for(i = 0; i < 3096; i++)
		SPI4W_WRITEDATA(0x00);
}

void image_a11(void)
{
	int i;
	SPI4W_WRITECOM(0x24);
	for(i = 0; i < 3096; i++)
		SPI4W_WRITEDATA(0xFF);
}

void image_a12(void)
{
	int i;
	SPI4W_WRITECOM(0x24);
	for(i = 0; i < 1548; i++)
		SPI4W_WRITEDATA(0xFF);
	for(i = 0; i < 1548; i++)
		SPI4W_WRITEDATA(0x00);
}

void MyRESET(void)
{
	nRST_L;
	_delay_ms(1);
	nRST_H;
	_delay_ms(1);
	LED_ON;
}

void ReadBusy(void)
{
	unsigned char i;
	while(1)
	{	 //=1 BUSY
		if(nBUSY == 0)
			break;
	}
//	for (i = 0; i < 30; i++)
//		_delay_ms(2000);
}


void WRITE_LUT(void)
{
	unsigned char i;
	SPI4W_WRITECOM(0x32);				// write LUT register
	for (i=0; i<90; i++)
		SPI4W_WRITEDATA(init_data[i]);	// write LUT register
}

void CloseBump(void)
{
	SPI4W_WRITECOM(0x22);	// display updata sequence option ,in page 33
	SPI4W_WRITEDATA(0x03);
	//ElinkSleep();
	SPI4W_WRITECOM(0x20);
}

void ElinkSleep(void)
{
	SPI4W_WRITECOM(0x10);
	SPI4W_WRITEDATA(0x01);
}

void display(unsigned char num)
{
	switch(num)
	{
		case 1:
			image_a12();
			break;
		case 2:
			image_a11();
			break;
		case 3:
			image_a10();
			break;
		default:
			break;
	}
	SPI4W_WRITECOM(0x20);
	_delay_ms(1);
	ReadBusy();
	_delay_ms(500);
	CloseBump();
	_delay_ms(2000);
}

void INIT_SPD2701(void)
{
	MyRESET();
	SPI4W_WRITECOM(0x10);	//exit deep sleep mode
	SPI4W_WRITEDATA(0x00);
	SPI4W_WRITECOM(0x11);	//data enter mode
	SPI4W_WRITEDATA(0x03);
	SPI4W_WRITECOM(0x44);	//set RAM x address start/end, in page 36
	SPI4W_WRITEDATA(0x00);	//RAM x address start at 00h;
	SPI4W_WRITEDATA(0x11);	//RAM x address end at 11h(17)->72: [because 1F(31)->128 and 12(18)->76] 

	SPI4W_WRITECOM(0x45);	//set RAM y address start/end, in page 37
	SPI4W_WRITEDATA(0x00);	//RAM y address start at 00h;
	SPI4W_WRITEDATA(0xAB);	//RAM y address start at ABh(171)->172: [because B3(179)->180]

	SPI4W_WRITECOM(0x4E);	//set RAM x address count to 0;
	SPI4W_WRITEDATA(0x00);
	SPI4W_WRITECOM(0x4F);	//set RAM y address count to 0;
	SPI4W_WRITEDATA(0xab);

	SPI4W_WRITECOM(0x21);
	SPI4W_WRITEDATA(0x03);
	SPI4W_WRITECOM(0xF0);	//booster feedback used, in page 37
	SPI4W_WRITEDATA(0x1F);

	SPI4W_WRITECOM(0x2C);	//vcom
	SPI4W_WRITEDATA(0xA0);

	SPI4W_WRITECOM(0x3C);	//board
	SPI4W_WRITEDATA(0x63);
	SPI4W_WRITECOM(0x22);	//display updata sequence option ,in page 33
	SPI4W_WRITEDATA(0xC4);	//enable sequence: clk -> CP -> LUT -> initial display -> pattern display
	WRITE_LUT();
}
