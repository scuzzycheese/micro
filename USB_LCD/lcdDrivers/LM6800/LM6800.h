#include <avr/io.h>
#include <util/delay.h>

//this needs to be defined, as it's used to define things about the lcdClass object
#define BITDEPTH 1

#include "lcdClass.h"


#ifndef _LM6800_H
#define	_LM6800_H

#ifdef	__cplusplus
extern "C"
{
#endif


	enum LM6800_WRITE_MODE
	{
		LM6800_COMMAND,
		LM6800_RAM
	};

	struct LM6800PixelConfigData
	{
		uint8_t page;
		uint8_t chip;
		uint8_t column;
		uint8_t pixely;
	};

	#define LM6800_DATA_DELAY			__asm("nop;");\
												__asm("nop;");\
												__asm("nop;");\
												__asm("nop;");\
												__asm("nop;")

	#define LM6800_CONFIG_DELAY		__asm("nop;");\
												__asm("nop;");\
												__asm("nop;")

	void LM6800Init(void);
	void LM6800Write(uint8_t chip, uint8_t data, enum LM6800_WRITE_MODE writeMode);
	uint8_t LM6800Read(uint8_t chip);
	uint8_t LM6800ReadStatus(uint8_t chip);
	void LM6800SetPixel(uint8_t x, uint8_t y);
	void LM6800ClearPixel(uint8_t x, uint8_t y);
	void LM6800SelectChip(uint8_t chip) __attribute__((always_inline));
	void LM6800WriteBlock(uint8_t chip, uint8_t page, char *data);
	void LM6800Register(struct lcdDriver *driver);
	void LM6800GetPixel(uint8_t x, uint8_t y, union pixelColour *colour);
	struct lcdData LM6800GetLCDData(void);
	void LM6800Reset(void);

	#define LM6800_NUM_CONTROLLERS 4

	#define LM6800_NUM_PAGES_PER_CONROLLER 8
	#define LM6800_RES_PAGE_X 64
	#define LM6800_RES_PAGE_Y 64
	#define LM6800_COLUMNS_PER_PAGE 64

	#define LM6800_RES_X 256
	#define LM6800_RES_Y 64

	//This is configuration data for the LCD lines
	#define LM6800_DOUT PORTD
	#define LM6800_DIN PIND
	#define LM6800_DDR DDRD

	#define LM6800_CONTROL_PORT PORTB
	#define LM6800_CONTROL_DDR DDRB

	#define LM6800_RS PORTB0
	#define LM6800_RW PORTB1
	#define LM6800_CS PORTB2

	#define LM6800_CSA PORTB7
	#define LM6800_CSB PORTB4
	#define LM6800_CSC PORTB5

	#define LM6800_RESET PORTB6

#ifdef	__cplusplus
}
#endif

#endif	/* _LM6800_H */

