#ifndef MOOH
#define MOOH

#include <stdio.h>
#include "testoo.h"
#include "coroDataOO.h"

class moo
{
	private:

	int internalVal;

	public:
	moo(int val) : internalVal(val)
	{
	}

	void RunL(coStData *rt);
};

#endif
