#include <stdlib.h>
#include <inttypes.h>
#include "libhash/libhash.h"
#include "webserver/httpd-fs.h"

#ifndef GENERAL_H
#define GENERAL_H

struct accessHolder
{
	void (*run)(struct httpd_fs_file *file);
};


/*FAKE CLASSES*/
	/*CLASS dynaloader*/
	/*{*/
		/*STRUCTURE*/
		struct dynaloader
		{
			hshObj files;

			void (*registerPage)(struct dynaloader *, char *name, void (*run)(struct httpd_fs_file *file));
			struct accessHolder *(*fetchPage)(struct dynaloader *, const char *name);
			void (*destruct)(struct dynaloader *);
		};
		typedef struct dynaloader *dynld;

		/*CONSTRUCTOR*/
		dynld newDynaloaderObject();
		
		/*METHODS*/
		void registerPage(dynld, char *name, void (*run)(struct httpd_fs_file *file));
		struct accessHolder *fetchPage(dynld, const char *name);

		/*DESTRUCTOR*/
		void dynObjDestruct(dynld);
#endif
