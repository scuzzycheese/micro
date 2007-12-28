#include "index.h"
#include <avr/io.h>

void callFunc(struct httpd_fs_file *file)
{
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

	file->data = testData;
	file->len = sizeof(testData) - 20;
}
