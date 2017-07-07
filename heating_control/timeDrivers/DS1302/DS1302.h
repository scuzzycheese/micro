#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#ifndef _DS1302_H
#define _DS1302_H


struct time
{
   uint8_t seconds;
   uint8_t minutes;
   uint8_t hours;
   uint8_t dayOfMonth;
   uint8_t month;
   uint8_t dayOfWeek;
   uint16_t year;
   uint8_t wp;
};

void DS1302Init(void);
void DS1302Reset(void);

//Configure your ports
#define DS1302_CLK PORTB0
#define DS1302_CLK_PORT PORTB
#define DS1302_CLK_DDR DDRB

#define DS1302_IO PORTB1
#define DS1302_IO_PORT PORTB
#define DS1302_IO_DDR DDRB
#define DS1302_IO_PIN PINB 

#define DS1302_CE PORTC6
#define DS1302_CE_PORT PORTC
#define DS1302_CE_DDR DDRC

#define DS1302_CLK_DELAY 500





void DS1302Stop(void);
void DS1302Start(void); 


void DS1302WriteByte(unsigned char commandByte, unsigned char byte);
unsigned char DS1302ReadByte(unsigned char commandByte);
uint8_t DS1302ReadSeconds(void);
uint8_t DS1302ReadMinutes(void);
uint8_t DS1302ReadHours(void);
uint8_t DS1302ReadDayOfMonth(void);
uint8_t DS1302ReadMonth(void);
uint8_t DS1302ReadDayOfWeek(void);
uint16_t DS1302ReadYear(void);
uint8_t DS1302ReadWP(void);

struct time DS1302ReadClock(void);

#endif
