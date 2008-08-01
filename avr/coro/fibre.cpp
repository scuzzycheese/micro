#include "fibre.h"
#include "moo.h"

//We can't execute the RunL method directly in the scheduler, as
//member function pointers are far more complex than just function
//pointers, and vary from compiler to compiler on size and complexity
void fibre::methodLauncher(fibre *rt)
{
	rt->obj->RunL(rt);
}

void fibre::setup(baseTest *activeObj, int stackSize, int *coRoSem)
{
	CLRBIT(flags, JMPBIT); // = JMPFROMMAIN
	CLRBIT(flags, CALLSTATUS); // = CALL
	CLRBIT(flags, FINISHED);
	SETBIT(flags, SHEDULED);

	//This is a wrapper system, so that we can launch objects safely
	//NOTE: this memeber doesn't really need to exist, 
	//it can just be called directly by the sheduler
	retAdd = methodLauncher;
	
	//object related stuff
	obj = activeObj;

	mallocStack = (char *)malloc(stackSize);
	SP = mallocStack + (stackSize - 1);

	(*coRoSem) ++;
}
