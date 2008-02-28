#include "index.h"
#include <avr/io.h>

//This function will soon take an char ** of input vars
int callFunc(char **vars, struct web_state *ws)
{
	DDRC = 0xFF;
	static int light = 0;

	writeLn("index getting called\r\n");
	PSOCK_BEGIN(&ws->po);

	PSOCK_SEND_STR(&ws->po, "<h1>Atmega 644 webserver</h1>");
	PSOCK_SEND_STR(&ws->po, "<b>Stats:</b><br/>");
	PSOCK_SEND_STR(&ws->po, "\tCHIP: Atmel Atmega 644 20Mhz 4Kb RAM.<br />");
	PSOCK_SEND_STR(&ws->po, "\tNIC: Microchip ENC28J60.<br />");
	PSOCK_SEND_STR(&ws->po, "\tTCP/IP stack: uIP<br />");
	PSOCK_SEND_STR(&ws->po, "\tIP: 192.168.0.40<br />");
	if(!light)
	{
		PSOCK_SEND_STR(&ws->po, "<a href=\"index.html\">Switch Light Off</a>");
		PORTC = 2;
		light = 1;
	}
	else
	{
		PSOCK_SEND_STR(&ws->po, "<a href=\"index.html\">Switch Light On</a>");
		PORTC &= ~(2);
		light = 0;
	}

	PSOCK_CLOSE(&ws->po);
	PSOCK_END(&ws->po);
}
