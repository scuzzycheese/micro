#include "index.h"
#include <avr/io.h>

//This function will soon take an char ** of input vars
int indexPage(struct argData *args, coStData *regs)
{
	static int light = 0;

	light ^= 1;

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
	if(light)
	{
		fib_send("\tLIGHT: On<br/>", regs);
	}
	else
	{
		fib_send("\tLIGHT: Off<br/>", regs);
	}

	fib_send("\tARGS: <br/>", regs);
	int i;
	for(i = 0; i < 5; i ++)
	{
		if(args[i].argName)
		{
			fib_send("\t\t", regs);
			fib_send(args[i].argName, regs);
			fib_send(": ", regs);
			if(args[i].argValue) fib_send(args[i].argValue, regs);
			fib_send("<br/>", regs);
		}
	}

}
