#include "moo.h"

void moo::RunL(coStData *rt)
{
	int count = 0;
	printf("Starting RunL()\n");

	while(count < 4)
	{
		//for some reason, printf behaves strangely in windows when it has a new stack.
		//sounds like hackery jiggery going on underneith
		printf("looping in RunL() count: %d\n", count);
		//flog(routineId);

		//Let this decide if I should yield or not
		fibre_yield(rt);

		count ++;
	}
	//if you don't put this on, it's all gonna be bad!

	fibre_end(rt);
}
