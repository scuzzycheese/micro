#include "testoo.h"

__volatile__ static coStData mainRegs;

//this has to get routineRegs dynamically
void fibre_yield(coStData *rt)
{
	SETBIT(rt->flags, JMPBIT); // = JMPFROMROUTINE
	getExecAdd(rt->retAdd);
	if(GETBIT(rt->flags, JMPBIT) == JMPFROMROUTINE)
	{
		//I think it's safer for the routine to save it's own registers and stack data
		//it means that it can self unschedule
		regSave(rt);
		jmpToAdd(mainRegs.retAdd);
	}
}

//this has to get routineRegs dynamically
void fibre_end(coStData *rt)
{
	SETBIT(rt->flags, FINISHED);
	//i think it's always safe to jump back
	jmpToAdd(mainRegs.retAdd);
}


//We can't execute the RunL method directly in the scheduler, as
//member function pointers are far more complex than just function
//pointers, and vary from compiler to compiler on size and complexity
void methodLauncher(coStData *rt)
{
	rt->obj->RunL(rt);
}


void fibre_create(__volatile__ coStData *regs, baseTest *obj, int stackSize, int *coRoSem)
{
	CLRBIT(regs->flags, JMPBIT); // = JMPFROMMAIN
	CLRBIT(regs->flags, CALLSTATUS); // = CALL
	CLRBIT(regs->flags, FINISHED);
	SETBIT(regs->flags, SHEDULED);

	//This is a wrapper system, so that we can launch objects safely
	//NOTE: this memeber doesn't really need to exist, 
	//it can just be called directly by the sheduler
	regs->retAdd = methodLauncher;
	
	//object related stuff
	regs->obj = obj;

	regs->mallocStack = (char *)malloc(stackSize);
	regs->SP = regs->mallocStack + (stackSize - 1);

	(*coRoSem) ++;
}

void fibres_start(coStData *routineRegs, int *coRoSem)
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
					routineRegs[routineId].SP -= sizeof(coStData *);
					*((coStData **)routineRegs[routineId].SP) = &(routineRegs[routineId]);

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


int main(int argc, char **argv)
{
	printf("Co-Routine storage size: %d\n", sizeof(coStData));

	coStData routineRegs[3];
	int crs = 0;

	moo myMoo(4);
	moo thisAo(10);

	//set up the fibres
	fibre_create(&(routineRegs[0]), (baseTest *)&myMoo, 10000, &crs);
	fibre_create(&(routineRegs[1]), (baseTest *)&myMoo, 10000, &crs);
	fibre_create(&(routineRegs[2]), (baseTest *)&thisAo, 10000, &crs);

	//start the fibres
	fibres_start(routineRegs, &crs);

	printf("Fibres finished\n");

	return 0;
}
