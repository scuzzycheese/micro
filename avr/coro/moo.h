#ifndef MOOH
#define MOOH

#include <stdio.h>
#include <iostream>
#include "testoo.h"
#include "fibre.h"


class baseTest
{
	public:
		fibre *rt;
		virtual void RunL() = 0;
};

class moo : baseTest
{
	private:

		int internalVal;

	public:
		moo(int val) : internalVal(val)
		{
		}

		void RunL();
};

#endif
