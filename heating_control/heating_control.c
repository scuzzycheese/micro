#include "heating_control.h"
#include <stdio.h>
#include "LM6800/LM6800.h"
#include "lcdClass.h"
#include "protocolHandler.h"
#include <util/delay.h>


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

uint16_t readVcc();
void enableADC();
void disableADC();

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
   //lcdDriver.setPixel(10, 10);
   //lcdDriver.setPixel(20, 10);

   uint8_t char_counter = 0;
   for(uint8_t i = 0; i < 64; i += 8)
   {
      for(uint8_t j = 0; j < 255; j += 5)
      {
         //lcdDriver.printChar(j, i, char_counter ++);
      }
   }

   //lcdDriver.printf(0, 0, "Hello World!");
   //lcdDriver.printf(0, 10, "Pipe temp: %d%c", 45, 9);

   enableADC();
   while(true)
   {
      _delay_ms(2000);
      lcdDriver.clearScreen();
      lcdDriver.printf(0, 20, "VCC: %u", readVcc());
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

void enableADC() 
{
   //configure the ADC ports
   //I think I have more work to do here
   ADMUX = _BV(REFS0) | _BV(REFS1) | _BV(ADLAR) | _BV(MUX0) | _BV(MUX1);
   //turn on ADC
   ADCSRA |= _BV(ADEN);
}

void disableACD() 
{
   ADCSRA &= ~(_BV(ADEN));
}


uint16_t readVcc() {

   ADCSRA |= _BV(ADSC); // Start conversion
   while (bit_is_set(ADCSRA,ADSC)); // measuring

   uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
   uint8_t high = ADCH; // unlocks both


   uint16_t result = (low >> 6) | (high << 2);

   //result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
   return result; // Vcc in millivolts
}

