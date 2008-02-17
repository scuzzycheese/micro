#include <stdlib.h>
#include <inttypes.h>
#include "libhash/libhash.h"
#include "uip.h"

#ifndef GENERAL_H
#define GENERAL_H

struct accessHolder
{
	int (*run)(char **vars, struct psock p);
};


/*FAKE CLASSES*/
	/*CLASS dynaloader*/
	/*{*/
		/*STRUCTURE*/
		struct dynaloader
		{
			hshObj files;

			void (*registerPage)(struct dynaloader *, char *name, int (*run)(char **vars, struct psock p));
			struct accessHolder *(*fetchPage)(struct dynaloader *, const char *name);
			void (*destruct)(struct dynaloader *);
		};
		typedef struct dynaloader *dynld;

		/*CONSTRUCTOR*/
		dynld newDynaloaderObject();
		
		/*METHODS*/
		void registerPage(dynld, char *name, int (*run)(char **vars, struct psock p));
		struct accessHolder *fetchPage(dynld, const char *name);

		/*DESTRUCTOR*/
		void dynObjDestruct(dynld);
#endif
