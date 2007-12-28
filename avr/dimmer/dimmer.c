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

#define INC_BRIGHT 1
#define DEC_BRIGHT 0

/* new style */
int main(void)
{


	char data[20];

	/* INITIALIZE */
	/* enable PC5 as output */
	DDRB |= 0xFF;
	DDRC |= 0xFF;
	PORTC = 0;
	PORTB = 0;


	int dimValue[8] = {0, 32, 64, 96, 128, 160, 192, 224};
	int i;
	int j;

	int mootCounter = 0;
	int lights = 0;
	int onner = 0;

	while(1)
	{

		for(i = 0; i < 256; i ++)
		{
			for(j = 0; j < 8; j ++)
			{
				if(i < dimValue[j]) lights = 1 << j;
				else lights &= ~(1 << j);
				PORTC = (lights & 0xF0) >> 4;
				PORTB = (lights & 0x0F);	
			}
		}

		
		mootCounter ++;
		if(mootCounter >= 50)
		{
			if(onner > 7) onner = 0;
			dimValue[onner] = 255;
			onner ++;
			mootCounter = 0;
		}
		
		for(j = 0; j < 8; j ++)
		{
			if(dimValue[j] > 0)
			{
				dimValue[j] --;
				//dimValue[j] = 255;
			}
		}
	}
	return 0;
}
