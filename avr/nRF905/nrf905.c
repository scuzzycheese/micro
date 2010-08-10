#include <avr/io.h>
#include <inttypes.h>
#define F_CPU 16000000UL  // 16 MHz
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "SPIDefs.h"
#include "nRF905_conf.h"

/**
 * TODO make this size configureable at compile time maybe?
 */
char recvBuffer[32];

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


//Please follow the documentation for these values
void nRF905SetFreq(uint16_t freqKhz, uint8_t HFREQ_PLL, uint8_t power)
{
	uint16_t channel = 0;
	if(HFREQ_PLL == 0)
	{
		 channel = freqKhz - 4224;
	}
	if(HFREQ_PLL == 1)
	{
		 channel = ((freqKhz / 2) - 4224);
	}

	channel |= (power & 2) << 10 | (HFREQ_PLL & 1) << 9;

	SPI_MasterStart();
	SPI_MasterTransmit(0x80 | (uint8_t)((channel >> 8) & 0x0F));
	SPI_MasterTransmit((uint8_t)channel);
	SPI_MasterEnd();
}

//valid values are 1, 2, 3 or 4
void nRF905SetTxRxAddWidth(uint8_t txAddWidth, uint8_t rxAddWidth)
{
	uint8_t addLenWidth = (txAddWidth << 4) | (rxAddWidth & 0x0F);
	SPI_MasterStart();
	SPI_MasterTransmit(0x02);
	SPI_MasterTransmit(addLenWidth);
	SPI_MasterEnd();
}

void nRF905SetRxAddress(uint8_t address1, uint8_t address2, uint8_t address3, uint8_t address4)
{
	SPI_MasterStart();
	SPI_MasterTransmit(0x05);
	SPI_MasterTransmit(address1);
	SPI_MasterTransmit(address2);
	SPI_MasterTransmit(address3);
	SPI_MasterTransmit(address4);
	SPI_MasterEnd();
}

void nRF905SetRxPayloadWidth(uint8_t width)
{
	//a small safety check to make sure, our payload isn't bigger than 32 bytes
	if(width > 32) width = 32;
	SPI_MasterStart();
	SPI_MasterTransmit(0x03);
	SPI_MasterTransmit(width);
	SPI_MasterEnd();
}

void nRF905SetTxPayloadWidth(uint8_t width)
{
	//a small safety check to make sure, our payload isn't bigger than 32 bytes
	if(width > 32) width = 32;
	SPI_MasterStart();
	SPI_MasterTransmit(0x04);
	SPI_MasterTransmit(width);
	SPI_MasterEnd();
}

void nRF905SetTxAddress(uint8_t address1, uint8_t address2, uint8_t address3, uint8_t address4)
{
	SPI_MasterStart();
	SPI_MasterTransmit(0x22);
	SPI_MasterTransmit(address1);
	SPI_MasterTransmit(address2);
	SPI_MasterTransmit(address3);
	SPI_MasterTransmit(address4);
	SPI_MasterEnd();
}

//TODO: make this function return something useful, like the address (:
void nRF905GetTxAddress()
{
	SPI_MasterStart();
	SPI_MasterTransmit(0x23);
	SPI_MasterTransmit(0x00);
	SPI_MasterTransmit(0x00);
	SPI_MasterTransmit(0x00);
	SPI_MasterTransmit(0x00);
	SPI_MasterEnd();
}

//Please note, the payload width should match the payload width you have
//configured with nRF905SetTxPayloadWidth, because only that ammount of
//data will be sent from the unit, and you'll be sending unessesary
//data over the SPI Bus.
void nRF905SetTxPayload(char *payload, uint8_t payloadWidth)
{

	SPI_MasterStart();
	SPI_MasterTransmit(0x20);
	for(uint8_t i = 0; i < payloadWidth; ++ i)
	{
		SPI_MasterTransmit(payload[i]);
	}
	SPI_MasterEnd();

}

//TODO: make this function return something useful, like the payload (:
void nRF905GetTxPayload(uint8_t payloadWidth)
{
	SPI_MasterStart();
	SPI_MasterTransmit(0x21);
	for(uint8_t i = 0; i < payloadWidth; ++ i)
	{
		SPI_MasterTransmit(0x00);
	}
	SPI_MasterEnd();
}

void nRF905SendPacket()
{
	NRF905_CONTRL_PORT |= (1 << NRF905_TXEN) | (1 << NRF905_TRX_CE);
	//once we start sending the packet, we wait for the DR pin to go high
	//indicating that the data is finished sending
	while(!(NRF905_DR_PORT & (1 << NRF905_DR)));
	NRF905_CONTRL_PORT &= ~((1 << NRF905_TXEN) | (1 << NRF905_TRX_CE));
}

void nRF905DeviceSleep()
{
	NRF905_CONTRL_PORT &= ~(1 << NRF905_PWR_UP);
}

//TODO: make this function return something useful, like the config (:
void nRF905GetConfig(uint8_t from, uint8_t count, char *buffer)
{
		SPI_MasterStart();
		SPI_MasterTransmit(0x10 | (from & 0x0F));
		for(int i = 0; i < count; i ++)
		{
			buffer[i] = SPI_MasterTransmit(0x00);
		}
		SPI_MasterEnd();
}

void nRF905SetConfig(uint8_t from, uint8_t count, char *buffer)
{
	SPI_MasterStart();
	SPI_MasterTransmit(0x00 | (from & 0x0F));
	for(int i = 0; i < count; i ++)
	{
		//send dummy bytes to read off the data
		SPI_MasterTransmit(buffer[i]);
	}
	SPI_MasterEnd();

}

void nRF905Init()
{
	//nRF905 power down
	NRF905_CONTRL_DDR = (1 << NRF905_TXEN) | (1 << NRF905_TRX_CE) | (1 << NRF905_PWR_UP);
	NRF905_CONTRL_PORT &= ~((1 << NRF905_TXEN) | (1 << NRF905_TRX_CE));
	NRF905_CONTRL_PORT |= (1 << NRF905_PWR_UP);

	//NRF905_DR_DDR &= ~((1 << NRF905_AM) | (1 << NRF905_CD) | (1 << NRF905_DR));

	//read the config data
	nRF905SetConfig(0, 10, initData);
	SPI_MasterEnd();
}

void nRF905EnableRecv()
{
	NRF905_CONTRL_PORT &= ~(1 << NRF905_TXEN);
	NRF905_CONTRL_PORT |= 1 << NRF905_TRX_CE;
}

void nRF905DisableRecv()
{
	NRF905_CONTRL_PORT &= ~(1 << NRF905_TXEN);
	NRF905_CONTRL_PORT &= ~(1 << NRF905_TRX_CE);
}

char *nRF905RecvPacket(uint8_t payloadWidth)
{
	//we only want to continue while AM is high (in case of a CRC failure)
	while(NRF905_DR_PORT & (1 << NRF905_AM))
	{
		//our data is ready for clocking out the RX buffer
		if(NRF905_DR_PORT & (1 << NRF905_DR))
		{
			//we need to turn off receive mode now
			//TODO: think about this one, maybe make it an option
			//we sometimes want to stay in recv mode after recieving a packet
			//NRF905_CONTRL_PORT &= ~(1 << NRF905_TRX_CE);

			SPI_MasterStart();
			SPI_MasterTransmit(0x24);
			for(uint8_t i = 0; i < payloadWidth; ++ i)
			{
				recvBuffer[i] = SPI_MasterTransmit(0x00);
			}
			SPI_MasterEnd();
		}
	}
	return recvBuffer;
}

void nRF905SetReduceRxPwr(uint8_t rxPwrRed)
{
	char byte1Config;
	nRF905GetConfig(1, 1, &byte1Config);
	if(rxPwrRed)
	{
		byte1Config |= 0x10;
	}
	else
	{
		byte1Config &= ~(0x10);
	}
	nRF905SetConfig(1, 1, &byte1Config);
}

void nRF905SetAutoRetransmit(uint8_t autoRetransmit)
{
	char byte1Config;
	nRF905GetConfig(1, 1, &byte1Config);
	if(autoRetransmit)
	{
		byte1Config |= 0x20;
	}
	else
	{
		byte1Config &= ~(0x20);
	}
	nRF905SetConfig(1, 1, &byte1Config);
}

void nRF905SetOuputClock(uint8_t outClockFreq, uint8_t enable)
{
	outClockFreq = (outClockFreq > 3) ? 3 : outClockFreq;
	enable = (enable) ? 1 : 0;
	char byte9Config;
	nRF905GetConfig(9, 1, &byte9Config);
	byte9Config = (byte9Config & 0b11111000) | outClockFreq | enable << 2;
	nRF905SetConfig(9, 1, &byte9Config);
}

void nRF905SetCRC(uint8_t CRCMode, uint8_t enable)
{
	CRCMode = (CRCMode) ? 1 : 0;
	enable = (enable) ? 1 : 0;
	char byte9Config;
	nRF905GetConfig(9, 1, &byte9Config);
	byte9Config = (byte9Config & 0b00111111) | CRCMode << 7 | enable << 6;
	nRF905SetConfig(9, 1, &byte9Config);
}

void nRF905SetOscFreq(uint8_t freq)
{
	freq = (freq > 4) ? 4 : freq;
	char byte9Config;
	nRF905GetConfig(9, 1, &byte9Config);
	byte9Config = (byte9Config & 0b11000111) | freq << 3;
	nRF905SetConfig(9, 1, &byte9Config);
}


/* new style */
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
		nRF905GetTxAddress();

		nRF905SetTxPayload(blah, 4);
		nRF905GetTxPayload(4);

		nRF905GetConfig();

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

		char buff;
		nRF905GetConfig(9, 1, &buff);
		nRF905SetOscFreq(0);
		nRF905GetConfig(9, 1, &buff);
		nRF905SetOscFreq(3);
		nRF905GetConfig(9, 1, &buff);

		/*
		while(1)
		{
			nRF905EnableRecv();
			nRF905RecvPacket(4);
		}
		 */
		 

#endif


		//nRF905DeviceSleep();
	}
	return 0;
}

