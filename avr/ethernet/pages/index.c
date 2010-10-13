#include "index.h"
#include <avr/io.h>

//This function will soon take an char ** of input vars
int indexPage(struct argData *args, coStData *regs)
{
	static int light = 0;

	light ^= 1;

	fib_send("<h1>Atmega 644 webserver</h1>", regs);
	fib_send("<b>Stats:</b><br/>", regs);
	fib_send("\tCHIP: Atmel Atmega 644 20Mhz 4Kb RAM.<br/>", regs);
	fib_send("\tNIC: Microchip ENC28J60.<br/>", regs);
	fib_send("\tTCP/IP stack: uIP<br/>", regs);
	fib_send("\tIP: 192.168.0.40<br/>", regs);
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
