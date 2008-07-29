#ifndef MOOH
#define MOOH

#include <stdio.h>
#include <iostream>
#include "testoo.h"
#include "coroDataOO.h"


class baseTest
{
	public:
		virtual void RunL(coStData *rt) = 0;
};

class moo : baseTest
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
