#ifndef WEB3H
#define WEB3H

#include "uipopt.h"
#include "config.h"

#define ISO_nl      0x0a
#define ISO_space   0x20
#define ISO_bang    0x21
#define ISO_percent 0x25
#define ISO_period  0x2e
#define ISO_slash   0x2f
#define ISO_colon   0x3a
#define ISO_question 0x3f
#define ISO_equals  0x3d
#define ISO_amp 0x26

typedef struct web_state
{
	char inputbuffer[100];
	char filename[100];
} __attribute__ ((packed)) uip_tcp_appstate_t;

typedef struct wrtDta
{
	char *data;
	int state;
} __attribute__ ((packed)) writeData;

void web_appcall(void);
#ifndef UIP_APPCALL
#define UIP_APPCALL web_appcall
#endif

void web_init(void);

#endif
