#include "index.h"
#include <avr/io.h>

//This function will soon take an char ** of input vars
int indexPage(char **vars, struct web_state *ws)
{
	PSOCK_BEGIN(&ws->po);
	DDRC = 0xFF;

/*
	static int counter = 0;
	while(counter < 10)
	{
		if(vars[counter])
		{
			PSOCK_SEND_STR(&ws->po, "key: ");
			PSOCK_SEND_STR(&ws->po, vars[counter]);
			counter ++;
			PSOCK_SEND_STR(&ws->po, "<br/> value: ");
			PSOCK_SEND_STR(&ws->po, vars[counter]);
			PSOCK_SEND_STR(&ws->po, "<br/>");
		}
		counter ++;
	}
	//reset the counter
	counter = 0;

*/


	//writeLn("Inside the page\r\n");

	PSOCK_SEND_STR(&ws->po, "<h1>Atmega 644 webserver</h1>");
	PSOCK_SEND_STR(&ws->po, "<b>Stats:</b><br/>");
	PSOCK_SEND_STR(&ws->po, "\tCHIP: Atmel Atmega 644 20Mhz 4Kb RAM.<br/>");
	PSOCK_SEND_STR(&ws->po, "\tNIC: Microchip ENC28J60.<br/>");
	PSOCK_SEND_STR(&ws->po, "\tWebServer: Web2 (Daine Mamacos).<br/>");
	PSOCK_SEND_STR(&ws->po, "\tTCP/IP stack: uIP<br/>");
	PSOCK_SEND_STR(&ws->po, "\tIP: 192.168.1.40<br/>");
	//if(!(PORTC & (1 << 1)))
	if(strcmp(vars[1], "on") == 0)
	{
		PSOCK_SEND_STR(&ws->po, "<a href=\"index.html?light1=off\">Switch Light Off</a>");
		PORTC |= 2;
	}
	else
	{
		PSOCK_SEND_STR(&ws->po, "<a href=\"index.html?light1=on\">Switch Light On</a>");
		PORTC &= ~(2);
	}

	PSOCK_CLOSE(&ws->po);
	PSOCK_END(&ws->po);
}
