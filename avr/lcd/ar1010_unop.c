#include "ar1010.h"

#include <avr/interrupt.h>

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

//This is a global placeholder for the current curFreq
uint16_t curFreq = 860;

void getCurFreq()
{
	//I'm using delays, as opposed to checking the STC bit,
	//because it seems somewhat unreliable
	//_delay_ms(5);
	ar1010WaitForReady();
	curFreq = RTF(getRegister(19, 1) >> 7);
}

uint16_t ar1010getCurFreq()
{
	return curFreq;
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
}