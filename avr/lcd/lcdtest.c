#include "global.h"
#include <avr/io.h>
#include <inttypes.h>
#include <avr/delay.h>

#include "lcd.h"

#define SET_BAUD(baudRate) (((F_CPU / baudRate) / 16L) - 1);


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
	//unsigned int baudRate = 25;
	UBRRL = baudRate;
	UBRRH = baudRate >> 8;

	UCSRB |= (1 << TXEN); 
	//I don't think this makes much of a difference
	UCSRC = ((1 << URSEL) | (3 << UCSZ0));
}

void putChar(uint8_t c)
{
	UDR = c;
	while(bit_is_clear(UCSRA, TXC));
	//clear the bit by writing a 1
	UCSRA = 1 << TXC;
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

	lcdInit();
	lcdHome();
	char *data = "this is an uber test and daine is a rock star";
	char *datP = data;
	int dataLen = 0;
	int counter = 0;
	char otherData[20];

	while(1)
	{
		lcdClear();
		dataLen = strlen(datP);
		lcdPrintData(datP, (dataLen > 20) ? 20 : dataLen);
		if(*datP) datP ++;
		else datP = data;

		lcdGotoXY(0, 2);
		sprintf(otherData, "Counter: %d", counter);
		lcdPrintData(otherData, strlen(otherData));
		delay_ms(1000);
		counter ++;

	}


	return 0;
}
