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
	LM6800Write(1,0x3f, LM6800_COMMAND);
	LM6800Write(2,0x3f, LM6800_COMMAND);
	LM6800Write(3,0x3f, LM6800_COMMAND);
	LM6800Write(4,0x3f, LM6800_COMMAND);
	

	//set start line = 0 for all chips
	LM6800Write(1,0xc0, LM6800_COMMAND);
	LM6800Write(2,0xc0, LM6800_COMMAND);
	LM6800Write(3,0xc0, LM6800_COMMAND);
	LM6800Write(4,0xc0, LM6800_COMMAND);

}



uint8_t LM6800Read(uint8_t chip)
{
	uint8_t data;

	while(LM6800ReadStatus(chip) && 0x80);

	//set the data port to input
	LM6800_DDR = 0x00;
	//set the port to 0
	LM6800_DOUT = 0x00;

	LM6800_CONTROL_PORT |= (1 << LM6800_RS) | (1 << LM6800_RW);

	LM6800SelectChip(chip);

	//NOTE: not sure if I need this or not
	//Raise the control select pin (sometimes called E)
	//apparently first access is to copy display data to display output register
	//LM6800_CONTROL_PORT |= (1 << LM6800_CS);
	//LM6800_CONTROL_PORT &= ~(1 << LM6800_CS);

	LM6800_CONTROL_PORT |= (1 << LM6800_CS);
	__asm("nop;");
	data = LM6800_DIN;
	LM6800_CONTROL_PORT &= ~(1 << LM6800_CS);

	//disable access to LCD
	LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB));
	LM6800_CONTROL_PORT |= (1 << LM6800_CSC);

	return data;
}

uint8_t LM6800ReadStatus(uint8_t chip)
{
	uint8_t data;

	//set the data port to input
	LM6800_DDR = 0x00;
	//set the port to 0
	LM6800_DOUT = 0x00;

	LM6800_CONTROL_PORT |= (1 << LM6800_RW);
	LM6800_CONTROL_PORT &= ~(1 << LM6800_RS);

	LM6800SelectChip(chip);

	LM6800_CONTROL_PORT |= (1 << LM6800_CS);
	__asm("nop;");
	data = LM6800_DIN;
	LM6800_CONTROL_PORT &= ~(1 << LM6800_CS);

	//disable access to LCD
	LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB));
	LM6800_CONTROL_PORT |= (1 << LM6800_CSC);

	return data;
}


void LM6800Write(uint8_t chip, uint8_t data, enum LM6800_WRITE_MODE writeMode)
{
	//Wait for the status
	while(LM6800ReadStatus(chip) & 0x80);

	//set the data on the port
	LM6800_DOUT = data;

	//set data port to output
	LM6800_DDR = 0xFF;

	if(writeMode == LM6800_RAM)
	{
		//select display ram
		LM6800_CONTROL_PORT |= (1 << LM6800_RS);
	}
	else if(writeMode == LM6800_COMMAND)
	{
		//select display command
		LM6800_CONTROL_PORT &= ~(1 << LM6800_RS);
	}

	//select write mode
	LM6800_CONTROL_PORT &= ~(1 << LM6800_RW);

	LM6800SelectChip(chip);

	//Raise the control select pin (sometimes called E)
	LM6800_CONTROL_PORT |= (1 << LM6800_CS);
	__asm("nop;");
	LM6800_CONTROL_PORT &= ~(1 << LM6800_CS);

	//disable access to LCD
	LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB));
	LM6800_CONTROL_PORT |= (1 << LM6800_CSC);
}


void LM6800DrawTest()
{
    	LM6800Write(1, 0xb8, LM6800_COMMAND);	// select page no to all driver
    	LM6800Write(2, 0xb8, LM6800_COMMAND);
    	LM6800Write(3, 0xb8, LM6800_COMMAND);
    	LM6800Write(4, 0xb8, LM6800_COMMAND);

    	LM6800Write(1, 0x40, LM6800_COMMAND);	    // set column 00h to all driver
    	LM6800Write(2, 0x40, LM6800_COMMAND);
    	LM6800Write(3, 0x40, LM6800_COMMAND);
    	LM6800Write(4, 0x40, LM6800_COMMAND);

		LM6800Write(1, 0xDE, LM6800_RAM);
		LM6800Write(2, 0xAD, LM6800_RAM);
		LM6800Write(3, 0xBE, LM6800_RAM);
		LM6800Write(4, 0xEF, LM6800_RAM);


}

void LM6800SelectChip(uint8_t chip)
{
	switch(chip)
	{
		case 1:
			LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB) | (1 << LM6800_CSC));
			break;
		case 2:
			LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB) | (1 << LM6800_CSC));
			LM6800_CONTROL_PORT |= (1 << LM6800_CSA);
			break;
		case 3:
			LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB) | (1 << LM6800_CSC));
			LM6800_CONTROL_PORT |= (1 << LM6800_CSB);
			break;
		case 4:
			LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB) | (1 << LM6800_CSC));
			LM6800_CONTROL_PORT |= ((1 << LM6800_CSA) | (1 << LM6800_CSB));
			break;
	}
}