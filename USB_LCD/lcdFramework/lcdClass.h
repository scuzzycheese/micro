/* 
 * File:   lcdClass.h
 * Author: scuzzy
 *
 * Created on 29 June 2011, 9:33 PM
 */
#include <inttypes.h>

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
		void (*getPixel)(uint8_t x, uint8_t y, union pixelColour *colour);
		void (*setPixel)(uint8_t x, uint8_t y);
		void (*clearPixel)(uint8_t x, uint8_t y);

		void (*writeBlock)(uint8_t x, uint8_t y, char *data);

		struct lcdData (*getLcdData)(void);
		void (*init)(void);
		void (*reset)(void);
		void (*clearScreen)(void);
	};


	void registerDriver(struct lcdDriver *driver, void (*driverRegister)(struct lcdDriver *));

#ifdef	__cplusplus
}
#endif

#endif	/* _LCDCLASS_H */

