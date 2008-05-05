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

#define D5 851
#define E5 758
#define Fsh5 675
#define G5 637
#define A5 568
#define B5 506
#define C6 477
#define D6 425
#define DUR 40

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
	{G5, 2 * DUR}
}; 

void play_tone(uint16_t delay, uint8_t duration)
{
	uint16_t tmp = 100 * duration;
	uint16_t delaysm = delay / 50;
	uint16_t cycles = tmp / delaysm;
	
	while(cycles > 0)
	{
		PORTC |= 1 << 3;
		delay_us(delay);
		PORTC &= ~(1 << 3);
		delay_us(delay);
		cycles --;
	}
}

/* new style */
int main(void)
{
	DDRC = 0xFF;

	while(1)
	{
		int tuneLen = sizeof(tune1) / 2;
		int tunePlace = 0;
		while(tunePlace < tuneLen)
		{
			play_tone(tune1[tunePlace][0], tune1[tunePlace][1]);
			tunePlace ++;
		}
		delay_ms(1000);
	}

	return 0;
}
