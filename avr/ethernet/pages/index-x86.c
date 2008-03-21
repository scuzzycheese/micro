#include "index.h"

//This function will soon take an char ** of input vars
int callFunc(char **vars, struct web_state *ws)
{
	PSOCK_BEGIN(&ws->po);
	static int light = 0;

	PSOCK_SEND_STR(&ws->po, "<h1>Atmega 644 webserver</h1>");
	PSOCK_SEND_STR(&ws->po, "<b>Stats:</b><br/>");
	PSOCK_SEND_STR(&ws->po, "\tCHIP: Atmel Atmega 644 20Mhz 4Kb RAM.<br />");
	PSOCK_SEND_STR(&ws->po, "\tNIC: Microchip ENC28J60.<br />");
	PSOCK_SEND_STR(&ws->po, "\tTCP/IP stack: uIP<br />");
	PSOCK_SEND_STR(&ws->po, "\tIP: 192.168.0.40<br />");

	PSOCK_CLOSE(&ws->po);
	PSOCK_END(&ws->po);
}
