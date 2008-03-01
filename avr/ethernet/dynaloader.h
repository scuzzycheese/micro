#ifndef GENERAL_H
#define GENERAL_H

#include <stdlib.h>
#include <inttypes.h>
#include "libhash/libhash.h"
#include "uip.h"

typedef int (*pageFunc)(char **vars, struct web_state *ws);

/*FAKE CLASSES*/
	/*CLASS dynaloader*/
	/*{*/
		/*STRUCTURE*/
		struct dynaloader
		{
			hshObj files;

			void (*registerPage)(struct dynaloader *, char *name, pageFunc);
			pageFunc (*fetchPage)(struct dynaloader *, const char *name);
			void (*destruct)(struct dynaloader *);
		};
		typedef struct dynaloader *dynld;

		/*CONSTRUCTOR*/
		dynld newDynaloaderObject();
		
		/*METHODS*/
		void registerPage(dynld, char *name, pageFunc);
		pageFunc fetchPage(dynld, const char *name);

		/*DESTRUCTOR*/
		void dynObjDestruct(dynld);
#endif
