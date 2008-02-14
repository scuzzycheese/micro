#include "uipopt.h"
#include "psock.h"

#ifndef WEB2H
#define WEB2H

typedef struct web_state
{
	struct psock p;
	char inputbuffer[100];
} uip_tcp_appstate_t;

void web_appcall(void);
#ifndef UIP_APPCALL
#define UIP_APPCALL web_appcall
#endif

void web_init(void);

#endif
