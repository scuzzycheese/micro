#include "ar1010.h"

#include "i2c.h"
#include <avr/io.h>
#include <util/delay.h>

//This is a global placeholder for the current curFreq
uint16_t curFreq = 860;

//Default register values for the ar1000
uint16_t registerValues[18] =
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


void ar1010Init()
{
	setAllRegs((uint16_t *)registerValues);
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
		//writeLn("Device Not Responding to READ operations\r\n");
	}

	_delay_ms(1);

	sbi(TWCR, TWIE);

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



void setAllRegs(uint16_t *regVals)
{
	uint8_t i;
	for(i = 1; i < 18; i ++)
	{
		uint8_t setBool = setRegister(i, regVals[i]);
		//if(!setBool) writeLn("Device Not Responding\r\n");
		_delay_ms(1);
	}
	uint8_t setBool = setRegister(0, regVals[0]);
	//if(!setBool) writeLn("Device Not Responding\r\n");
}


void getCurFreq()
{
	//Wait for STC, then set the global curFreq to the one the radio tuned to
	uint16_t reg19;
	while(!(getRegister(19, 1) & (1 << 5)));
	reg19 = getRegister(19, 1);

	//reg19 = (reg19 & 0xFF80) >> 7;
	//since we are shifting right, we don't need to mask out the rightmost bits like above
	reg19 = reg19 >> 7;

	curFreq = RTF(reg19);
}

//Nasty little blocking function, oh well.
void ar1010WaitForReady()
{
	//wait for radio to be ready after initialising
	while(!(getRegister(19, 1) & (1 << 5)))
	{
		_delay_ms(10);
	}
}

uint16_t ar1010getCurFreq()
{
	return curFreq;
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




void ar1010Seek()
{
	//set default values for register 2 and 3
	//These might have to be set from getRegister
	uint16_t reg2 = registerValues[2];
	uint16_t reg3 = registerValues[3];

	//Wait for STC bit (ready bit)
	//while(!(getRegister(19, 1) & (1 << 5)));

	//clear tune bit
	//set chan bits
	reg2 = 0xB480;
	reg2 &= ~(0x01FF | 0x0200);
	//use global curFreq as a base
	reg2 |= FTR(curFreq);

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

	getCurFreq();

	//char strout[20];
	//sprintf(strout, "Found FREQ: %d\r\n", curFreq);
	//writeLn(strout);
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