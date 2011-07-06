/* 
 * File:   protocolHandler.h
 * Author: scuzzy
 *
 * Created on 05 July 2011, 4:14 PM
 */

#include <LUFA/Drivers/USB/USB.h>
#include "LM6800/LM6800.h"
#include "lcdClass.h"

#ifndef _PROTOCOLHANDLER_H
#define	_PROTOCOLHANDLER_H

#ifdef	__cplusplus
extern "C"
{
#endif

	typedef struct lcdPortHandler
	{
		struct lcdDriver *lcdDriver;
		USB_ClassInfo_CDC_Device_t *VirtualSerial_CDC_Interface;
	} portHandlerObj;




#ifdef	__cplusplus
}
#endif

#endif	/* _PROTOCOLHANDLER_H */

