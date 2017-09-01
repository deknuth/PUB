#include "main.h"

void PortInit(void)
{
    DDRB = 0B00000000;
    PORTB= 0B00000000;
    PINB = 0x00;

    DDRD = 0B01111100;		// PD5->RES	PD6->D/C PD7->BUSY PD4->SDI PD3->CS PD2->CLK
    PORTD= 0B00000000;
    PIND = 0x00;

    DDRC = 0B00111100;
    PORTC= 0B00000000;
    PINC = 0x00;
}

void UartInit(void)
{
    UBRR0H = (F_CPU / BAUD / 16 - 1) / 256;
    UBRR0L = (F_CPU / BAUD / 16 - 1) % 256;
    UCSR0B = 1<<RXEN0 | 1<<TXEN0 | 1<<RXCIE0;
    UCSR0C = 1<<UCSZ00 | 1<<UCSZ01;
}
void SendStr(unsigned char* data,unsigned char len)
{
    unsigned char i;
    for(i=0; i<len; i++)
    {
        while(!(UCSR0A & (1 << UDRE0)));
        UDR0 = *(data++);
    }
}

int main(void)
{
	PortInit();
	_delay_ms(200);
	while(1)
	{
		INIT_SPD2701();
		display(1);
		ReadBusy();
		INIT_SPD2701();
		display(2);
		ReadBusy();
		INIT_SPD2701();
		display(3);
		ReadBusy();
	}
}