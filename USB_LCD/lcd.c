#include "lcd.h"
#include <stdio.h>
#include "LM6800/LM6800.h"
#include "lcdClass.h"

/** LUFA CDC Class driver interface configuration and state information. This structure is
 *  passed to all CDC Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface =
	{
		.Config =
			{
				.ControlInterfaceNumber         = 0,

				.DataINEndpointNumber           = CDC_TX_EPNUM,
				.DataINEndpointSize             = CDC_TXRX_EPSIZE,
				.DataINEndpointDoubleBank       = false,

				.DataOUTEndpointNumber          = CDC_RX_EPNUM,
				.DataOUTEndpointSize            = CDC_TXRX_EPSIZE,
				.DataOUTEndpointDoubleBank      = false,

				.NotificationEndpointNumber     = CDC_NOTIFICATION_EPNUM,
				.NotificationEndpointSize       = CDC_NOTIFICATION_EPSIZE,
				.NotificationEndpointDoubleBank = false,
			},
	};

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{

	SetupHardware();

	sei();

	struct lcdDriver lcdDriver;
	registerDriver(&lcdDriver, LM6800Register);
	lcdDriver.init();


	for (;;)
	{
		int16_t ReceivedByte = CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);

		/* Read bytes from the USB OUT endpoint into the USART transmit buffer */
		if (!(ReceivedByte < 0))
		{
			//CDC_Device_SendByte(&VirtualSerial_CDC_Interface, ReceivedByte);
			if(ReceivedByte == 's')
			{
				for(uint8_t y = 0; y < 64; y ++)
				{
					for(uint8_t x = 0; x < 255; x ++)
					{
						lcdDriver.setPixel(x, y);
					}
					lcdDriver.setPixel(255, y);
				}
			}
			if(ReceivedByte == 'x')
			{
				for(uint8_t y = 0; y < 64; y ++)
				{
					for(uint8_t x = 0; x < 255; x ++)
					{
						if(x & 1) lcdDriver.clearPixel(x, y);
						else lcdDriver.setPixel(x, y);
					}
					lcdDriver.clearPixel(255, y);
				}
			}
			if(ReceivedByte == 'b')
			{
				char data[64] =
				{
					0b00011000, 0b00100100, 0b01000010, 0b10000001, 0b01000010, 0b00100100, 0b00011000, 0b00000000,
					0b00011000, 0b00100100, 0b01000010, 0b10000001, 0b01000010, 0b00100100, 0b00011000, 0b00000000,
					0b00011000, 0b00100100, 0b01000010, 0b10000001, 0b01000010, 0b00100100, 0b00011000, 0b00000000,
					0b00011000, 0b00100100, 0b01000010, 0b10000001, 0b01000010, 0b00100100, 0b00011000, 0b00000000,
					0b00011000, 0b00100100, 0b01000010, 0b10000001, 0b01000010, 0b00100100, 0b00011000, 0b00000000,
					0b00011000, 0b00100100, 0b01000010, 0b10000001, 0b01000010, 0b00100100, 0b00011000, 0b00000000,
					0b00011000, 0b00100100, 0b01000010, 0b10000001, 0b01000010, 0b00100100, 0b00011000, 0b00000000,
					0b00011000, 0b00100100, 0b01000010, 0b10000001, 0b01000010, 0b00100100, 0b00011000, 0b00000000,
				};
				for(uint8_t chip = 0; chip < 4; chip ++)
				{
					for(uint8_t page = 0; page < 8; page ++)
					{
						lcdDriver.writeBlock(chip, page, data);
					}
				}
			}
			if(ReceivedByte == 'c')
			{
				lcdDriver.clearScreen();
			}
			if(ReceivedByte == 'r')
			{

				//uint8_t one = LM6800Read(1);
				//uint8_t two = LM6800Read(2);
				//uint8_t three = LM6800Read(3);
				//uint8_t four = LM6800Read(4);
				uint8_t status = LM6800ReadStatus(1);

				char blah[30];
				//sprintf(blah, "0x%X - 0x%X - 0x%X - 0x%X\r\n", one, two, three, four);
				sprintf(blah, "STATUS: 0x%X\r\n", status);
				for(char *tmp = blah; *tmp; tmp ++)
				{
					CDC_Device_SendByte(&VirtualSerial_CDC_Interface, *tmp);
				}

			}
			if(ReceivedByte == 'o')
			{
				LM6800Write(1,0x3F, LM6800_COMMAND);
			}
			if(ReceivedByte == 'f')
			{
				LM6800Write(1,0x3E, LM6800_COMMAND);
			}

			PORTE |= (1 << PORTE6);
			_delay_ms(10);
			PORTE &= ~(1 << PORTE6);
		}

		CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
		USB_USBTask();
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
	DDRE |= (1 << PORTE6);

	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);

	USB_Init();

	/* Start the flush timer so that overflows occur rapidly to push received bytes to the USB interface */
	TCCR0B = (1 << CS02);
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	//LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
	//LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	ConfigSuccess &= CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface);

	//LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
}


/** Event handler for the CDC Class driver Line Encoding Changed event.
 *
 *  \param[in] CDCInterfaceInfo  Pointer to the CDC class interface configuration structure being referenced
 */
void EVENT_CDC_Device_LineEncodingChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo)
{

	uint8_t ConfigMask = 0;

	switch (CDCInterfaceInfo->State.LineEncoding.ParityType)
	{
		case CDC_PARITY_Odd:
			ConfigMask = ((1 << UPM11) | (1 << UPM10));
			break;
		case CDC_PARITY_Even:
			ConfigMask = (1 << UPM11);
			break;
	}

	if (CDCInterfaceInfo->State.LineEncoding.CharFormat == CDC_LINEENCODING_TwoStopBits)
	  ConfigMask |= (1 << USBS1);
}

