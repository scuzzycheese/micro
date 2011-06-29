#include "lcd.h"
#include <stdio.h>
#include "LM6800/LM6800.h"

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

	LM6800Init();


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
					for(uint8_t x = 128; x < 192; x ++)
					{
						LM6800SetPixel(x, y);
					}
				}
				for(uint8_t y = 0; y < 64; y ++)
				{
					for(uint8_t x = 192; x < 255; x ++)
					{
						LM6800SetPixel(x, y);
					}
					LM6800SetPixel(255, y);
				}
			}
			if(ReceivedByte == 'g')
			{
				for(uint8_t y = 0; y < 1; y += 8)
				{
					for(uint8_t x = 192; x < 255; x ++)
					{
						uint8_t colVal = LM6800GetColumn(x, 0);
						char blah[30];
						sprintf(blah, "X: %d PAGE: %d COLVAL: 0x%X\r\n", x, y >> 3, colVal);
						for(char *tmp = blah; *tmp; tmp ++)
						{
							CDC_Device_SendByte(&VirtualSerial_CDC_Interface, *tmp);
						}
					}
				}
			}
			if(ReceivedByte == 'x')
			{
				for(uint8_t y = 0; y < 64; y ++)
				{
					for(uint8_t x = 128; x < 192; x ++)
					{
						if(x & 1) LM6800ClearPixel(x, y);
						else LM6800SetPixel(x, y);
					}
				}
				for(uint8_t y = 0; y < 64; y ++)
				{
					for(uint8_t x = 192; x < 255; x ++)
					{
						if(x & 1) LM6800ClearPixel(x, y);
						else LM6800SetPixel(x, y);
					}
					LM6800ClearPixel(255, y);
				}
			}
			if(ReceivedByte == 'c')
			{
				for(uint8_t y = 0; y < 64; y ++)
				{
					for(uint8_t x = 128; x < 192; x ++)
					{
						LM6800ClearPixel(x, y);
					}
				}
				for(uint8_t y = 0; y < 64; y ++)
				{
					for(uint8_t x = 192; x < 255; x ++)
					{
						LM6800ClearPixel(x, y);
					}
					LM6800ClearPixel(255, y);
				}
			}
			if(ReceivedByte == 'd')
			{
				LM6800DrawTest();
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

