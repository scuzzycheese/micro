#include "D22_5003.h"


void D22Init()
{
	D22_CONTROL_DDR = (1 << D22_READ_PIN | 1 << D22_WRITE_PIN | 1 << D22_REGISTER_SELECT_PIN | 1 << D22_CS_PIN);
	D22_CONTROL_PORT |= (1 << D22_CS_PIN);


	//DDRD = 0xFF;
	//PORTD = 0x00;
}

uint8_t D22WriteByte(uint8_t byte)
{
	D22_DB_DDR = 0xFF;

	D22_CONTROL_PORT &= ~(1 << D22_REGISTER_SELECT_PIN);

	D22_CONTROL_PORT &= ~(1 << D22_CS_PIN);

	//D22_SET_WRITE;
	PORTB &= ~(1 << PORTB0);
	//This line below, causes all sorts of nasties
	PORTB |= (1 << PORTB1);

	D22_DBOUT = 0xAF;
	_delay_ms(1);

	//D22_CLEAR_WRITE;
	PORTB &= ~(1 << PORTB1);

	D22_CONTROL_PORT |= (1 << D22_CS_PIN);

	D22_DBOUT = 0x00;

	return PORTD;
	/*
	uint8_t ctrlPortVal = 0;
	//enable output on the data port
	D22_DB_DDR = 0xFF;

	//pull RS down (Control Date)
	D22_CONTROL_PORT &= ~(1 << D22_REGISTER_SELECT_PIN);

	//pull CS down
	D22_CONTROL_PORT &= ~(1 << D22_CS_PIN);

	D22_SET_WRITE;
	ctrlPortVal = D22_CONTROL_PORT;
	D22_DBOUT = byte;
	ctrlPortVal = D22_DBOUT;
	//NOTE: this delay will probably slow things down, maybe a few nops instead
	_delay_ms(1);
	D22_CLEAR_WRITE;

	D22_CONTROL_PORT |= (1 << D22_CS_PIN);

	//D22_DBOUT = 0x00;
	return ctrlPortVal;
	 */
}