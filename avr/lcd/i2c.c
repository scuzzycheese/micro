#include "global.h"
#include <inttypes.h>
#include <compat/twi.h>

#include "i2c.h"

void i2c_setBitRate(uint16_t bitrateKHz)
{
	uint8_t bitrate_div;
	// set i2c bitrate
	// SCL freq = F_CPU/(16+2*TWBR))
	// calculate bitrate division
	bitrate_div = ((F_CPU/1000l)/bitrateKHz);
	if(bitrate_div >= 16) bitrate_div = (bitrate_div - 16) / 2;
	TWBR = bitrate_div;
}

void i2c_init(void)
{
	i2c_setBitRate(100);

	TWCR = (1 << TWEA);
}


void i2c_start()
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	i2c_waitForComplete();
}

void i2c_waitForComplete()
{
	while(!(TWCR & (1<<TWINT)));
}

void i2c_stop()
{
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	
	// wait until stop condition is executed and bus released
	while(TWCR & (1 << TWSTO));
}

unsigned char i2c_write( unsigned char data )
{	
	// send data to the previously addressed device
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);

	// wait until transmission completed
	while(!(TWCR & (1<<TWINT)));


	if((TW_STATUS & 0xF8) == TW_MT_DATA_ACK) return 1;
	else return 0;
}


unsigned char i2c_read(void)
{
	TWCR = (1 << TWINT) | (1 << TWEN);

	// wait until transmission completed
	while(!(TWCR & (1<<TWINT)));    

	return TWDR;
}
