#ifndef MOOH
#define MOOH

#include <stdio.h>
#include <iostream>
#include "testoo.h"
#include "fibre.h"


class baseTest
{
	public:
		virtual void RunL(fibre *rt) = 0;
};

class moo : baseTest
{
	private:

		int internalVal;

	public:
		moo(int val) : internalVal(val)
		{
		}

		void RunL(fibre *rt);
};

#endif
