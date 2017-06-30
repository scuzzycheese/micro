#include "heating_control.h"
#include <stdio.h>
#include "LM6800/LM6800.h"
#include "lcdClass.h"
#include "protocolHandler.h"
#include <util/delay.h>
#include "adc/adc.h"


/** LUFA CDC Class driver interface configuration and state information. This structure is
 *  passed to all CDC Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface =
	{
		.Config =
			{
				.ControlInterfaceNumber   = INTERFACE_ID_CDC_CCI,
				.DataINEndpoint           =
					{
						.Address          = CDC_TX_EPADDR,
						.Size             = CDC_TXRX_EPSIZE,
						.Banks            = 1,
					},
				.DataOUTEndpoint =
					{
						.Address          = CDC_RX_EPADDR,
						.Size             = CDC_TXRX_EPSIZE,
						.Banks            = 1,
					},
				.NotificationEndpoint =
					{
						.Address          = CDC_NOTIFICATION_EPADDR,
						.Size             = CDC_NOTIFICATION_EPSIZE,
						.Banks            = 1,
					},
			},
	};

/** Standard file stream for the CDC interface when set up, so that the virtual CDC COM port can be
 *  used like any regular character stream in the C APIs.
 */
static FILE USBSerialStream;


/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */

int main(void)
{


   SetupHardware();

   sei();

   struct lcdDriver lcdDriver;
   //register the LCD driver with this driver interface
   registerDriver(&lcdDriver, LM6800Register);
   lcdDriver.init();

   lcdDriver.clearScreen();

   lcdDriver.setPixel(0, 0);
   lcdDriver.setPixel(0, 7);
   lcdDriver.setPixel(63, 0);
   lcdDriver.setPixel(63, 7);

   lcdDriver.setPixel(64, 0);
   lcdDriver.setPixel(64, 7);
   lcdDriver.setPixel(127, 0);
   lcdDriver.setPixel(127, 7);


   lcdDriver.setPixel(64, 8);
   lcdDriver.setPixel(64, 15);
   lcdDriver.setPixel(127, 8);
   lcdDriver.setPixel(127, 15);

   lcdDriver.setPixel(0, 8);
   lcdDriver.setPixel(0, 15);
   lcdDriver.setPixel(63, 8);
   lcdDriver.setPixel(63, 15);

   lcdDriver.flushVM();


   enableADC();
   _delay_ms(2000);



   while(true)
   {
      _delay_ms(200);
      lcdDriver.clearController(0);

      lcdDriver.printf(0, 0, "Tank: ");
      lcdDriver.printf(0, 8, "Pipe: ");

      enableADC11();
      uint16_t adcValue = readADC();
      float steinhart = steinhartValue(adcValue);
      lcdDriver.printf(34, 0, "%.2f", steinhart);

      enableADC12();
      adcValue = readADC();
      steinhart = steinhartValue(adcValue);
      lcdDriver.printf(34, 8, "%.2f", steinhart);


      lcdDriver.flushVM();

   }

/*
   portHandlerObj lcdPort;
   portHandlerConstruct(&lcdPort, &VirtualSerial_CDC_Interface, &lcdDriver);
   portHandler(&lcdPort);
*/


/*
	SetupHardware();

	//Create a regular character stream for the interface so that it can be used with the stdio.h functions 
	CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);

	GlobalInterruptEnable();

	for (;;)
	{

		//Must throw away unused bytes from the host, or it will lock up while waiting for the device 
		CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);

		CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
		USB_USBTask();
	}
*/
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
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	ConfigSuccess &= CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface);

}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
}

/** CDC class driver callback function the processing of changes to the virtual
 *  control lines sent from the host..
 *
 *  \param[in] CDCInterfaceInfo  Pointer to the CDC class interface configuration structure being referenced
 */
void EVENT_CDC_Device_ControLineStateChanged(USB_ClassInfo_CDC_Device_t *const CDCInterfaceInfo)
{
	/* You can get changes to the virtual CDC lines in this callback; a common
	   use-case is to use the Data Terminal Ready (DTR) flag to enable and
	   disable CDC communications in your application when set to avoid the
	   application blocking while waiting for a host to become ready and read
	   in the pending data from the USB endpoints.
	*/
	bool HostReady = (CDCInterfaceInfo->State.ControlLineStates.HostToDevice & CDC_CONTROL_LINE_OUT_DTR) != 0;
}





