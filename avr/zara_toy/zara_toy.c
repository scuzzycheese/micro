#include <avr/io.h>
#include <inttypes.h>
#define F_CPU 16000000UL  // 16 MHz
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#define _NOP() asm volatile("nop")

void delay_ms(unsigned int n)
{
	while(n --)
	{
		_delay_ms(0.96);
	}
}

//This is a rough guess at a uS delay routine
//16Mhz = 16 nop's - 2 (compare, jmp and 
void delay_us(unsigned int n)
{
	while(n --)
	{
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
	}
}

#define A5 568
#define B5 506
#define C6 477
#define D5 851
#define E5 758
#define F5 716
#define Fsh5 675
#define G5 637
#define D6 425
#define C5 956
#define DUR 40

int tune2[][2] =
{
	{G5, DUR * 2},
	{B5, DUR * 2},
	{C5, DUR * 2},
	{B5, DUR * 2},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
};

int tune1[][2] = 
{
	{D5, DUR}, 
	{E5, DUR}, 
	{D5, DUR}, 
	{G5, DUR}, 
	{Fsh5, 2 * DUR}, 

	{D5, DUR}, 
	{E5, DUR},
	{D5, DUR},
	{A5, DUR},
	{G5, 2 * DUR},

	{D5, DUR},
	{D6, DUR},
	{B5, DUR},
	{G5, DUR},
	{Fsh5, DUR},
	{E5, DUR},

	{C6, DUR},
	{B5, DUR},
	{G5, DUR},
	{A5, DUR},
	{G5, 2 * DUR},
	{0, 0}
}; 

void play_tone(uint16_t delay, uint8_t duration)
{
	uint16_t tmp = 100 * duration;
	uint16_t delaysm = delay / 50;
	uint16_t cycles = tmp / delaysm;
	
	while(cycles > 0)
	{
		PORTC |= 1 << 2;
		delay_us(delay);
		PORTC &= ~(1 << 2);
		delay_us(delay);
		cycles --;
	}
}

/* new style */
int main(void)
{
	DDRC = 0xFF;
	DDRD = 0xFF;

	PORTC = 0;

	while(1)
	{
		int tunePlace = 0;
		while(tune1[tunePlace][1])
		{
			//play_tone(tune1[tunePlace][0], tune1[tunePlace][1]);
			tunePlace ++;
		}
		delay_ms(1000);
		PORTD = 1 << 5;	
		PORTC |= 1 << 5;
		delay_ms(1000);
		PORTD = 0;
		PORTC &= ~(1 << 5);
	}

	return 0;
}
