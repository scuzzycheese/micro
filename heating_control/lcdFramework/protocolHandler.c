#include "protocolHandler.h"
#include <inttypes.h>

void portHandlerConstruct(portHandlerObj *this, USB_ClassInfo_CDC_Device_t *VirtualSerial_CDC_Interface, struct lcdDriver *driver)
{
	this->VirtualSerial_CDC_Interface = VirtualSerial_CDC_Interface;
	this->lcdDriver = driver;
}

//Need to put a limit on how long we can block for, I think
int16_t CDC_Device_ReceiveByte_blocking(USB_ClassInfo_CDC_Device_t *VirtualSerial_CDC_Interface)
{
	int16_t ReceivedByte = -1;
	while(1)
	{
		ReceivedByte = CDC_Device_ReceiveByte(VirtualSerial_CDC_Interface);
		if(!(ReceivedByte < 0)) return ReceivedByte;
	}
}

//NOTE: LEAST SIGNIFICANT BYTE FIRST!!!!
lcdXYType fetchXYFromSerial(USB_ClassInfo_CDC_Device_t *VirtualSerial_CDC_Interface)
{
	lcdXYType xyVal = 0;
	for(uint8_t i = 0; i < sizeof(lcdXYType); i ++)
	{
		 xyVal |= (CDC_Device_ReceiveByte_blocking(VirtualSerial_CDC_Interface) << (8 * i));
	}
	return xyVal;
}

void portHandler(portHandlerObj *this)
{


	this->lcdDriver->clearScreen();
	while(1)
	{
		int16_t ReceivedDoubleByte = CDC_Device_ReceiveByte(this->VirtualSerial_CDC_Interface);
		uint8_t ReceivedByte = 0;

		if(!(ReceivedDoubleByte < 0))
		{
			ReceivedByte = ReceivedDoubleByte;
		}
		else
		{
			CDC_Device_USBTask(this->VirtualSerial_CDC_Interface);
			USB_USBTask();
			continue;
		}

		switch((ReceivedByte & 0b11000000) >> 6)
		{
			case 0:
			{
				switch(ReceivedByte & 0b00111111)
				{
					//init
					case 0:
					{
						this->lcdDriver->init();
						break;
					}
					//reset
					case 1:
					{
						this->lcdDriver->reset();
						break;
					}
					//clearScreen
					case 2:
					{
						this->lcdDriver->clearScreen();
						break;
					}
				}
				break;
			}
			case 1:
			{
				switch(ReceivedByte & 0b00111111)
				{
					//setPixel
					case 0:
					{
						lcdXYType x = fetchXYFromSerial(this->VirtualSerial_CDC_Interface);
						lcdXYType y = fetchXYFromSerial(this->VirtualSerial_CDC_Interface);
						this->lcdDriver->setPixel(x, y);
						break;
					}
					//clearPixel
					case 1:
					{
						lcdXYType x = fetchXYFromSerial(this->VirtualSerial_CDC_Interface);
						lcdXYType y = fetchXYFromSerial(this->VirtualSerial_CDC_Interface);
						this->lcdDriver->clearPixel(x, y);
						break;
					}
					//writeBlock
					//TODO: turn this into a streaming function, where each byte of the block
					//is written as it comes off the USB port
					case 2:
					{
						lcdXYType x = fetchXYFromSerial(this->VirtualSerial_CDC_Interface);
						lcdXYType y = fetchXYFromSerial(this->VirtualSerial_CDC_Interface);
						char blockData[LCD_BYTES_PER_BLOCK];
						for(int i = 0; i < 64; i ++)
						{
							blockData[i] = CDC_Device_ReceiveByte_blocking(this->VirtualSerial_CDC_Interface);
						}
						this->lcdDriver->writeBlock(x, y, blockData);
						break;
					}
				}
				break;
			}
			case 2:
			{
				switch(ReceivedByte & 0b00111111)
				{
					//getPixel
					//NOTE: NOT TESTED
					case 0:
					{
						lcdXYType x = fetchXYFromSerial(this->VirtualSerial_CDC_Interface);
						lcdXYType y = fetchXYFromSerial(this->VirtualSerial_CDC_Interface);
						union pixelColour pxColour;
						this->lcdDriver->getPixel(x, y, &pxColour);
						for(uint8_t i = 0; i < sizeof(union pixelColour); i ++)
						{
							CDC_Device_SendByte(this->VirtualSerial_CDC_Interface, *(((char *)&pxColour) + i));
						}
						break;
					}
					//getLcdData
					case 1:
					{
						struct lcdData lcdData = this->lcdDriver->getLcdData();
						for(uint8_t i = 0; i < sizeof(struct lcdData); i ++)
						{
							CDC_Device_SendByte(this->VirtualSerial_CDC_Interface, *(((char *)&lcdData) + i));
						}
						break;
					}

				}
				break;
			}
		}

		CDC_Device_USBTask(this->VirtualSerial_CDC_Interface);
		USB_USBTask();
	}

}
