#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#ifndef _DS1302_H
#define _DS1302_H


struct ds1302
{
};

void DS1302Init(void);
void DS1302Reset(void);

//Configure your ports
#define DS1302_CLK PORTB1
#define DS1302_CLK_PORT PORTB
#define DS1302_CLK_DDR DDRB

#define DS1302_IO PORTB2
#define DS1302_IO_PORT PORTB
#define DS1302_IO_DDR DDRB
#define DS1302_IO_PIN PINB 

#define DS1302_CE PORTC6
#define DS1302_CE_PORT PORTC
#define DS1302_CE_DDR DDRC

#define DS1302_CLK_DELAY 5




#endif
