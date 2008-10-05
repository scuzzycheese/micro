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
#define NON 0
#define DUR 4000

uint16_t tune2[][2] =
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

uint16_t tune1[][2] = 
{
	{D5, DUR}, 
	{NON, 1}, 
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

void play_tone(uint16_t delay, uint16_t duration)
{
	uint16_t cycles = duration / (delay / 50);
	
	while(cycles > 0)
	{
		PORTC |= 1 << 2;
		delay_us(delay);
		PORTC &= ~(1 << 2);
		delay_us(delay);
		cycles --;
	}
}

#define MOTOR_ON PORTC |= 1 << 5
#define MOTOR_OFF PORTC &= ~(1 << 5);

/* new style */
int main(void)
{
	DDRC = 0xFF;
	DDRD = 0xFF;
	
	//Enable the input of these pins for the switch state controller
	DDRD &= ~(1 << 2);
	DDRD &= ~(1 << 3);

	//Turn on the output pin for the switch state controller
	PORTD = 1 << 4;

	PORTC = 0;
	//Always turn on the motor
	//MOTOR_ON;

	while(1)
	{
		MOTOR_ON;
		delay_ms(250);
		MOTOR_OFF;
		delay_ms(250);
		/*
		int tunePlace = 0;
		while(tune1[tunePlace][1])
		{
			//I'm going to add the state detection in this loop, it should be
			//accurate enough for a simple toy
			//NOTE: I don't need to bother with detecting the first state on the
			//switch, because the motor will ALWAYs turn, according to the controll
			//images on the switch
			if(PIND & (1 << 2)) 
			{
				//play_tone(tune1[tunePlace][0], tune1[tunePlace][1]);
				//PORTD |= 1 << 5;	
			}
			else
			{
				//PORTD &= ~(1 << 5);
			}

			tunePlace ++;
		}
		delay_ms(1000);
		*/
	}

	return 0;
}
