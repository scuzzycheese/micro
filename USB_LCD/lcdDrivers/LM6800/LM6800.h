#include <avr/io.h>
#include <util/delay.h>

//this needs to be defined, as it's used to define things about the lcdClass object
#define BITDEPTH 1

#include "lcdClass.h"
#include "LM6800Externals.h"

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

	uint8_t currentContrast;

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
	void LM6800SetBacklight(uint8_t state);

	#define LM6800_NUM_CONTROLLERS 4

	#define LM6800_NUM_PAGES_PER_CONROLLER 8
	#define LM6800_RES_PAGE_X 64
	#define LM6800_RES_PAGE_Y 8
	#define LM6800_COLUMNS_PER_PAGE 64

	#define LM6800_RES_X 256
	#define LM6800_RES_Y 64

	//This is configuration data for the LCD lines
	#define LM6800_DOUT PORTD
	#define LM6800_DIN PIND
	#define LM6800_DDR DDRD

	#define LM6800_CONTROL_PORT PORTF
	#define LM6800_CONTROL_DDR DDRF
	#define LM6800_RS PORTF0
	#define LM6800_RW PORTF1
	#define LM6800_CS PORTF4
	#define LM6800_CSA PORTF5
	#define LM6800_CSB PORTF6
	#define LM6800_CSC PORTF7

	#define LM6800_RESET_PORT PORTE
	#define LM6800_RESET_DDR DDRE
	#define LM6800_RESET PORTE6

	#define LM6800_CONT_PORT PORTB
	#define LM6800_CONT_DDR DDRB
	#define LM6800_CONT_UD PORTB7




#ifdef	__cplusplus
}
#endif

#endif	/* _LM6800_H */

