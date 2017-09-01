#ifndef MAIN_H_
#define MAIN_H_
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <math.h>
#include <util/delay.h>
#include <util/twi.h>

#define LOW           0
#define HIGH          (!LOW)
#define FALSE         0
#define TRUE		  (!FALSE)	

#define setbit(x,y) x |= (1<<y)
#define clrbit(x,y) x &= ~(1<<y)

#define SDA_H  PORTD|=1<<4
#define SDA_L  PORTD&=~(1<<4)
#define SCLK_H PORTD|=1<<2
#define SCLK_L PORTD&=~(1<<2)
#define nCS_H  PORTD|=1<<3
#define nCS_L  PORTD&=~(1<<3)
#define nDC_H  PORTD|=1<<6
#define nDC_L  PORTD&=~(1<<6)
#define nRST_H PORTD|=1<<5
#define nRST_L PORTD&=~(1<<5)
#define nBUSY  (PIND&0x80)


#define	LED_ON		PORTC|=(1<<2)
#define	LED_OFF		PORTC&=~(1<<2)
#define	LED_BLINK	PORTC^=(1<<2)

#define BAUD	38400

extern void SendStr(unsigned char* data,unsigned char len);
extern void INIT_SPD2701(void);
extern void display(unsigned char num);
extern void ReadBusy(void);

#endif


