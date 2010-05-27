#define F_CPU 1200000UL  // 1.2 MHz

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>


const uint8_t __attribute__ ((progmem)) sinArray[64] =
{
	0,   0,   2,   5,   9,  15,  21,  29,
  37,  46,  56,  67,  79,  90, 103, 115,
 128, 140, 152, 165, 176, 188, 199, 209,
 218, 226, 234, 240, 246, 250, 253, 255,
 255, 255, 253, 250, 246, 240, 234, 226,
 218, 209, 199, 188, 176, 165, 152, 140,
 128, 115, 103,  90,  79,  67,  56,  46,
  37,  29,  21,  15,   9,   5,   2,   0,
};

int main(void)
{
	DDRB = 0xFF;
	
	uint8_t dutyInc = 0;
	uint8_t dutySlowDown = 20;
	uint8_t counter = 0;
	while(1)
	{
		counter ++;
		if(counter >= dutySlowDown)
		{
			dutyInc ++;
			counter = 0;
		}
		uint8_t dutyCycle = pgm_read_byte(&sinArray[dutyInc]);
		for(int i = 0; i < 256; i ++)
		{
			if(i < dutyCycle) PORTB |= (1 << 0) | (1 << 2) | (1 << 3) | (1 << 4);
			else PORTB &= ~((1 << 0) | (1 << 2) | (1 << 3) | (1 << 4));
		}
		if(dutyInc >= 63) dutyInc = 0;
	}

	return 0;
}

