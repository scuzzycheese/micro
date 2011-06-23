#include <avr/io.h>
#include <util/delay.h>


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

	void LM6800Init(void);
	void LM6800Write(uint8_t chip, uint8_t data, enum LM6800_WRITE_MODE writeMode);
	uint8_t LM6800Read(uint8_t chip);
	uint8_t LM6800ReadStatus(uint8_t chip);
	void LM6800SelectChip(uint8_t chip) __attribute__((always_inline));
	void LM6800DrawTest();


	#define LM6800_DOUT PORTD
	#define LM6800_DIN PIND
	#define LM6800_DDR DDRD

	#define LM6800_CONTROL_PORT PORTB
	#define LM6800_CONTROL_DDR DDRB

	#define LM6800_RS PORTB0
	#define LM6800_RW PORTB1
	#define LM6800_CS PORTB2

	#define LM6800_CSA PORTB3
	#define LM6800_CSB PORTB4
	#define LM6800_CSC PORTB5

	#define LM6800_RESET PORTB6


#ifdef	__cplusplus
}
#endif

#endif	/* _LM6800_H */

