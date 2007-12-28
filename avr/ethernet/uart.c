#include "uart.h"

void usart_init()
{
	unsigned int baudRate = SET_BAUD(38400);
	//unsigned int baudRate = 25;
	UBRR0L = baudRate;
	UBRR0H = baudRate >> 8;

	UCSR0B |= (1 << TXEN0); 
	//I don't think this makes much of a difference
	UCSR0C = ((1 << USBS0) | (3 << UCSZ00));
}

inline void putChar(uint8_t c)
{
	UDR0 = c;
	while(!(UCSR0A & (1 << UDRE0)));
	//clear the bit by writing a 1
	//UCSR0B = 1 << TXC0;
}

void writeLn(char *strn)
{
	while(*strn)
	{
		putChar(*(strn ++));
	}
}

void writeLnLen(char *data, int len)
{
	while(len --)
	{
		putChar(*data);
	}
}

