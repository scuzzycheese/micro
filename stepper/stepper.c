#include <avr/io.h>
#include <inttypes.h>
#define F_CPU 16000000UL  // 16 MHz
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>



typedef struct stpPin
{
	uint8_t pin;
	struct stpPin *next;
	struct stpPin *prev;
} stepPin;


stepPin stepper[4];
stepPin *step = &(stepper[0]);

void stepClockwise(int count)
{
	while(count --)
	{
		PORTC |= step->pin;
		_delay_ms(3);
		//turn on the next pin before turning off the current one
		PORTC |= step->next->pin;
		//now turn off the current one
		PORTC &= ~(step->pin);

		step = step->next;
	}
}

void stepCounterClockwise(int count)
{
	while(count --)
	{
		PORTC |= step->pin;
		_delay_ms(3);
		//turn on the next pin before turning off the current one
		PORTC |= step->prev->pin;
		//now turn off the current one
		PORTC &= ~(step->pin);

		step = step->prev;
	}
}

/* new style */
int main(void)
{
	DDRC = 0xFF;


	//The pin assignement should be done with defines for
	//reusability
	stepper[0].next = &(stepper[1]);	
	stepper[0].prev = &(stepper[3]);	
	stepper[0].pin = 1 << (0 + 2);

	stepper[1].next = &(stepper[2]);	
	stepper[1].prev = &(stepper[0]);	
	stepper[1].pin = 1 << (1 + 2);

	stepper[2].next = &(stepper[3]);	
	stepper[2].prev = &(stepper[1]);	
	stepper[2].pin = 1 << (2 + 2);

	stepper[3].next = &(stepper[0]);	
	stepper[3].prev = &(stepper[2]);	
	stepper[3].pin = 1 << (3 + 2);


	stepClockwise(10);
	stepCounterClockwise(10);
	stepClockwise(50);
	stepCounterClockwise(100);



	return 0;
}
