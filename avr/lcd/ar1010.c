#include "global.h"

#include "ar1010.h"
//#include "i2c.h"
#include <avr/io.h>
#include <util/delay.h>

#include <string.h>
#include <stdio.h>
#include "i2cmaster.h"

#include <compat/twi.h>


extern uint16_t curFreq;

extern uint16_t registerValues[18];


void ar1010Init()
{
	setAllRegs((uint16_t *)registerValues);
}

uint16_t getRegister_helper(uint8_t regNumber)
{
	uint16_t retReg;

	i2c_start();
	i2c_waitForComplete();

	i2c_write(SLA_W);
	i2c_waitForComplete();

	i2c_write(regNumber);
	i2c_waitForComplete();

	i2c_start();
	i2c_waitForComplete();

	i2c_write(SLA_R);
	i2c_waitForComplete();

	if(TWSR == TW_MR_SLA_ACK)
	{
		uint8_t value = i2c_read();
		retReg = (value & 0x00FF) << 8;

		value = i2c_read();
		retReg |= (value & 0x00FF);
	}
	else
	{
		//writeLn("Device Not Responding to READ operations\r\n");
	}

	return retReg;
}


uint16_t getRegister(uint8_t regNumber, uint8_t vola)
{
	static uint16_t internalRegs[29];
	//This is crazy, it doesn't work like the docco says
	if(vola)
	{
		uint8_t i;
		for(i = 0x0; i < 0x1d; i++)
		{
			internalRegs[i] = getRegister_helper(i);
			_delay_ms(5);
		}
		i2c_stop();
		i2c_waitForComplete();
	}
	return internalRegs[regNumber];
}


uint8_t setRegister(uint8_t regNumber, uint16_t regValue)
{

	uint8_t retVal = 1;
	i2c_start();
	i2c_waitForComplete();

	i2c_write(SLA_W);
	i2c_waitForComplete();

	if(TWSR == TW_MT_SLA_ACK)
	{
		i2c_write(regNumber);
		i2c_waitForComplete();
		_delay_us(2);

		uint8_t value = (regValue & 0xFF00) >> 8;
		i2c_write(value);
		i2c_waitForComplete();
		_delay_us(2);

		value = (regValue & 0x00FF);
		i2c_write(value);
		i2c_waitForComplete();
		_delay_us(2);
	}
	else
	{
		retVal = 0;
	}

	i2c_stop();
	_delay_us(2);


	return retVal;
}



void setAllRegs(uint16_t *regVals)
{
	uint8_t i;
	for(i = 1; i < 18; i ++)
	{
		setRegister(i, regVals[i]);
		_delay_ms(1);
	}
	setRegister(0, regVals[0]);
}

//TODO: re-add the getCurFreq function back here


//Nasty little blocking function, oh well.
void ar1010WaitForReady()
{
	//wait for radio to be ready after initialising
	while(!(getRegister(19, 1) & (1 << 5)))
	{
		_delay_ms(10);
	}
}


void ar1010Tune(uint16_t freq)
{
	uint16_t reg1 = registerValues[1];
	uint16_t reg2 = registerValues[2];
	uint16_t reg3 = registerValues[3];

	if(getRegister(19, 1) & (1 << 5))
	{
		//writeLn("Radio ready for tuning...\r\n");

		//clear tune bit and chan bits
		reg2 &= ~(0x01FF | 0x0200);
		//set chan bits
		reg2 |= FTR(freq);
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

	getCurFreq();

}






void ar1010Volume(uint8_t volu)
{
	if(volu >= 21) volu = 21;
	if(volu <= 0) volu = 0;

	uint16_t reg3 = registerValues[3];
	uint16_t reg14 = registerValues[14];

	const uint8_t vols[22] =
	{
		0x0F,
		0xCF,
		0xDF,
		0xEF,
		0xFF,
		0xEE,
		0xFE,
		0xED,
		0xFD,
		0xFB,
		0xFA,
		0xF9,
		0xF7,
		0xE6,
		0xF6,
		0xE5,
		0xF5,
		0xE3,
		0xF3,
		0xF2,
		0xF1,
		0xF0
	};

	//clear this part of the register
	reg3 &= ~(0x0F << 7);
	//fill this part with the nessesary data
	reg3 |= (vols[volu] & 0x0F) << 7;


	//clear this part of the register
	reg14 &= ~(0xF000);
	//fill this part with the nessesary data "x << 8 = (x >> 4 ) << 12"
	reg14 |= (vols[volu] & 0xF0) << 8;

	//char outstr[20];
	//sprintf(outstr, "REG3: %0.2X\r\n", reg3);
	//writeLn(outstr);
	//sprintf(outstr, "REG14: %0.2X\r\n", reg14);
	//writeLn(outstr);

	setRegister(3, reg3);
	setRegister(14, reg14);

	//This is to ensure the volume stays the same after every seek
	//I hope
	registerValues[3] = reg3;
	registerValues[14] = reg14;
}
