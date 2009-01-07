#include "global.h"
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include <stdio.h>

#include "lcd.h"

#define SET_BAUD(baudRate) (((F_CPU / baudRate) / 16L) - 1);


uint16_t register_values[18] = 
{
	0xffff,
	0x5b15,
	0xF4B9,
	0x8012,
	0x0400,
	0x28aa,
	0x4400,
	0x1ee7,
	0x7141,
	0x007d,
	0x82ce,
	0x4f55,
	0x970c,
	0xb845,
	0xfc2d,
	0x8097,
	0x04a1,
	0xdf6a
};

#define SLA_W 0x20 //write address
#define SLA_R 0x21 //read address



void delay_ms(unsigned int ms)
/* delay for a minimum of <ms> */
{
	// we use a calibrated macro. This is more
	// accurate and not so much compiler dependent
	// as self made code.
	while(ms)
	{
		_delay_ms(0.96);
		ms--;
	}
}


void usart_init()
{
	unsigned int baudRate = SET_BAUD(38400);

	UBRRL = baudRate;
	UBRRH = baudRate >> 8;

	/* Enable receiver and transmitter */
	UCSRB = (1 << RXEN) | (1 << TXEN);

	/* Set frame format: 8data, 0stop bit */
	UCSRC = (1 << URSEL) | (3 << UCSZ0);
}

void putChar(uint8_t c)
{
	UDR = c;
	while(!(UCSRA & (1 << TXC)));
	//clear the bit by writing a 1
	UCSRA = 1 << TXC;
}

unsigned char getChar()
{
	while(!(UCSRA & (1 << RXC)));
	return UDR;
}

void writeLn(char *strn)
{
	while(*strn)
	{
		putChar(*(strn ++));
	}
}



/* new style */
int main(void)
{
	usart_init();
	writeLn("\r\nHello from LCD\r\n");

	lcdInit();
	lcdHome();

	lcdClear();
	lcdGotoXY(0, 0);
	while(1)
	{
		char let = getChar();
		lcdPrintData(&let, 1);
	}

	return 0;
}
