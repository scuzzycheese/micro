#include "LM6800.h"


void LM6800Init(void)
{
	LM6800_CONTROL_DDR |=
		(1 << LM6800_CS) |
		(1 << LM6800_CSA) |
		(1 << LM6800_CSB) |
		(1 << LM6800_CSC) |
		(1 << LM6800_RESET) |
		(1 << LM6800_RS) |
		(1 << LM6800_RW);

	LM6800_CONTROL_DDR = 0xFF;

	//set the default state of the ports
	LM6800_CONTROL_PORT = 0x00;
	LM6800_DOUT = 0x00;

	//Apparently setting CSC high disables access to the LCD
	LM6800_CONTROL_PORT |= (1 << LM6800_CSC);

	//reset LCD
	LM6800_CONTROL_PORT |= (1 << LM6800_RESET);
	_delay_ms(1);
	LM6800_CONTROL_PORT &= ~(1 << LM6800_RESET);
	_delay_ms(1);
	LM6800_CONTROL_PORT |= (1 << LM6800_RESET);
	_delay_ms(1);

	//Turn on the display for all chips
	LM6800WriteCommand(1,0x3f);
	LM6800WriteCommand(2,0x3f);
	LM6800WriteCommand(3,0x3f);
	LM6800WriteCommand(4,0x3f);

	//set start line = 0 for all chips
	LM6800WriteCommand(1,0xc0);
	LM6800WriteCommand(2,0xc0);
	LM6800WriteCommand(3,0xc0);
	LM6800WriteCommand(4,0xc0);

}


//Can probably be consolodated with LM6800WriteRAM as well
void LM6800WriteCommand(uint8_t chip, uint8_t data)
{
	//set the data on the port
	LM6800_DOUT = data;

	//select display ram
	LM6800_CONTROL_PORT |= (1 << LM6800_RS);

	//select write mode
	LM6800_CONTROL_PORT &= ~(1 << LM6800_RW);

	switch(chip)
	{
		case 1:
			LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB) | (1 << LM6800_CSC));
			//CSC=0; CSB=0; CSA=0;
			break;
		case 2:
			LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB) | (1 << LM6800_CSC));
			LM6800_CONTROL_PORT |= (1 << LM6800_CSA);
			//CSC=0; CSB=0; CSA=1;
			break;
		case 3:
			LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB) | (1 << LM6800_CSC));
			LM6800_CONTROL_PORT |= (1 << LM6800_CSB);
			//CSC=0; CSB=1; CSA=0;
			break;
		case 4:
			LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB) | (1 << LM6800_CSC));
			LM6800_CONTROL_PORT |= ((1 << LM6800_CSA) | (1 << LM6800_CSB));
			//CSC=0; CSB=1; CSA=1;
			break;
	}

	//Raise the control select pin (sometimes called E)
	LM6800_CONTROL_PORT |= (1 << LM6800_CS);
	_delay_us(1);
	LM6800_CONTROL_PORT &= ~(1 << LM6800_CS);

	//disable access to LCD
	LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB));
	LM6800_CONTROL_PORT |= (1 << LM6800_CSC);

}

void LM6800WriteRAM(uint8_t chip, uint8_t data)
{
	//set the data on the port
	LM6800_DOUT = data;

	//select display ram
	LM6800_CONTROL_PORT &= ~(1 << LM6800_RS);

	//select write mode
	LM6800_CONTROL_PORT &= ~(1 << LM6800_RW);

	switch(chip)
	{
		case 1:
			LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB) | (1 << LM6800_CSC));
			//CSC=0; CSB=0; CSA=0;
			break;
		case 2:
			LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB) | (1 << LM6800_CSC));
			LM6800_CONTROL_PORT |= (1 << LM6800_CSA);
			//CSC=0; CSB=0; CSA=1;
			break;
		case 3:
			LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB) | (1 << LM6800_CSC));
			LM6800_CONTROL_PORT |= (1 << LM6800_CSB);
			//CSC=0; CSB=1; CSA=0;
			break;
		case 4:
			LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB) | (1 << LM6800_CSC));
			LM6800_CONTROL_PORT |= ((1 << LM6800_CSA) | (1 << LM6800_CSB));
			//CSC=0; CSB=1; CSA=1;
			break;
	}

	//Raise the control select pin (sometimes called E)
	LM6800_CONTROL_PORT |= (1 << LM6800_CS);
	_delay_us(1);
	LM6800_CONTROL_PORT &= ~(1 << LM6800_CS);

	//disable access to LCD
	LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB));
	LM6800_CONTROL_PORT |= (1 << LM6800_CSC);

}



void LM6800DrawTest()
{
    	LM6800WriteCommand(1, 0xb8);	// select page no to all driver
    	LM6800WriteCommand(2, 0xb8);
    	LM6800WriteCommand(3, 0xb8);
    	LM6800WriteCommand(4, 0xb8);

    	LM6800WriteCommand(1, 0x40);	    // set column 00h to all driver
    	LM6800WriteCommand(2, 0x40);
    	LM6800WriteCommand(3, 0x40);
    	LM6800WriteCommand(4, 0x40);

		LM6800WriteRAM(1, 0xFF);
		LM6800WriteRAM(2, 0xFF);
		LM6800WriteRAM(3, 0xFF);
		LM6800WriteRAM(4, 0xFF);



}