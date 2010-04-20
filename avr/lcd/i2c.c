/**
 *  Copyright (c) 2010 Daine Mamacos <daine.mamacos@reverseorder.net>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

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
