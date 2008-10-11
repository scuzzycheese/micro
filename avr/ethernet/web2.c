#include "web2.h"
#include "uip.h"
#include <string.h>

#include <stdio.h>
#include "pages/index.h"
#include "libhash/libhash.h"

static int handle_connection(struct web_state *ws);
static pageFunc comm = NULL;

//This might be wastefull
char *getVars[webVarSize * 2];

hshObj fls;
void web_init(void)
{
	fls = newHashObject();
	fls->addIndexString(fls, "/index.html", indexPage);

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


	#ifdef DEBUGSOCK
	writeLn("PAGE REGUEST: ");
	writeLn(ws->filename);
	writeLn("\r\n");
	#endif


	char *req = ws->filename;
	while(*(req ++))
	{
		if(*req == ISO_question) *req = 0;
	}

	memset(getVars, 0x00, sizeof(getVars));

	//This is dangrous parsing, that needs to be secured
	char *varKey = req;
	char *varValue = NULL;

	//add the first Key to the array
	int varCount = 0;
	getVars[varCount] = varKey;
	varCount ++;

	#ifdef DEBUGSOCK
	writeLn("varKey at the beginning: ");
	writeLn(varKey);
	writeLn("\r\n");
	#endif
	while(*(req ++) && varCount < (webVarSize * 2))
	{
		if(*req == ISO_equals)
		{
			writeLn("found = sign\r\n");
			*req = 0;
			req ++;
			varValue = req;
			getVars[varCount] = varValue;
			varCount ++;
		}
		if(*req == ISO_amp || !(*req))
		{
			writeLn("found & sign\r\n");
			*req = 0;
			req ++;
			varKey = req;
			#ifdef DEBUGSOCK
			writeLn("Got Some Vars - KEY: ");
			writeLn(varKey);
			writeLn(" VALUE: ");
			writeLn(varValue);
			writeLn("\r\n");
			#endif
			getVars[varCount] = varKey;
			varCount ++;
		}
	}


	//NOTE: This line causes a bug in GCC, BUG 27192
	//WORKAROUND: don't let the compiler optimise
	comm = fls->findIndexString(fls, ws->filename);
	if(comm)
	{
		//Send headers. This mechanism needs to be more complex, but it's ok for now
		PSOCK_SEND_STR(&ws->p, "HTTP/1.0 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n");

		#ifdef DEBUGSOCK
		writeLn("Calling the page\r\n");
		#endif
		PT_WAIT_THREAD(&((&ws->p)->pt), comm(getVars, ws));
	}
	else
	{
		PSOCK_SEND_STR(&ws->p, "HTTP/1.0 404 Not Found\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n");
		PT_WAIT_THREAD(&((&ws->p)->pt), error404(NULL, ws));
	}

	PSOCK_CLOSE(&ws->p);
	PSOCK_END(&ws->p);
}

