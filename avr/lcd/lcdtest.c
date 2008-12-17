#include "global.h"
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include <stdio.h>
#include "i2c.h"
#include <avr/interrupt.h>

#include "lcd.h"

#define SET_BAUD(baudRate) (((F_CPU / baudRate) / 16L) - 1);


uint16_t register_values[18] = 
{
	0xffff,
	0x5b15,
	0xF4B9,
	0x8012,
	0x0400,
	0x28aa,
	0x4400,
	0x1ee7,
	0x7141,
	0x007d,
	0x82ce,
	0x4f55,
	0x970c,
	0xb845,
	0xfc2d,
	0x8097,
	0x04a1,
	0xdf6a
};

#define SLA_W 0x20 //write address
#define SLA_R 0x21 //read address



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


void usart_init()
{
	unsigned int baudRate = SET_BAUD(38400);
	//unsigned int baudRate = 25;
	UBRRL = baudRate;
	UBRRH = baudRate >> 8;

	UCSRB |= (1 << TXEN); 
	//I don't think this makes much of a difference
	UCSRC = ((1 << URSEL) | (3 << UCSZ0));
}

void putChar(uint8_t c)
{
	UDR = c;
	while(bit_is_clear(UCSRA, TXC));
	//clear the bit by writing a 1
	UCSRA = 1 << TXC;
}

void writeLn(char *strn)
{
	while(*strn)
	{
		putChar(*(strn ++));
	}
}



uint16_t getRegister_helper(uint8_t regNumber)
{
	uint16_t retReg;
	cbi(TWCR, TWIE);

	i2cSendStart();
	i2cWaitForComplete();

	i2cSendByte(SLA_W);
	i2cWaitForComplete();

	i2cSendByte(regNumber);
	i2cWaitForComplete();

	i2cSendStart();
	i2cWaitForComplete();

	i2cSendByte(SLA_R);
	i2cWaitForComplete();

	if(inb(TWSR) == TW_MR_SLA_ACK)
	{
		i2cReceiveByte(TRUE);
		i2cWaitForComplete();
		uint8_t value = i2cGetReceivedByte();
		retReg = (value & 0x00FF) << 8;

		i2cReceiveByte(TRUE);
		i2cWaitForComplete();
		value = i2cGetReceivedByte();
		retReg |= (value & 0x00FF);
	}
	else
	{
		writeLn("Device Not Responding to READ operations\r\n");
	}

	delay_ms(1);

	sbi(TWCR, TWIE);

	return retReg;
}


uint16_t getRegister(uint8_t regNumber)
{
	uint16_t retReg = 0;
	//This is crazy, it doesn't work like the docco says
	uint8_t i;
	for(i = 0x0; i < 0x1d; i++)
	{
		uint16_t inReg = getRegister_helper(i);
		delay_ms(5);
		if(regNumber == i) retReg = inReg;
	}
	i2cSendStop();
	return retReg;
}


uint8_t setRegister(uint8_t regNumber, uint16_t regValue)
{
	cbi(TWCR, TWIE);

	uint8_t retVal = 1;
	i2cSendStart();
	_delay_us(10);
	i2cWaitForComplete();

	i2cSendByte(SLA_W);
	i2cWaitForComplete();
	_delay_us(10);

	if(inb(TWSR) == TW_MT_SLA_ACK)
	{
		i2cSendByte(regNumber);
		i2cWaitForComplete();
	_delay_us(10);
		
		uint8_t value = (regValue & 0xFF00) >> 8;
		i2cSendByte(value);
		i2cWaitForComplete();
	_delay_us(10);

		value = (regValue & 0x00FF);
		i2cSendByte(value);
		i2cWaitForComplete();
	_delay_us(10);
	}
	else
	{
		retVal = 0;
	}

	i2cSendStop();
	_delay_us(10);

	sbi(TWCR, TWIE);

	return retVal;
}



void setAllRegs(uint16_t regVals[])
{
	uint8_t i;
	for(i = 1; i < 18; i ++)
	{
		writeLn("Setting Register\r\n");
		uint8_t setBool = setRegister(i, regVals[i]);
		if(setBool) writeLn("Device Responding\r\n");
		else writeLn("Device Not Responding\r\n");
		delay_ms(1);
	}
	setRegister(0, regVals[0]);
}

void tune()
{

	writeLn("Getting regs...\r\n");

	uint16_t R0 = getRegister(0);
	uint16_t R1 = getRegister(1);
	uint16_t R2 = getRegister(2);
	uint16_t R3 = getRegister(3);
	uint16_t R17 = getRegister(17);


	char strOut[20];
	sprintf(strOut, "REGB0: %0.4X\r\n", R0);
	writeLn(strOut);
	sprintf(strOut, "REGB1: %0.4X\r\n", R1);
	writeLn(strOut);
	sprintf(strOut, "REGB2: %0.4X\r\n", R2);
	writeLn(strOut);
	sprintf(strOut, "REGB3: %0.4X\r\n", R3);
	writeLn(strOut);
	sprintf(strOut, "REGB17: %0.4X\r\n", R17);
	writeLn(strOut);


	//(88.40Mhz)
	uint16_t freq = 194;


	writeLn("Done.\r\n");

	if(R17 & 0x0400)
	{
		writeLn("Radio ready for tuning...\r\n");
		
		//set hmute bit
		R1 |= 0x40;
		setRegister(1, R1);

		//clean tune bit
		R2 &= ~(1);
		setRegister(2, R2);

		//clear seek bit
		R3 &= ~(2);
		setRegister(3, R3);

		//set band and space bits
		R3 &= ~(3 << 3);
		R3 |= (1 << 2);
		setRegister(3, R3);

		//set Band
		//clear the chan bits
		R2 &= ~(0x1FF << 1);
		//set the band bits
		R2 |= (freq << 1);
		sprintf(strOut, "REG2-T: %0.4X\r\n", R2);
		writeLn(strOut);
		setRegister(2, R2);

		//set tune bit
		R2 |= 1;
		setRegister(2, R2);

		writeLn("Waiting for STC...\r\n");
		while(!(getRegister(17) & 0x0400))
		{
			writeLn("Waiting for STC...\r\n");
			delay_ms(20);
		}
		writeLn("done.\r\n");

		//clear the hmute bit
		R1 &= ~(0x40);
		setRegister(1, R1);

		writeLn("Finished Tuning.\r\n");

	}

	R1 = getRegister(1);
	R2 = getRegister(2);
	R3 = getRegister(3);
	R17 = getRegister(17);


	sprintf(strOut, "REGA1: %0.4X\r\n", R1);
	writeLn(strOut);
	sprintf(strOut, "REGA2: %0.4X\r\n", R2);
	writeLn(strOut);
	sprintf(strOut, "REGA3: %0.4X\r\n", R3);
	writeLn(strOut);
	sprintf(strOut, "REGA17: %0.4X\r\n", R17);
	writeLn(strOut);
}

void seek()
{
	register_values[2] = 0xB480;
	register_values[3] = 0xA001;
	setAllRegs(register_values);
	register_values[3] = 0xE001;
	setAllRegs(register_values);
}

#define STATION_STATE 0
#define VOLUME_STATE 1
#define NO_STATE 2

#define STATE_UNCHANGED 0
#define STATE_CHANGED 1

struct displayState
{
	uint8_t volume;
	uint8_t state;
	uint8_t timer;
} dispState;

ISR(INT0_vect)
{
	cli();
	if(PINC & 2)
	{
		delay_ms(50);
		if(PINC & 2)
		{
			writeLn("button pressed\r\n");
			
			dispState.state = VOLUME_STATE;
			dispState.timer = 255;
		}
	}
	sei();
}

/* new style */
int main(void)
{
	usart_init();
	writeLn("Hello from LCD\r\n");

	MCUCR = (1 << ISC01) | (1 << ISC00);
	//MCUCR = (1 << ISC00);

	GIMSK  |= (1 << INT0);
	sei();

	i2cInit();

	lcdInit();
	lcdHome();

/*
	setAllRegs(register_values);
	delay_ms(100);

	seek();	
	delay_ms(100);

	
	while(!(getRegister(17) & 0x0400))
	{
		writeLn("Waiting for STC...\r\n");
		delay_ms(20);
	}

	uint16_t R17 = getRegister(17);

	char outStr[20];
	sprintf(outStr, "R17: %0.4X\r\n");
	writeLn(outStr);
*/


	dispState.state = STATION_STATE;
	dispState.timer = 0;

	//enable internal pullup on pin 1 of port C
	//PORTC |= 2;
	//output in pin 1 of port C
	//DDRC |= 2;
	DDRC = 0;


	while(1)
	{
		if(dispState.state == STATION_STATE)
		{
			lcdClear();
			lcdGotoXY(0, 0);
			lcdPrintData("X-FM", 4);

			//don't thrash this state
			dispState.state = NO_STATE;
		}
		if(dispState.state == VOLUME_STATE)
		{
			lcdClear();
			lcdGotoXY(0, 0);
			lcdPrintData("VOLUME", 6);

			//don't thrash this state
			dispState.state = NO_STATE;
			dispState.timer = 255;
		}
		//decrease the counter, and then drop to the default state
		if(dispState.timer > 0)
		{
			delay_ms(5);
			dispState.timer --;
		}
		else
		{
			dispState.timer = 255;
			dispState.state = STATION_STATE;
		}
	}


	return 0;
}
