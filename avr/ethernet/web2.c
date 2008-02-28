#include "web2.h"
#include "uip.h"
#include <string.h>
#include "dynaloader.h"

extern dynld fileObject;

static int handle_connection(struct web_state *ws);

void web_init(void)
{
	uip_listen(HTONS(80));
}

void web_appcall(void)
{
	struct web_state *ws = &(uip_conn->appstate);
	if(uip_connected())
	{
		PSOCK_INIT(&ws->p, ws->inputbuffer, sizeof(ws->inputbuffer));
		PSOCK_INIT(&ws->po, ws->inputbuffer, sizeof(ws->inputbuffer));
	}
	handle_connection(ws);


}

static int handle_connection(struct web_state *ws)
{
	PSOCK_BEGIN(&ws->p);

	PSOCK_READTO(&ws->p, ISO_space);
	if(strncmp(ws->inputbuffer, "GET ", 4) != 0)
	{
		PSOCK_CLOSE_EXIT(&ws->p);
	}

	PSOCK_READTO(&ws->p, ISO_space);
	if(ws->inputbuffer[0] != ISO_slash)
	{
		PSOCK_CLOSE_EXIT(&ws->p);
	}

	if(ws->inputbuffer[1] == ISO_space)
	{
		strncpy(ws->filename, "/index.html", sizeof(ws->filename));
	}
	else
	{
		ws->inputbuffer[PSOCK_DATALEN(&ws->p) - 1] = 0;
		strncpy(ws->filename, ws->inputbuffer, sizeof(ws->filename));
	}

	//Send headers. This mechanism needs to be more complex, but it's ok for now
	PSOCK_SEND_STR(&ws->p, "HTTP/1.0 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n");

	pageFunc comm = fileObject->fetchPage(fileObject, ws->filename);
	if(comm)
	{
		//NOTE: have to figure out why this is not working 100%
		//PT_WAIT_THREAD(&((&ws->p)->pt), comm(NULL, ws));
		PT_WAIT_THREAD(&((&ws->p)->pt), callFunc(NULL, ws));
	}
	else
	{
		writeLn("404\r\n");
		//404?
	}

	PSOCK_CLOSE(&ws->p);
	PSOCK_END(&ws->p);
}

