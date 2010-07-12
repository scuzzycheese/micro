#include "index-x86.h"

//This function will soon take an char ** of input vars
int indexPage(char **vars, struct web_state *ws)
{
	static int light = 0;

	uip_send("<h1>Atmega 644 webserver</h1>", strlen("<h1>Atmega 644 webserver</h1>"));
	uip_send("<b>Stats:</b><br/>", strlen("<b>Stats:</b><br/>"));
	uip_send("\tCHIP: Atmel Atmega 644 20Mhz 4Kb RAM.<br />", strlen("\tCHIP: Atmel Atmega 644 20Mhz 4Kb RAM.<br />"));
	uip_send("\tNIC: Microchip ENC28J60.<br />", strlen("\tNIC: Microchip ENC28J60.<br />"));
	uip_send("\tTCP/IP stack: uIP<br />", strlen("\tTCP/IP stack: uIP<br />"));
	uip_send("\tIP: 192.168.0.40<br />", strlen("\tIP: 192.168.0.40<br />"));
}
