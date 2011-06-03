#include "D22_5003.h"


void D22Init()
{
	D22_CONTROL_DDR |= (1 << D22_READ_PIN | 1 << D22_WRITE_PIN | 1 << D22_REGISTER_SELECT_PIN);
}

void D22WriteByte(uint8_t byte)
{
	//enable output on the data port
	D22_DB_DDR = 0xFF;

	D22_SET_WRITE;
	D22_DBOUT = byte;
	//NOTE: this delay will probably slow things down, maybe a few nops instead
	_delay_ms(1);
	D22_CLEAR_WRITE;
}