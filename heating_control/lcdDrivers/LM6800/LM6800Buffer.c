#include "LM6800.h"
#include <stdio.h>
#include "../fonts/glcdfont.h"
#include <string.h>

static void LM6800ComputePixelConfigData(uint8_t x, uint8_t y, struct LM6800PixelConfigData *data) __attribute__((always_inline));
void LM6800ClearVideoMemory(void);

static char videoMemory[64];
static uint8_t lastChipWritten = 0;
static uint8_t lastPageWritten = 0;

//If this is useful I'll back port it to the original LM6800 driver
void LM6800ReadBlock(uint8_t chip, uint8_t page, char *data);

void LM6800Init(void)
{
	currentContrast = 0;

	LM6800_CONTROL_DDR |=
		(1 << LM6800_CS) |
		(1 << LM6800_CSA) |
		(1 << LM6800_CSB) |
		(1 << LM6800_CSC) |
		(1 << LM6800_RS) |
		(1 << LM6800_RW);

	LM6800_RESET_DDR |= (1 << LM6800_RESET);

	//set the default state of the ports
	LM6800_CONTROL_PORT = 0x00;
	LM6800_DOUT = 0x00;

	//Apparently setting CSC high disables access to the LCD
	LM6800_CONTROL_PORT |= (1 << LM6800_CSC);

	//set up the port that controls contrast
	LM6800_CONT_DDR |= (1 << LM6800_CONT_UD);

	//set contrast
	LM6800SetBacklight(1);

	//reset LCD
	LM6800Reset();

	//Turn on the display for all chips
	LM6800Write(0,0x3f, LM6800_COMMAND);
	LM6800Write(1,0x3f, LM6800_COMMAND);
	LM6800Write(2,0x3f, LM6800_COMMAND);
	LM6800Write(3,0x3f, LM6800_COMMAND);
	

	//set start line = 0 for all chips
	LM6800Write(0,0xc0, LM6800_COMMAND);
	LM6800Write(1,0xc0, LM6800_COMMAND);
	LM6800Write(2,0xc0, LM6800_COMMAND);
	LM6800Write(3,0xc0, LM6800_COMMAND);

}

void LM6800ClearVideoMemory(void) 
{
   for(uint8_t i = 0; i <= 64; i ++)
   {
      videoMemory[i] = 0x00;
   }
}

void LM6800Reset(void)
{
	//reset LCD
	LM6800_RESET_PORT |= (1 << LM6800_RESET);
	_delay_ms(1);
	LM6800_RESET_PORT &= ~(1 << LM6800_RESET);
	_delay_ms(1);
	LM6800_RESET_PORT |= (1 << LM6800_RESET);
	_delay_ms(1);
}


struct lcdData LM6800GetLCDData(void)
{
	struct lcdData lcdStats;
	lcdStats.backlight = 1;
	lcdStats.bitDepth = 1;
	lcdStats.colour = 0;
	lcdStats.height = 64;
	lcdStats.width = 256;

	return lcdStats;
}

static void LM6800ComputePixelConfigData(uint8_t x, uint8_t y, struct LM6800PixelConfigData *data)
{
   //figure out which page and chip we want
   data->page = (y >> 3) & 7;
   data->chip = (x >> 6) & 3;

   //figure out the pixel on each page/chip
   data->column = (x & 63);
   data->pixely = (y & 7);
}


void LM6800ClearPixel(uint8_t x, uint8_t y)
{

	struct LM6800PixelConfigData piConData;
	LM6800ComputePixelConfigData(x, y, &piConData);

   //Sort of like an auto flush thing
   if(piConData.chip != lastChipWritten || piConData.page != lastPageWritten) 
   {
      LM6800FlushVM();

      //Fetch the block and populate the video memory with it
      //so that the drawing can happen on the new block
      LM6800ReadBlock(piConData.chip, piConData.page, videoMemory);


      lastChipWritten = piConData.chip;
      lastPageWritten = piConData.page;
   }

   char *columnVal = &(videoMemory[piConData.column]);

	//clear the pixel on the column
	*columnVal &= ~(1 << piConData.pixely);
}

void LM6800SetPixel(uint8_t x, uint8_t y)
{
	struct LM6800PixelConfigData piConData;
	LM6800ComputePixelConfigData(x, y, &piConData);

   //Sort of like an auto flush thing
   if(piConData.chip != lastChipWritten || piConData.page != lastPageWritten) 
   {
      LM6800FlushVM();

      //Fetch the block and populate the video memory with it
      //so that the drawing can happen on the new block
      LM6800ReadBlock(piConData.chip, piConData.page, videoMemory);


      lastChipWritten = piConData.chip;
      lastPageWritten = piConData.page;
   }

   char *columnVal = &(videoMemory[piConData.column]);

	//set the pixel on the column
	*columnVal |= (1 << piConData.pixely);
}


void LM6800PrintChar(uint8_t x, uint8_t y, unsigned char c)
{

   for(uint8_t i = 0; i < 5; i ++)
   {
      const char char_item = pgm_read_byte(&font[(c * 5) + i]);

      for(uint8_t j = 0; j < 8; j ++) 
      {
         uint8_t pixel_set = char_item & (1 << j);
         if(pixel_set)
         {
            LM6800SetPixel(i + x, j + y);
         }
      }

   }
}


void LM6800VSPrintf(uint8_t x, uint8_t y, const char *fmt, va_list ap) 
{

   char testString[strlen(fmt) + 50];
   vsprintf(testString, fmt, ap);

   char *progressionPointer = testString;
   uint8_t x_val = x;
   while(*progressionPointer != '\0') 
   {
      LM6800PrintChar(x_val, y, *progressionPointer);
      x_val += 6;
      progressionPointer += sizeof(char);
   }

}

void LM6800Printf(uint8_t x, uint8_t y, const char *fmt, ...) 
{
   va_list argp;
   va_start(argp, fmt);
   LM6800VSPrintf(x, y, fmt, argp);
   va_end(argp);

}


void LM6800FlushVM() 
{
   LM6800WriteBlock(lastChipWritten, lastPageWritten, videoMemory);
}


uint8_t LM6800GetColumn(uint8_t x, uint8_t y)
{
	struct LM6800PixelConfigData piConData;
	LM6800ComputePixelConfigData(x, y, &piConData);

	//Set the colum of the chip we want
	LM6800Write(piConData.chip, (1 << 6) | piConData.column, LM6800_COMMAND);
	//set the page we want for that chip
	LM6800Write(piConData.chip, (23 << 3) | piConData.page, LM6800_COMMAND);

	LM6800Read(piConData.chip);
	uint8_t columnVal = LM6800Read(piConData.chip);
	return columnVal;
}

/**
 * NOTE: This function has not been tested yet
 */
void LM6800GetPixel(uint8_t x, uint8_t y, union pixelColour *colour)
{
	struct LM6800PixelConfigData piConData;
	LM6800ComputePixelConfigData(x, y, &piConData);

	//Set the colum of the chip we want
	LM6800Write(piConData.chip, (1 << 6) | piConData.column, LM6800_COMMAND);
	//set the page we want for that chip
	LM6800Write(piConData.chip, (23 << 3) | piConData.page, LM6800_COMMAND);

	LM6800Read(piConData.chip);
	uint8_t columnVal = LM6800Read(piConData.chip);
	colour->MONO.M = (columnVal & (1 << piConData.pixely)) >> piConData.pixely;
}



uint8_t LM6800Read(uint8_t chip)
{
	uint8_t data;
	LM6800SelectChip(chip);

	while(LM6800ReadStatus(chip) && 0x80);

	//set the data port to input
	LM6800_DDR = 0x00;
	//set the port to 0
	LM6800_DOUT = 0x00;

	//set read mode
	LM6800_CONTROL_PORT |= (1 << LM6800_RS) | (1 << LM6800_RW);

	LM6800_CONFIG_DELAY;

	LM6800_CONTROL_PORT |= (1 << LM6800_CS);
	LM6800_DATA_DELAY;
	data = LM6800_DIN;
	LM6800_CONTROL_PORT &= ~(1 << LM6800_CS);

	return data;
}

uint8_t LM6800ReadStatus(uint8_t chip)
{
	uint8_t data;
	LM6800SelectChip(chip);

	//set the data port to input
	LM6800_DDR = 0x00;
	//set the port to 0
	LM6800_DOUT = 0x00;

	//enter mode to read status
	LM6800_CONTROL_PORT |= (1 << LM6800_RW);
	LM6800_CONTROL_PORT &= ~(1 << LM6800_RS);

	LM6800_CONFIG_DELAY;

	LM6800_CONTROL_PORT |= (1 << LM6800_CS);
	LM6800_DATA_DELAY;
	//we may need another nop here
	data = LM6800_DIN;
	LM6800_CONTROL_PORT &= ~(1 << LM6800_CS);

	return data;
}


void LM6800Write(uint8_t chip, uint8_t data, enum LM6800_WRITE_MODE writeMode)
{
	LM6800SelectChip(chip);

	//Wait for the status
	while(LM6800ReadStatus(chip) & 0x80);

	//set data port to output
	LM6800_DDR = 0xFF;
	//set the data on the port
	LM6800_DOUT = data;

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

	LM6800_CONFIG_DELAY;

	//Raise the control select pin (sometimes called E)
	LM6800_CONTROL_PORT |= (1 << LM6800_CS);
	LM6800_DATA_DELAY;
	LM6800_CONTROL_PORT &= ~(1 << LM6800_CS);
}


void LM6800WriteBlock(uint8_t chip, uint8_t page, char *data)
{
	//Set our column to the beginning
	LM6800Write(chip, (1 << 6), LM6800_COMMAND);
	//set the page we want for that chip
	LM6800Write(chip, (23 << 3) | page, LM6800_COMMAND);

	//Dump a block of data to the page
	for(uint8_t col = 0; col < LM6800_COLUMNS_PER_PAGE; col ++)
	{
		LM6800Write(chip, data[col], LM6800_RAM);
	}
}

void LM6800ReadBlock(uint8_t chip, uint8_t page, char *data)
{
	//Set our column to the beginning
	LM6800Write(chip, (1 << 6), LM6800_COMMAND);
	//set the page we want for that chip
	LM6800Write(chip, (23 << 3) | page, LM6800_COMMAND);

   //dummy read
   LM6800Read(chip);

	//Dump a block of data to the page
	for(uint8_t col = 0; col < LM6800_COLUMNS_PER_PAGE; col ++)
	{
      *(data + col) = LM6800Read(chip);
	}
}

void LM6800ClearScreen(void)
{
	for(uint8_t chip = 0; chip < LM6800_NUM_CONTROLLERS; chip ++)
	{
		for(uint8_t page = 0; page < LM6800_NUM_PAGES_PER_CONROLLER; page ++)
		{
         LM6800ClearBlock(chip, page);
		}
	}
   //We also have to clear anything left in the video memory
   LM6800ClearVideoMemory();
}

void LM6800ClearController(uint8_t chip) 
{
	for(uint8_t page = 0; page < LM6800_NUM_PAGES_PER_CONROLLER; page ++)
   {
      LM6800ClearBlock(chip, page);
   }
}

void LM6800ClearBlock(uint8_t chip, uint8_t page) 
{
	//Set our column to the beginning
	LM6800Write(chip, (1 << 6), LM6800_COMMAND);
	//set the page we want for that chip
	LM6800Write(chip, (23 << 3) | page, LM6800_COMMAND);

	//Dump a block of data to the page
	for(uint8_t col = 0; col < LM6800_COLUMNS_PER_PAGE; col ++)
	{
		LM6800Write(chip, 0x00, LM6800_RAM);
	}

   if(chip == lastChipWritten && page == lastPageWritten) 
   {
      //We also have to clear anything left in the video memory
      //if it's in the right place
      LM6800ClearVideoMemory();
   }
}

void LM6800Register(struct lcdDriver *driver)
{
	driver->clearPixel = LM6800ClearPixel;
	driver->clearScreen = LM6800ClearScreen;
	driver->getLcdData = LM6800GetLCDData;
	driver->getPixel = LM6800GetPixel;
	driver->init = LM6800Init;
	driver->reset = LM6800Reset;
	driver->setPixel = LM6800SetPixel;
	driver->writeBlock = LM6800WriteBlock;
   driver->printChar = LM6800PrintChar;
   driver->printf = LM6800Printf;
   driver->flushVM = LM6800FlushVM;
   driver->readBlock = LM6800ReadBlock;
   driver->clearController = LM6800ClearController;
   driver->clearBlock = LM6800ClearBlock;
}

void LM6800SelectChip(uint8_t chip)
{
	switch(chip)
	{
		case 0:
			LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB) | (1 << LM6800_CSC));
			break;
		case 1:
			LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB) | (1 << LM6800_CSC));
			LM6800_CONTROL_PORT |= (1 << LM6800_CSA);
			break;
		case 2:
			LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB) | (1 << LM6800_CSC));
			LM6800_CONTROL_PORT |= (1 << LM6800_CSB);
			break;
		case 3:
			LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB) | (1 << LM6800_CSC));
			LM6800_CONTROL_PORT |= ((1 << LM6800_CSA) | (1 << LM6800_CSB));
			break;
		default:
			LM6800_CONTROL_PORT &= ~((1 << LM6800_CSA) | (1 << LM6800_CSB) | (1 << LM6800_CSC));
			break;
	}
}

void LM6800SetBacklight(uint8_t state)
{
	if(state) LM6800_CONT_PORT &= ~(1 << LM6800_CONT_UD);
	else LM6800_CONT_PORT |= (1 << LM6800_CONT_UD);
}
