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


	char data[20];

	/* INITIALIZE */
	/* enable PC5 as output */
	DDRC |= 1 << DDC5;
	PORTC = 0;
	uint32_t loops;
	char measureState = 0;
	char state = 0;



	/* PC5 is 5 (see file include/avr/iom8.h) and 1<<PC5 is 00100000 
	* This can also be written as _BV(PC5)*/
	while(1)
	{
		loops = 0;
		/*charge the loader LED*/
		PORTC = 1 << 2;
		//PORTC = 0;
		DDRC = 0xFF;

		/*pin 5 output, 4 as ground*/
		PORTC |= 1 << 5;
		
		delay_ms(1);

		/*pin 4 output, 5 as ground*/
		PORTC |= 1 << 4;
		PORTC &= ~(1 << 5);

		delay_ms(1);

		DDRC &= ~(1 << 4);
		PORTC &= ~(1 << 4);
		
		/*measure capacitance of the LED*/
		while(PINC & (1 << 4))
		{
			if(loops > 999) break;
			loops ++;
		}

		
		static uint32_t smoother = 0;
		static int j = 0;
		smoother += loops;
		static uint32_t holderVal;

		if(j > 10)
		{
			holderVal = (smoother/ j);
			/*operate our switch*/
			if(holderVal >= 100)
			{
				measureState = 1;
			}
			if(holderVal <= 100 && measureState == 1)
			{
				//sprintf(data, "%d\r\n", holderVal);
				//writeLn(data);
				if(state == 0)
				{
					state = 1;
					writeLn("On\r\n");
					//delay_ms(500);
				}
				else
				{
					state = 0;
					writeLn("Off\r\n");
					//delay_ms(500);
				}
				measureState = 0;
			}
			smoother = 0;
			j = 0;
		}		
		j++;


		/*this code is to smooth stuff over*/
		/*
		static uint32_t summer = 0;
		static uint32_t j = 0;
		summer += loops;
		if(j >= 20)
		{
			sprintf(data, "%d\r\n", (summer / j));
			int leng = strlen(data);
			for(i = 0; i < leng; i ++)
			{
				putChar(data[i]);
			}
			j = 0;
			summer = 0;
		}
		j ++;
		*/
		

		/*				
		sprintf(data, "%d\r\n", loops);
		int leng = strlen(data);
		for(i = 0; i < leng; i ++)
		{
			putChar(data[i]);
		}
		*/
	

	}
	return 0;
}
