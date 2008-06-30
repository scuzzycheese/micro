#include "uart.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <stdio.h>
//FUSES - HFUSE:99 LFUSE:EF

void WDT_off(void) __attribute__((naked)) __attribute__((section(".init3")));
void WDT_off(void) 
{ 
	cli();
	wdt_reset();
	/* Clear WDRF in MCUSR */ 
	MCUSR &= ~(1<<WDRF); 
	/* Write logical one to WDCE and WDE */ 
	/* Keep old prescaler setting to prevent unintentional time-out */ 
	WDTCSR |= (1<<WDCE) | (1<<WDE); 
	/* Turn off WDT */ 
	WDTCSR = 0x00; 
	sei();
}


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

struct CORO_STATE
{
	int state;
	void *resume;
};

int yielder()
{
	static int time = 0;

	if(time > 5)
	{
		time = 0;
		return 1;
	}
	time ++;
	return 0;
}

#define CORO_START static struct CORO_STATE pt = {0, NULL}; if(pt.resume) { writeLn("Resuming\r\n"); goto *pt.resume; }
#define CORO_YIELD { __label__ resume; resume: pt.resume = &&resume; } if(yielder()) return 0


int func1();
int func2();
int main()
{

	usart_init();

	int (*coFunc1)() = func1;
	int (*coFunc2)() = func2;
	while(1)
	{
		coFunc1();
		coFunc2();
		//func1();
		//func2();
	}
}


int func1()
{
	CORO_START;
	int static state = 0;
	int static blah = 0;
	writeLn("I should not get called when resuming\r\n");
	while(1)
	{
		CORO_YIELD;

		char buffer[20];
		sprintf(buffer, "hello from func1: %d\r\n", blah ++);
		writeLn(buffer);

		//delay_ms(1000);
	}
}

int func2()
{
	CORO_START;
	int static state = 0;
	int static blah = 0;
	writeLn("I should not get called when resuming\r\n");
	while(1)
	{
		CORO_YIELD;

		char buffer[20];
		sprintf(buffer, "hello from func2: %d\r\n", blah ++);
		writeLn(buffer);

		//delay_ms(1000);
	}
}

