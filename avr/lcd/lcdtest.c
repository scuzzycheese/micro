#include "global.h"
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include <stdio.h>
#include "i2c.h"
#include <avr/interrupt.h>

#include "lcd.h"

#define SET_BAUD(baudRate) (((F_CPU / baudRate) / 16L) - 1);

const uint16_t registerValues[18] = 
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

void usart_init()
{
	unsigned int baudRate = SET_BAUD(38400);

	UBRRL = baudRate;
	UBRRH = baudRate >> 8;

	/* Enable receiver and transmitter */
	UCSRB = (1 << RXEN) | (1 << TXEN);

	/* Set frame format: 8data, 0stop bit */
	UCSRC = (1 << URSEL) | (3 << UCSZ0);
}

void putChar(uint8_t c)
{
	UDR = c;
	while(!(UCSRA & (1 << TXC)));
	//clear the bit by writing a 1
	UCSRA = 1 << TXC;
}

unsigned char getChar()
{
	while(!(UCSRA & (1 << RXC)));
	return UDR;
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

	_delay_ms(1);

	sbi(TWCR, TWIE);

	return retReg;
}


uint16_t getRegister(uint8_t regNumber, uint8_t vola)
{
	static uint16_t internalRegs[18]; 
	//This is crazy, it doesn't work like the docco says
	if(vola)
	{
		//writeLn("Getting register set (volatile)...\r\n");
		uint8_t i;
		for(i = 0x0; i < 0x1d; i++)
		{
			internalRegs[i] = getRegister_helper(i);
			_delay_ms(5);
		}
		i2cSendStop();
	}
	return internalRegs[regNumber];
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
		//writeLn("Setting Register\r\n");
		uint8_t setBool = setRegister(i, regVals[i]);
		if(!setBool) writeLn("Device Not Responding\r\n");
		_delay_ms(1);
	}
	//writeLn("Setting Register\r\n");
	uint8_t setBool = setRegister(0, regVals[0]);
	if(!setBool) writeLn("Device Not Responding\r\n");
}

void tune(uint16_t freq)
{
	uint16_t reg1 = registerValues[1];
	uint16_t reg2 = registerValues[2];
	uint16_t reg3 = registerValues[3];

	freq -= 690;

	if(getRegister(17, 1) & (1 << 5))
	{
		writeLn("Radio ready for tuning...\r\n");
		
		//clear tune bit and chan bits
		reg2 &= ~(0x01FF | 0x0200);
		//set chan bits
		reg2 |= freq; 
		//clear seek bit 
		reg3 &= ~(1 << 14);

		//set space = 100k (seek stepping increments in 100k steps)
		reg3 |= (1 << 13);
		//set band to US/Europe
		reg3 &= ~(3 << 11);


		//send the registers to the chip
		setRegister(2, reg2);
		setRegister(3, reg3);

		//set tune bit
		reg2 |= (0x0200);

		//send the register to the chip
		setRegister(2, reg2);

		setRegister(1, reg1);



	}

}

void seek()
{
	uint16_t reg2 = registerValues[2];
	uint16_t reg3 = registerValues[3];

	if(getRegister(17, 1) & (1 << 5))
	{

		//clear tune bit
		//set chan bits
		reg2 = 0xB480;
	
		//clear seek bit 
		reg3 &= ~(1 << 14);
		//set seekup bit
		reg3 |= (1 << 15);
		//set space = 100k (seek stepping increments in 100k steps)
		reg3 |= (1 << 13);
		//set band to US/Europe
		reg3 &= ~(3 << 11);
	
		//send the registers to the chip
		setRegister(2, reg2);
		setRegister(3, reg3);
	
		//set the seek bit
		reg3 |= (1 << 14);
	
		//send the register to the chip
		setRegister(3, reg3);
	}
}
void vol(uint8_t volume)
{


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
		_delay_ms(50);
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

	lcdClear();
	lcdGotoXY(0, 0);
	lcdPrintData("X-FM", 4);

	_delay_ms(4000);

	setAllRegs((uint16_t *)registerValues);
	_delay_ms(100);

	//wait for radio to be ready after initialising
	while(!(getRegister(17, 1) & 0x0400))
	{
		writeLn("Waiting for STC...\r\n");
		_delay_ms(20);
	}

	_delay_ms(4000);
	writeLn("Seeking...\r\n");
	//tune();
	//seek();	
	
	_delay_ms(4000);

	while(!(getRegister(17, 1) & 0x0400))
	{
		writeLn("Waiting for STC...\r\n");
		_delay_ms(20);
	}

	writeLn("Done!\r\n");

	uint16_t freq = 860;
	while(1)
	{
		char c = getChar();
		if(c == 0x73)
		{
			writeLn("Seeking...");
			seek();	
			writeLn("Done.\r\n");
		}
		if(c == 0x75)
		{
			char strout[20];
			sprintf(strout, "FREQ: %d\r\n", freq ++);
			writeLn(strout);
			tune(freq);	
		}
		if(c == 0x64)
		{
			char strout[20];
			sprintf(strout, "FREQ: %d\r\n", freq --);
			writeLn(strout);
			tune(freq);	
		}
		if(c == 0x72)
		{
			//we need to do a volatile fetch
			getRegister(0, 1);
			uint8_t y;
			for(y = 0; y < 0x1d; y ++)
			{
				char outStr[30];
				sprintf(outStr, "REG: %0.2d - VAL: %0.4X\r\n", y, getRegister(y, 0));
				writeLn(outStr);
			}
		}
		if(c == 0x76)
		{
			vol(4);
		}
	}





/*

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
			_delay_ms(5);
			dispState.timer --;
		}
		else
		{
			dispState.timer = 255;
			dispState.state = STATION_STATE;
		}
	}
*/

	return 0;
}
