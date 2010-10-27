#include "index.h"
#include <avr/io.h>

//This function will soon take an char ** of input vars
int indexPage(struct argData *args, coStData *regs)
{
	fib_send
	(
		"<h1>Atmega 644 webserver</h1>"
		"<b>Stats:</b><br/>"
		"\tCHIP: Atmel Atmega 644 20Mhz 4Kb RAM.<br/>"
		"\tNIC: Microchip ENC28J60.<br/>"
		"\tTCP/IP stack: uIP<br/>"
		"\tIP: 192.168.0.17<br/>",
	 	regs
	);
	fib_send
	(
		"<a href=\"?redlight=on\">turn on red light</a><br/>"
		"<a href=\"?redlight=off\">turn off red light</a><br/>"
		"<a href=\"?greenlight=on\">turn on green light</a><br/>"
		"<a href=\"?greenlight=off\">turn off green light</a><br/>",
		regs
	);

	fib_send("\tARGS: <br/>", regs);
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
			fib_send("\t\t", regs);
			fib_send(args[i].argName, regs);
			fib_send(": ", regs);
			if(args[i].argValue) fib_send(args[i].argValue, regs);
			fib_send("<br/>", regs);
		}
	}

}
