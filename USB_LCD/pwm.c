#include <avr/io.h>

volatile uint8_t ocTmp = 0x7F;
//These are all just stubs
void initPWM()
{

	DDRB |= (1 << PORTB5);

	//Fast PWM, 8-bit
	TCCR1A |= (1 << WGM10);
	TCCR1A |= (1 << COM1A1);

	TCCR1B |= (1 << CS10) | (1 << WGM12);

	OCR1A = ocTmp;
}

void increasePWM()
{
	ocTmp += 1;
	OCR1A = ocTmp;
}

void decreasePWM()
{
	ocTmp -= 1;
	OCR1A = ocTmp;
}