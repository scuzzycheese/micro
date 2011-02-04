#include <avr/io.h>
#include <inttypes.h>
#define F_CPU 16000000UL  // 16 MHz
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdlib.h>

#define NOSTATE 0
#define MODECYCLESTATE 1
#define INTENSITYCYCLESTATE 2

uint8_t sinArray[256] = 
{
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   2,   2,   3,   4,   4,   5,   6,   7,   9,
  10,  11,  12,  14,  15,  17,  18,  20,  22,  24,  25,  27,  29,  31,  34,  36,  38,  40,  43,  45,  47,
  50,  52,  55,  57,  60,  63,  66,  68,  71,  74,  77,  80,  83,  86,  89,  92,  95,  98, 101, 104, 107,
 110, 113, 116, 119, 123, 126, 129, 132, 135, 138, 141, 144, 148, 151, 154, 157, 160, 163, 166, 169, 172,
 175, 178, 181, 183, 186, 189, 192, 194, 197, 200, 202, 205, 207, 210, 212, 214, 217, 219, 221, 223, 225,
 227, 229, 231, 233, 235, 236, 238, 240, 241, 242, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 253,
 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 254, 254, 253, 253, 252, 251, 251, 250, 249,
 248, 246, 245, 244, 243, 241, 240, 238, 237, 235, 233, 231, 230, 228, 226, 224, 221, 219, 217, 215, 212,
 210, 208, 205, 203, 200, 198, 195, 192, 189, 187, 184, 181, 178, 175, 172, 169, 166, 163, 160, 157, 154,
 151, 148, 145, 142, 139, 136, 132, 129, 126, 123, 120, 117, 114, 111, 107, 104, 101,  98,  95,  92,  89,
  86,  83,  80,  77,  74,  72,  69,  66,  63,  61,  58,  55,  53,  50,  48,  45,  43,  41,  38,  36,  34,
  32,  30,  28,  26,  24,  22,  20,  19,  17,  15,  14,  13,  11,  10,   9,   8,   7,   6,   5,   4,   3,
   2,   2,   1,   1
};



volatile struct
{
	volatile uint8_t state;
	volatile uint8_t intensity;
} treeState = { NOSTATE, 10 };



ISR(INT0_vect)
{
	cli();

	PORTC = 0;

	//This is for the buttons. When we are in the interrupt,
	//we change the configureation, where all the pins
	//connected to he buttons are pulled high internally, and the
	//interrupt pin becomes an open sink , this way we can see
	//which button is pulled low when it's pressed.
	DDRD |= (1 << PORTD2);
	PORTD &= ~(1 << PORTD2);

	DDRD &= ~((1 << PORTD0) | (1 << PORTD1));
	PORTD |= (1 << PORTD0) | (1 << PORTD1);


	_delay_ms(50);

	if(!(PIND & 1))
	{
		treeState.state = MODECYCLESTATE;
	}
	if(!(PIND & 2))
	{
		//treeState.intensity -= 1;
	}

	//return to the normal configuration where the interrupt pin
	//is pulled high, and each button is an open sink, causing
	//the interrupt pin to be pulled low when you press a button
	//thereby triggering an interrupt.
	DDRD &= ~(1 << PORTD2);
	PORTD |= (1 << PORTD2);

	DDRD = (1 << PORTD0) | (1 << PORTD1);
	PORTD = ~((1 << PORTD0) | (1 << PORTD1));

	//clear any new interrupt flags
	GIFR |= 1 << INTF0;

	sei();
}

/* new style */
int main(void)
{

	DDRD = (1 << PORTD0) | (1 << PORTD1);
	PORTD = (1 << PORTD2);

	DDRC = 0xFF;


	MCUCR = (1 << ISC01);
	GIMSK  |= (1 << INT0);


	//power down the ADC conversion
	ACSR |= (1 << ACD);

	sei();

	
	int dutyCycle[3] = {0, 66, 200};
	int dutyInc[3] = {1, 2, 3};
	int dutyNumber = 3;
	int8_t slowDown = 0;
	int8_t slowDownCounter = 0;




	while(1)
	{

		while(1)
		{
			PORTC = 0;

			if(treeState.state == MODECYCLESTATE)
			{
				treeState.state = NOSTATE;
				break;
			}
		}


		while(1)
		{
			PORTC |= 14;

			if(treeState.state == MODECYCLESTATE)
			{
				treeState.state = NOSTATE;
				break;
			}
		}


		for(uint8_t i = 0; i < 5; i ++)
		{
			if(i == 0) slowDown = 100;
			if(i == 1) slowDown = 80;
			if(i == 2) slowDown = 50;
			if(i == 3) slowDown = 20;
			if(i == 4) slowDown = 10;

			while(1)
			{
				slowDownCounter ++;
				if(slowDownCounter >= slowDown)
				{
					for(int8_t i = 0; i < dutyNumber; i ++)
					{
						dutyCycle[i] += dutyInc[i];
					}
					slowDownCounter = 0;
				}
				for(int i = 0; i < 256; i ++)
				{
					if(i < sinArray[dutyCycle[0]]) PORTC |= 8;
					else PORTC &= ~(8);

					if(i < sinArray[dutyCycle[1]]) PORTC |= 4;
					else PORTC &= ~(4);

					if(i < sinArray[dutyCycle[2]]) PORTC |= 2;
					else PORTC &= ~(2);
				}
				for(int8_t i = 0; i < dutyNumber; i ++)
				{
					if(dutyCycle[i] >= 255) dutyCycle[i] = 0;
				}

				if(treeState.state == MODECYCLESTATE)
				{
					treeState.state = NOSTATE;
					break;
				}
			}
		}

	}

	return 0;
}

