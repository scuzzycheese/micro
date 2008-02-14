#include "web2.h"
#include "uip.h"
#include <string.h>

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
	}
	handle_connection(ws);
}

static int handle_connection(struct web_state *ws)
{
	PSOCK_BEGIN(&ws->p);
	PSOCK_SEND_STR(&ws->p, "blah");
	PSOCK_CLOSE(&ws->p);
	PSOCK_END(&ws->p);
}

