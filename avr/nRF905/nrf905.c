#include <avr/io.h>
#include <inttypes.h>
#define F_CPU 16000000UL  // 16 MHz
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "SPIDefs.h"
#include "nRF905_conf.h"


void SPI_MasterInit(void)
{
	/* Set MOSI and SCK output, all others input */
	DDR_SPI = (1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_SS);

	//SPI Master Mode
	SPCR = (1 << MSTR);

	//Set Speed (Fosc/4) (16 / 4 = 4Mhz)
	SPCR &= ~((1 << SPR1) | (1 << SPR0) | (1 << SPI2X));

	//set MSB
	SPCR &= ~(1 << DORD);

	//Enable SPI
	SPCR |= (1 << SPE);


}
void SPI_MasterStart()
{
	//Pull down the line for the correct slave
	NRF905_SS_PORT &= ~(1 << NRF905_SS);
}

void SPI_MasterEnd()
{
	//pull up the line again.
	NRF905_SS_PORT |= (1 << NRF905_SS);
}
unsigned char SPI_MasterTransmit(unsigned char cData)
{
	unsigned char data;

	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1 << SPIF)));

	data = SPDR;

	return data;
}

void nRF905Init()
{
	//nRF905 power down
	NRF905_CONTRL_DDR = (1 << NRF905_TXEN) | (1 << NRF905_TRX_CE) | (1 << NRF905_PWR_UP);
	NRF905_CONTRL_PORT &= ~((1 << NRF905_TXEN) | (1 << NRF905_TRX_CE) | (1 << NRF905_PWR_UP));


	NRF905_CONTRL_PORT |= (1 << NRF905_PWR_UP);
	//read the config data
	SPI_MasterStart();
	SPI_MasterTransmit(0x00);
	for(int i = 0; i < 10; i ++)
	{
		//send dummy bytes to read off the data
		SPI_MasterTransmit(initData[i]);
	}
	SPI_MasterEnd();
}


/* new style */
int main(void)
{
	SPI_MasterInit();


	//this has to be high from the start
	SPI_MasterEnd();

	while(1)
	{
		_delay_ms(5000);

		nRF905Init();



		SPI_MasterStart();
		SPI_MasterTransmit(0x10);
		for(int i = 0; i < 10; i ++)
		{
			//send dummy bytes to read off the data
			SPI_MasterTransmit(0x00);
		}
		SPI_MasterEnd();


		NRF905_CONTRL_PORT &= ~(1 << NRF905_PWR_UP);
	}
	return 0;
}

