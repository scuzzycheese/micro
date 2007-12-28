#include <avr/io.h>
#include <inttypes.h>
#define F_CPU 16000000UL  // 16 MHz
#include <avr/delay.h>

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


	usart_init();
	char message[] = "Hello\r\n";
	int i;
	for(i = 0; i < 7; i ++)
	{
		putChar(message[i]);	
	}


	while(1)
	{

		/*none of this code can really work untill I redesign the circuit*/

		/*configure the ports carefully*/
		DDRB = 0xFF;
		PORTB = 0x0F;

		delay_ms(1);

		PORTB = 0xF0;
		delay_ms(1);

		PORTB = 1 << 0 | 1 << 2;
		DDRB = 1 << 1 | 1 << 3 | 1 << 4;	

		while(PINB & (1 << 0 | 1 << 2))
		{
			
		}



	}

	



	return 0;
}
