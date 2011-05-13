#include <stdio.h>
#include <stdint.h>

struct lcdData
{
	uint16_t width;
	uint16_t height;
	uint8_t bitDepth : 5;
	uint8_t colour : 1;
	uint8_t backlight : 1;
}__attribute__((packed));


//I want this to be sizeable by a #define or something, depending on the controller.

#define BITDEPTH 8
#ifdef COLOUR
#define COLOURBITDEPTH BITDEPTH
#else
#define COLOURBITDEPTH (BITDEPTH / 3)
#endif


union pixelColour
{
	struct
	{
		uint8_t R : COLOURBITDEPTH;
		uint8_t G : COLOURBITDEPTH;
		uint8_t B : COLOURBITDEPTH;
	};

	struct
	{
		uint8_t M : BITDEPTH;
	};
};


struct lcdDriver
{
	void (*init)();
	void (*reset)();
	void (*clearScreen)();
	//Still have to see if flush is the right way to go
	void (*flush)();
	/**
	 * setPixel needs to keep it's operations in a buffer, until flush is called
	 */
	void (*setPixel)(uint16_t x, uint16_t y);
	/**
	 * clearPixel needs to keep it's operations in a buffer, until flush is called
	 */
	void (*clearPixel)(uint16_t x, uint16_t y);

	uint8_t (*isPixelSet)(uint16_t x, uint16_t y);
	void (*getPixel)(union pixelColour *colour);

	void (*getLcdData)(struct lcdData *data);
};
