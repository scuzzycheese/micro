/**
 *  Copyright (c) 2010 Daine Mamacos <daine.mamacos@reverseorder.net>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "global.h"
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <string.h>

#include "lcd.h"
#include "ar1010.h"

#include "i2c.h"

#include <compat/twi.h>


#define NO_STATE 0
#define STATION_STATE 1
#define VOLUME_STATE 2
#define SEEK_STATE 3
#define FREQ_STATE 4
#define UART_STATE 5
#define VOLUME_UP_STATE 6
#define VOLUME_DOWN_STATE 7
#define SLEEP_STATE 8



struct displayState
{
	volatile int8_t sleepTimer;
	uint8_t state;
	int8_t timer;
} dispState = { 0, SEEK_STATE, 3 };


//interrupt to catch button presses
ISR(INT0_vect)
{
	cli();

	//This is for the buttons. When we are in the interrupt,
	//we change the configureation, where all the pins
	//connected to he buttons are pulled high internally, and the
	//interrupt pin becomes an open sink , this way we can see
	//which button is pulled low when it's pressed.
	DDRD |= (1 << PORTD2);
	PORTD &= ~(1 << PORTD2);

	DDRC &= ~((1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3));
	PORTC |= (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3);


	_delay_ms(50);
	if(!(PINC & 2))
	{
		dispState.state = SEEK_STATE;
	}
	if(!(PINC & 4))
	{
		dispState.state = VOLUME_UP_STATE;
	}
	if(!(PINC & 8))
	{
		dispState.state = VOLUME_DOWN_STATE;
	}

	//Reset sleep timer
	dispState.sleepTimer = 0;


	//return to the normal configuration where the interrupt pin
	//is pulled high, and each button is an open sink, causing
	//the interrupt pin to be pulled low when you press a button
	//thereby triggering an interrupt.
	DDRD &= ~(1 << PORTD2);
	PORTD |= (1 << PORTD2);

	DDRC = (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3);
	PORTC = ~((1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3));

	//clear any new interrupt flags
	GIFR |= 1 << INTF0;

	sei();
}

ISR(TIMER1_COMPA_vect)
{
	cli();
	//de-increment the timer every second
	dispState.timer --;
	dispState.sleepTimer ++;
	if(dispState.sleepTimer >= 20)
	{
		dispState.state = SLEEP_STATE;
		dispState.sleepTimer = 0;
		dispState.timer = 3;
	}
	sei();
}

int main(void)
{

	DDRD = (1 << PORT0);
	PORTD = (1 << PORTD2) | (1 << PORTD0);

	DDRC = (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3);
	PORTC = ~((1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3));

	MCUCR = (1 << ISC01);
	GIMSK  |= (1 << INT0);


	//power down the ADC conversion
	ACSR |= (1 << ACD);

	sei();

	//enable the pullups for these pins, for the i2c bus
	PORTC |= (1 << 4);
	PORTC |= (1 << 5);
	i2c_init();


	lcdInit();
	lcdHome();

	lcdClear();
	lcdGotoXY(0, 0);
	lcdPrintData("RADIO", 5);

	ar1010Init();
	_delay_ms(10);

	ar1010WaitForReady();

	//Set up out timer interrupt to fire every second 
	TIMSK = 1 << OCIE1A;
	TCCR1B = 1 << CS12 | 1 << WGM12;      // CTC mode, TOP = OCR1A
	OCR1A = 62500;

	
	_delay_ms(10);
	uint8_t vol = 10;
	ar1010Volume(vol);

	while(1)
	{
		//nominalise the volume
		if(vol >= 21) vol = 21;
		if(vol <= 0) vol = 0;

		switch(dispState.state)
		{

			case VOLUME_UP_STATE:
			{
				++ vol;
				dispState.state = VOLUME_STATE;
				dispState.timer = 3;
				ar1010Volume(vol);
			}
			break;

			case VOLUME_DOWN_STATE:
			{
				-- vol;
				dispState.state = VOLUME_STATE;
				dispState.timer = 3;
				ar1010Volume(vol);
			}
			break;

			case VOLUME_STATE:
			{
				lcdClear();
				lcdGotoXY(0, 0);
				lcdPrintData("VOLUME", 6);
				lcdGotoXY(0, 1);
				lcdProgressBar(vol, 21, 20);
	
				//don't thrash this state
				dispState.state = NO_STATE;
				dispState.timer = 3;
			}
			break;

			case SEEK_STATE:
			{
				lcdClear();
				lcdGotoXY(0, 0);
				lcdPrintData("SEEKING...", 10);
	
				ar1010Seek();
	
				//drop to the default state as soon as we are finished seeking
				dispState.state = NO_STATE;
				dispState.timer = 0;
			}
			break;

			case FREQ_STATE:
			{
				uint16_t curFreq = ar1010getCurFreq();

				char strOut[20];
				lcdClear();
				lcdGotoXY(0, 0);
				sprintf(strOut, "%d", curFreq / 10);
				lcdPrintData(strOut, strlen(strOut));
	
				//Some nasty hackery doo, to get fixed point decimal place
				sprintf(strOut, ".%d Mhz", curFreq - ((curFreq / 10) * 10));
				lcdPrintData(strOut, strlen(strOut));

				//if I've been here too long, then go to sleep
				dispState.state = NO_STATE;
				dispState.timer = 20;
			}
			break;
			
			case SLEEP_STATE:
			{
				lcdGotoXY(0, 1);
				lcdPrintData("Sleeping", 8);
				
				//disable interrupts (race condition might occur)
				cli();
				//Set the sleep mode and type (idle mode)
				MCUCR |= (1 << SE);
				//disable the timer interrupt
				TIMSK &= ~(1 << OCIE1A);
				//switch off LCD
				PORTD &= ~(1 << PORTD0);
				//re-enable interrupts
				sei();
				sleep_cpu();
				//disable sleem mode
				MCUCR &= ~(1 << SE);
				//re-enable the timer interrupt
				TIMSK |= (1 << OCIE1A);
				//switch on LCD
				PORTD |= (1 << PORTD0);

				//when the interrupt fires, it sets the state
				//dispState.state = NO_STATE;
				dispState.timer = 3;
			}
			break;
			default:
			break;

		}

		//Don't let this thrash
		if(dispState.timer > 0)
		{
			_delay_ms(1);
		}
		else
		{
			dispState.timer = 3;
			dispState.state = FREQ_STATE;
		}
	}


	return 0;
}
