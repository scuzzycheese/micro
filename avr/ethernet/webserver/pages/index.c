#include "index.h"
#include <avr/io.h>
#include <stdio.h>

//This function will soon take an char ** of input vars
int indexPage(struct argData *args)
{
	//Lets get our IP address for fun
	uip_ipaddr_t ipaddr;
	uip_gethostaddr(ipaddr);
	char IPAdd[16];
	sprintf(IPAdd, "%d.%d.%d.%d", (uint8_t)ipaddr[0], (uint8_t)(ipaddr[0] >> 8), (uint8_t)ipaddr[1], (uint8_t)(ipaddr[1] >> 8));


	fib_send
	(
		"<h1>Atmega 644 webserver</h1>"
		"<b>Stats:</b><br/>"
		"\tCHIP: Atmel Atmega 644 20Mhz 4Kb RAM.<br/>"
#ifdef ENC28J60
		"\tNIC: Microchip ENC28J60.<br/>"
#elif CP2200
		"\tNIC: Silicon Labs CP2200.<br/>"
#endif
		"\tTCP/IP stack: uIP<br/>"
		"\tIP: "
	);
	fib_send(IPAdd);
	fib_send
	(
		"<br/><a href=\"?redlight=on\">turn on red light</a><br/>"
		"<a href=\"?redlight=off\">turn off red light</a><br/>"
	);
	fib_send
	(
		"<a href=\"?greenlight=on\">turn on green light</a><br/>"
		"<a href=\"?greenlight=off\">turn off green light</a><br/>"
	);
	fib_send
	(
		"<a href=\"?testlight=on\">turn on test light</a><br/>"
		"<a href=\"?testlight=off\">turn off test light</a><br/>"
	);

	fib_send("\tARGS: <br/>");
	int i;
	for(i = 0; i < 5; i ++)
	{
		if(args[i].argName)
		{
			if(strcmp(args[i].argName, "greenlight") == 0)
			{
				if(strcmp(args[i].argValue, "off") == 0)
				{
					PORTC |= 1;
				}
				else
				{
					PORTC &= ~1;
				}
			}
			if(strcmp(args[i].argName, "redlight") == 0)
			{
				if(strcmp(args[i].argValue, "off") == 0)
				{
					PORTC |= 2;
				}
				else
				{
					PORTC &= ~2;
				}
			}
			if(strcmp(args[i].argName, "testlight") == 0)
			{
				if(strcmp(args[i].argValue, "on") == 0)
				{
					PORTB |= 1;
				}
				else
				{
					PORTB &= ~1;
				}
			}
			fib_send("\t\t");
			fib_send(args[i].argName);
			fib_send(": ");
			if(args[i].argValue) fib_send(args[i].argValue);
			fib_send("<br/>");
		}
	}

}
