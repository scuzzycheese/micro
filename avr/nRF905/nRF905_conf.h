/* 
 * File:   nRF905_conf.h
 * Author: scuzzy
 *
 * Created on 26 July 2010, 12:55
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

