#include <avr/io.h>
#include <inttypes.h>
#define F_CPU 16000000UL  // 16 MHz
#include <util/delay.h>

void delay_ms(unsigned int n)
{
	while(n --)
	{
		_delay_ms(0.96);
	}
}

/* new style */
int main(void)
{
	DDRC = 0xFF;
	while(1)
	{
		PORTC = 0;
		delay_ms(1000);
		PORTC = 1 << 4;
		delay_ms(1000);
	}
	return 0;
}
