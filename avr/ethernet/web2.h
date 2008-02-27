#include "uipopt.h"
#include "psock.h"

#ifndef WEB2H
#define WEB2H

#define ISO_nl      0x0a
#define ISO_space   0x20
#define ISO_bang    0x21
#define ISO_percent 0x25
#define ISO_period  0x2e
#define ISO_slash   0x2f
#define ISO_colon   0x3a

typedef struct web_state
{
	struct psock p, po;
	char inputbuffer[100];
	char filename[20];
} uip_tcp_appstate_t;

typedef struct wrtDta
{
	char *data;
	int state;
} writeData;

void web_appcall(void);
#ifndef UIP_APPCALL
#define UIP_APPCALL web_appcall
#endif

void web_init(void);

#endif
