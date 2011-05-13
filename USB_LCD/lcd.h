/* 
 * File:   lcd.h
 * Author: scuzzy
 *
 * Created on 10 May 2011, 10:23 PM
 */

#ifndef _LCD_H
#define	_LCD_H



/* Includes: */
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/delay.h>

#include "Descriptors.h"

#include <LUFA/Version.h>
#include <LUFA/Drivers/USB/USB.h>

/* Function Prototypes: */
void SetupHardware(void);

void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_ControlRequest(void);

void EVENT_CDC_Device_LineEncodingChanged(USB_ClassInfo_CDC_Device_t* const CDCInterfaceInfo);



#endif	/* _LCD_H */

