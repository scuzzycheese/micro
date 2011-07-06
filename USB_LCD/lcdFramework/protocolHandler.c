#include "protocolHandler.h"


void portHandlerConstruct(portHandlerObj *this, USB_ClassInfo_CDC_Device_t *VirtualSerial_CDC_Interface, struct lcdDriver *driver)
{
	this->VirtualSerial_CDC_Interface = VirtualSerial_CDC_Interface;
	this->lcdDriver = driver;
}

void portHandler(portHandlerObj *this)
{

	while(1)
	{
		uint8_t ReceivedByte = CDC_Device_ReceiveByte(this->VirtualSerial_CDC_Interface);

		switch(ReceivedByte & 0b11000000)
		{
			case 0:
			{
				switch(ReceivedByte & 0b00111111)
				{
					case 0:
					{
						this->lcdDriver->init();
						break;
					}
					case 1:
					{
						this->lcdDriver->reset();
						break;
					}
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
						uint8_t x = CDC_Device_ReceiveByte(this->VirtualSerial_CDC_Interface);
						uint8_t y = CDC_Device_ReceiveByte(this->VirtualSerial_CDC_Interface);
						this->lcdDriver->setPixel(x, y);
						break;
					}
					//clearPixel
					case 1:
					{
						uint8_t x = CDC_Device_ReceiveByte(this->VirtualSerial_CDC_Interface);
						uint8_t y = CDC_Device_ReceiveByte(this->VirtualSerial_CDC_Interface);
						this->lcdDriver->clearPixel(x, y);
						break;
					}
					//writeBlock
					case 2:
					{
						uint8_t x = CDC_Device_ReceiveByte(this->VirtualSerial_CDC_Interface);
						uint8_t y = CDC_Device_ReceiveByte(this->VirtualSerial_CDC_Interface);
						char blockData[64];
						for(int i = 0; i < 64; i ++)
						{
							blockData[i] = CDC_Device_ReceiveByte(this->VirtualSerial_CDC_Interface);
						}
						this->lcdDriver->writeBlock(x, y, blockData);
						break;
					}
				}
				break;
			}
			case 2:
			{
				break;
			}
		}

	}

}
