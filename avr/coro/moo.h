#ifndef MOOH
#define MOOH

#include <stdio.h>
#include "coroDataOO.h"
#include "testoo.h"


class moo
{
	private:

	int internalVal;

	moo(int val) : internalVal(val)
	{
	}

	void RunL(coStData *rt);
};

#endif
