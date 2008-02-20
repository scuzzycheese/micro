#include "index.h"
#include <avr/io.h>

//This function will soon take an char ** of input vars
int callFunc(char **vars, struct psock p)
{
	PSOCK_BEGIN(&p);

	DDRC = 0xFF;
	static int light = 0;

	PSOCK_SEND_STR(&p, "<h1>Atmega 644 webserver</h1>");
	PSOCK_SEND_STR(&p, "<b>Stats:</b><br/>");
	PSOCK_SEND_STR(&p, "\tCHIP: Atmel Atmega 644 20Mhz 4Kb RAM.<br />");
	PSOCK_SEND_STR(&p, "\tNIC: Microchip ENC28J60.<br />");
	PSOCK_SEND_STR(&p, "\tTCP/IP stack: uIP<br />");
	PSOCK_SEND_STR(&p, "\tIP: 192.168.0.40<br />");
	PSOCK_SEND_STR(&p, "<a href=\"index.html\">");

	if(!light)
	{
		PSOCK_SEND_STR(&p, "Switch Light Off");
		PORTC = 2;
		light = 1;
	}
	else
	{
		PSOCK_SEND_STR(&p, "Switch Light On");
		PORTC &= ~(2);
		light = 0;
	}
	PSOCK_SEND_STR(&p, "</a>");

	PSOCK_CLOSE(&p);
	PSOCK_END(&p);
}

/*
	DDRC = 0xFF;

	static int light = 0;

	char testData[] = 
	"<h1>Atmega644 webserver</h1>"
	"<b>Stats:</b><br />"
	"\tCHIP: Atmel Atmega 644 20Mhz 4Kb RAM.<br />"
	"\tNIC: Microchip ENC28J60.<br />"
	"\tTCP/IP stack: uIP<br />"
	"\tIP: 192.168.0.40<br />"
	"<a href=\"index.html\">"
	"Switch Light Off"
	"</a>\0                   ";

	if(!light)
	{
		testData[sizeof(testData) - 28] = 'O';
		testData[sizeof(testData) - 27] = 'f';
		testData[sizeof(testData) - 26] = 'f';
		PORTC = 2;
		light = 1;
	}
	else if(light)
	{
		testData[sizeof(testData) - 28] = 'O';
		testData[sizeof(testData) - 27] = 'n';
		testData[sizeof(testData) - 26] = ' ';
		PORTC &= ~(2);
		light = 0;
	}
	*/
