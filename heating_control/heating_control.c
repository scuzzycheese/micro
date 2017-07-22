#include "heating_control.h"
#include <stdio.h>
#include "LM6800/LM6800.h"
#include "lcdClass.h"
#include "protocolHandler.h"
#include <util/delay.h>
#include "adc/adc.h"
#include "panels/temperature_panel.h"
#include "panels/time_panel.h"
#include "DS1302/DS1302.h"
#include "utils/utils.h"


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

struct lcdDriver lcdDriver;
uint8_t backlight_value = 255;
uint8_t direction = 0;

ISR(INT0_vect) 
{
   cli();
   _delay_ms(1000);
   
   //Clear any interrupts that occured during this ISR
   EIFR |= (0x0F);
   sei();
}

ISR(INT1_vect) 
{
   cli();
   _delay_ms(1);

   if((PIND & ((1 << PORTD2) | (1 << PORTD1))) == 0)
   {
      lcdDriver.setBacklight(++backlight_value);
   } 
   else
   {
      lcdDriver.setBacklight(--backlight_value);
   }
   
   //Clear any interrupts that occured during this ISR
   EIFR |= (0x0F);
   sei();
}

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */

int main(void)
{
   SetupHardware();


   //Disable interrupts while configuring the interrupt conditions
   //as fiddling with the ISCnx registers can cause an interrupt
   cli();
   //Configure interrupts here
   EIMSK &= ~(0x0F);

   EICRA |= (1 << ISC01);
   EICRA |= (1 << ISC11);
   //EICRA |= (1 << ISC21);

   EIMSK |= (1 << INT0);
   EIMSK |= (1 << INT1);
   //EIMSK |= (1 << INT2);
   sei();


   disableIndexer();
   //struct lcdDriver lcdDriver;
   //register the LCD driver with this driver interface
   registerDriver(&lcdDriver, LM6800Register);
   lcdDriver.init();

   lcdDriver.clearScreen();

   //Blinky
   lcdDriver.setBacklight(0);
   _delay_ms(200);
   lcdDriver.setBacklight(255);

   enableIndexer();

   struct temperaturePanel temperaturePanel;
   temperaturePanel.lcdDriver = &lcdDriver;
   temperaturePanel.panelNumber = 0;


   struct timePanel timePanel;
   timePanel.lcdDriver = &lcdDriver;
   timePanel.panelNumber = 1;

   DS1302Init();
   //Make sure we can write time to the device
   DS1302ClearWPBit();
   //These are just test values
   DS1302WriteSeconds(10);
   DS1302WriteMinutes(10);
   DS1302WriteHours(10);
   DS1302WriteDayOfMonth(10);
   DS1302WriteMonth(10);
   DS1302WriteDayOfWeek(4);
   DS1302WriteYear(2010);
   DS1302SetWPBit();


   enableADC();
   _delay_ms(2000);


   while(true)
   {
      drawTemperaturePanel(&temperaturePanel);
      drawTimePanel(&timePanel);

      disableIndexer();
      lcdDriver.clearController(3);
      lcdDriver.printf(193, 0, "%d", backlight_value);
      lcdDriver.flushVM();
      enableIndexer();

      _delay_ms(200);


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





