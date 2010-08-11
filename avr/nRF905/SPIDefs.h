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

#ifndef _SPIDEFS_H
#define	_SPIDEFS_H

#ifdef	__cplusplus
extern "C"
{
#endif

#define DDR_SPI DDRB
#define DD_MOSI PORTB3
#define DD_MISO PORTB4
#define DD_SCK PORTB5
#define DD_SS PORTB2

#ifdef	__cplusplus
}
#endif

#endif	/* _SPIDEFS_H */

