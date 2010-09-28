#include "uart.h"
#ifndef X86
#else
#include <stdio.h>
#endif

void usart_init()
{
#ifndef X86
	unsigned int baudRate = SET_BAUD(38400);
	//unsigned int baudRate = 25;
	UBRR0L = baudRate;
	UBRR0H = baudRate >> 8;

	UCSR0B |= (1 << TXEN0); 
	//I don't think this makes much of a difference
	UCSR0C = ((1 << USBS0) | (3 << UCSZ00));
#endif
}

void putChar(uint8_t c)
{
#ifndef X86
	UDR0 = c;
	while(!(UCSR0A & (1 << UDRE0)));
	//clear the bit by writing a 1
	//UCSR0B = 1 << TXC0;
#endif
}

void writeLn(char *strn)
{
#ifndef X86
	while(*strn)
	{
		putChar(*(strn ++));
	}
#else
	printf(strn);
#endif

}

void writeLnLen(char *data, int len)
{
#ifndef X86
	while(len --)
	{
		putChar(*(data ++));
	}
#else
	while(len --)
	{
		printf("%c", *(data ++));
	}
#endif
}
