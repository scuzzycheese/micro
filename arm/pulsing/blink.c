#include <inttypes.h>
#include "AT91SAM7S256.h" // Definitions of the ARM chip and on-chip peripherals.
#include "SAM7-P256.h"    // Definitions of peripherals on the Olimex dev board.

void delay()
{
	int i;

	for (i = 0; i < 0x10; i++)
		__asm("nop");
}


uint8_t sinArray[256] = 
{
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   2,   2,   3,   4,   4,   5,   6,   7,   9,
  10,  11,  12,  14,  15,  17,  18,  20,  22,  24,  25,  27,  29,  31,  34,  36,  38,  40,  43,  45,  47,
  50,  52,  55,  57,  60,  63,  66,  68,  71,  74,  77,  80,  83,  86,  89,  92,  95,  98, 101, 104, 107,
 110, 113, 116, 119, 123, 126, 129, 132, 135, 138, 141, 144, 148, 151, 154, 157, 160, 163, 166, 169, 172,
 175, 178, 181, 183, 186, 189, 192, 194, 197, 200, 202, 205, 207, 210, 212, 214, 217, 219, 221, 223, 225,
 227, 229, 231, 233, 235, 236, 238, 240, 241, 242, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 253,
 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 254, 254, 253, 253, 252, 251, 251, 250, 249,
 248, 246, 245, 244, 243, 241, 240, 238, 237, 235, 233, 231, 230, 228, 226, 224, 221, 219, 217, 215, 212,
 210, 208, 205, 203, 200, 198, 195, 192, 189, 187, 184, 181, 178, 175, 172, 169, 166, 163, 160, 157, 154,
 151, 148, 145, 142, 139, 136, 132, 129, 126, 123, 120, 117, 114, 111, 107, 104, 101,  98,  95,  92,  89,
  86,  83,  80,  77,  74,  72,  69,  66,  63,  61,  58,  55,  53,  50,  48,  45,  43,  41,  38,  36,  34,
  32,  30,  28,  26,  24,  22,  20,  19,  17,  15,  14,  13,  11,  10,   9,   8,   7,   6,   5,   4,   3,
   2,   2,   1,   1
};

int main()
{
// Get a pointer to the PIO data structure. The PIO is the "Peripheral input/output
// controller" and is the part of the ARM chip which can access input/output (GPIO) pins.
	volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA;
	
// Enable PIO to control the LEDs.
	pPIO->PIO_PER = LED_MASK;
	
// Set LED pins to outputs.
	pPIO->PIO_OER = LED_MASK;

	int dutyCycle[3] = {0, 66, 200};
	int dutyInc[3] = {1, 2, 3};
	int dutyNumber = 3;
	int8_t slowDown = 3;
	int8_t slowDownCounter = 0;
	while(1)
	{
		slowDownCounter ++;
		if(slowDownCounter >= slowDown)
		{
			for(int8_t i = 0; i < dutyNumber; i ++)
			{
				dutyCycle[i] += dutyInc[i];
			}
			slowDownCounter = 0;
		}
		for(int i = 0; i < 256; i ++)
		{
			delay();
			//if(i < sinArray[dutyCycle[0]]) PORTD |= (1 << 5);
			//else PORTD &= ~(1 << 5);


			if(i < sinArray[dutyCycle[1]]) pPIO->PIO_SODR |= LED1;
			else pPIO->PIO_CODR |= LED1;

			if(i < sinArray[dutyCycle[2]]) pPIO->PIO_SODR |= LED2;
			else pPIO->PIO_CODR |= LED2;
		}
		for(int8_t i = 0; i < dutyNumber; i ++)
		{
			if(dutyCycle[i] >= 255) dutyCycle[i] = 0;
		}
	}

	return 0;

}
