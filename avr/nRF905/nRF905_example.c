/**
 *    Copyright 2010 Daine Mamacos
 *
 *    This file is part of the nRF905 driver for AVR micro controllers.
 *
 *    The nRF905 driver is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License.
 *
 *    The nRF905 driver is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <avr/io.h>
#include <inttypes.h>
#define F_CPU 16000000UL  // 16 MHz
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "SPIDefs.h"
#include "nRF905_conf.h"
#include "nrf905.h"

int main(void)
{
	SPI_MasterInit();

	char blah[] = {0xDE, 0xAD, 0xBE, 0xEF};

	//this has to be high from the start
	SPI_MasterEnd();

	while(1)
	{


#ifdef SEND
		_delay_ms(5000);

		nRF905Init();

		nRF905SetFreq(4331, 0, 0);

		nRF905SetTxRxAddWidth(4, 4);

		nRF905SetRxAddress(192, 168, 0, 1);

		nRF905SetRxPayloadWidth(4);
		nRF905SetTxPayloadWidth(4);

		nRF905SetTxAddress(192, 168, 0, 5);

		nRF905SetTxPayload(blah, 4);

		nRF905SendPacket();
#endif

#ifdef RECV

		_delay_ms(5000);
		nRF905Init();

		nRF905SetFreq(4331, 0, 0);

		nRF905SetTxRxAddWidth(4, 4);

		nRF905SetRxAddress(192, 168, 0, 5);

		nRF905SetRxPayloadWidth(4);
		nRF905SetTxPayloadWidth(4);

		nRF905SetTxAddress(192, 168, 0, 1);
		//nRF905GetTxAddress();

		//nRF905SetTxPayload(blah, 4);
		//nRF905GetTxPayload(4);


		nRF905EnableRecv();
		char buff[4];
		while(1)
		{
			nRF905RecvPacket(buff, 4, 1);
		}


#endif


		//nRF905DeviceSleep();
	}
	return 0;
}


