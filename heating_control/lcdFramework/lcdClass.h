#include <inttypes.h>
#include "LM6800/LM6800Externals.h"
#include <stdarg.h>

#ifndef _LCDCLASS_H
#define	_LCDCLASS_H

#ifdef	__cplusplus
extern "C"
{
#endif

	struct lcdData
	{
		uint16_t width;
		uint16_t height;
		uint8_t bitDepth : 5;
		uint8_t colour : 1;
		uint8_t backlight : 1;
	} __attribute__((packed));

	#ifndef BITDEPTH
	#define BITDEPTH 8
	#endif

	/**
	 * Still not 100% sure what to do here, the struct
	 * could go over size if it's monochrome, but 8 bit
	 * say... Hmmmmm
	 */
	union pixelColour
	{
		struct
		{
			uint8_t R : BITDEPTH;
			uint8_t G : BITDEPTH;
			uint8_t B : BITDEPTH;
		} RGB;

		struct
		{
			uint8_t M : BITDEPTH;
		} MONO;
	};

	struct lcdDriver
	{
		void (*getPixel)(lcdXYType x, lcdXYType y, union pixelColour *colour);
		void (*setPixel)(lcdXYType x, lcdXYType y);
		void (*clearPixel)(lcdXYType x, lcdXYType y);

		void (*writeBlock)(lcdXYType x, lcdXYType y, char *data);
		void (*readBlock)(lcdXYType x, lcdXYType y, char *data);

		struct lcdData (*getLcdData)(void);
		void (*init)(void);
		void (*reset)(void);
		void (*clearScreen)(void);
      void (*printChar)(uint8_t x, uint8_t y, unsigned char c);
      void (*printf)(uint8_t x, uint8_t y, const char *fmt, ...);
      void (*flushVM)(void);
      void (*clearController)(uint8_t chip); 
      void (*clearBlock)(uint8_t chip, uint8_t page); 
      void (*setBacklight)(uint8_t state);
	};


	void registerDriver(struct lcdDriver *driver, void (*driverRegister)(struct lcdDriver *));

#ifdef	__cplusplus
}
#endif

#endif	/* _LCDCLASS_H */

