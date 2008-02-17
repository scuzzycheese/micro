#include "dynaloader.h"

dynld newDynaloaderObject()
{
	dynld returnObj = malloc(sizeof(struct dynaloader));

	returnObj->files = newHashObject(); 

	/*assign all my members*/
	returnObj->registerPage = registerPage;
	returnObj->fetchPage = fetchPage;
	returnObj->destruct = dynObjDestruct;

	return returnObj;
}

void registerPage(dynld this, char *name, int (*run)(char **vars, struct psock p))
{
	struct accessHolder *newFile = malloc(sizeof(struct accessHolder));
	newFile->run = run;
	this->files->addIndexString(this->files, name, newFile);
}

struct accessHolder *fetchPage(dynld this, const char *name)
{
	return (struct accessHolder *)this->files->findIndexString(this->files, (char *)name);
}

void dynObjDestruct(dynld this)
{
	/*TODO: add code to free all the registered methods*/
	this->files->destruct(this->files);
	free(this);
}
