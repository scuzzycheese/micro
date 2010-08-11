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

#ifndef _NRF905_CONF_H
#define	_NRF905_CONF_H

#ifdef	__cplusplus
extern "C"
{
#endif

/*
 * These are defines for the nRF905 evaulation board, based on 433 Mhz.
 *
 * These will probably change later when the chip is on a PCB connected
 * directly with the microcontroller
 */

#define NRF905_CONTRL_PORT PORTC
#define NRF905_CONTRL_DDR DDRC
#define NRF905_TXEN PORTC1
#define NRF905_TRX_CE PORTC0
#define NRF905_PWR_UP PORTC2

#define NRF905_DR_PORT PIND
#define NRF905_DR_DDR DDRD
#define NRF905_CD PIN4
#define NRF905_AM PIN2
#define NRF905_DR PIN3

#define NRF905_SS_PORT PORTB
#define NRF905_SS PORTB2


unsigned char initData[10] =
{
	0b01101100,
	0b00001100,
	0b01000100,
	0b00100000,
	0b00100000,

	//Devices Address
	0b00000001,
	0b00000001,
	0b00000001,
	0b00000001,

	0b11011000,
};


#ifdef	__cplusplus
}
#endif

#endif	/* _NRF905_CONF_H */

