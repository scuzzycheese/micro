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
	printf("Webserver hit...\n");
	if(uip_connected())
	{
		if(uip_newdata())
		{
			printf("New data on socket\n");
			handle_connection(ws);
		}
	}

}

static int handle_connection(struct web_state *ws)
{
	uint16_t len = uip_datalen();
	char *dataPtr = (char *)uip_appdata;

	printf("DATA LEN: %d\n", len);


	if(len > 0)
	{
		if(strncmp(dataPtr, "GET ", 4) != 0)
		{
			uip_close();
			return;
		}

		while(*(dataPtr ++) != ISO_space)

		if(*dataPtr != ISO_slash)
		{
			uip_close();
			return;
		}
		dataPtr ++;
		if(*dataPtr == ISO_space)
		{
			strncpy(ws->filename, "/index.html", sizeof(ws->filename));
		}
		else
		{
			dataPtr[len - 1] = 0;
			strncpy(ws->filename, dataPtr, sizeof(ws->filename));
		}

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

		while(*(req ++) && varCount < (webVarSize * 2))
		{
			if(*req == ISO_equals)
			{
				*req = 0;
				req ++;
				varValue = req;
				getVars[varCount] = varValue;
				varCount ++;
			}
			if(*req == ISO_amp || !(*req))
			{
				*req = 0;
				req ++;
				varKey = req;
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
			uip_send("HTTP/1.0 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n", strlen("HTTP/1.0 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n"));

			comm(getVars, ws);
		}
		else
		{
			uip_send("HTTP/1.0 404 Not Found\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n", strlen("HTTP/1.0 404 Not Found\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n"));
			error404(NULL, ws);
		}

		uip_close();
	}
}


