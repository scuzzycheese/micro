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

//this has to get routineRegs dynamically
void fibre::end()
{
	SETBIT(flags, FINISHED);
	//i think it's always safe to jump back
	jmpToAdd(mainRegs.retAdd);
}


void fibre::yield()
{
	SETBIT(flags, JMPBIT); // = JMPFROMROUTINE
	getExecAdd(retAdd);
	if(GETBIT(flags, JMPBIT) == JMPFROMROUTINE)
	{
		//I think it's safer for the routine to save it's own registers and stack data
		//it means that it can self unschedule
		regSave(this);
		jmpToAdd(mainRegs.retAdd);
	}
}

void fibre::start(fibre *routineRegs, int *coRoSem)
{
	int numOfRoutines = (*coRoSem);
	int routineId;

	//This is the sheduler, it needs lots of work
	//and carefully
	while((*coRoSem))
	{
		for(routineId = 0; routineId < numOfRoutines; routineId ++)
		{
			printf("Begin loop\n");
			CLRBIT(routineRegs[routineId].flags, JMPBIT); // = JMPFROMMAIN

			regSave(&mainRegs);
			getExecAdd(mainRegs.retAdd);
			regRestore(&mainRegs);

			//This might be a few too many checks
			if(GETBIT(routineRegs[routineId].flags, JMPBIT) == JMPFROMMAIN && !GETBIT(routineRegs[routineId].flags, FINISHED) && GETBIT(routineRegs[routineId].flags, SHEDULED))
			{
				if(GETBIT(routineRegs[routineId].flags, CALLSTATUS) == CALL)
				{
					//We should onyl get in here once per routine,
					//there after we jmp back, not call back
					SETBIT(routineRegs[routineId].flags, CALLSTATUS); // = JMP

					//copy a pointer to the specific routine's reg data structure
					//onto it's stack so it's passed in as an argument
					routineRegs[routineId].SP -= sizeof(fibre *);
					*((fibre **)routineRegs[routineId].SP) = &(routineRegs[routineId]);

					//This is designed to replace to two calls below
					setStackAndCallToAdd(routineRegs[routineId].SP, routineRegs[routineId].retAdd);
					/*
					//point the stack to the new data
					setStack(routineRegs[routineId].SP);

					//call our function
					callToAdd(routineRegs[routineId].retAdd);
					*/
				}
				else
				{
					//This is designed to replace to two calls below
					regRestoreAndJmpToAdd(&routineRegs[routineId]);
					/*
					regRestore(&routineRegs[routineId]);
					jmpToAdd(routineRegs[routineId].retAdd);
					*/
				}
			}
			if(GETBIT(routineRegs[routineId].flags, FINISHED) && routineRegs[routineId].mallocStack)
			{
				//now that our routine is finished, get rid of it's stack
				free(routineRegs[routineId].mallocStack);
				routineRegs[routineId].mallocStack = NULL;
				(*coRoSem) --;
			}
			printf("End loop\n");
		}
	}
}


