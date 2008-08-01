#include "testoo.h"

__volatile__ static fibre mainRegs;

//this has to get routineRegs dynamically
void fibre_yield(fibre *rt)
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
void fibre_end(fibre *rt)
{
	SETBIT(rt->flags, FINISHED);
	//i think it's always safe to jump back
	jmpToAdd(mainRegs.retAdd);
}

void fibres_start(fibre *routineRegs, int *coRoSem)
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


int main(int argc, char **argv)
{
	printf("Co-Routine storage size: %d\n", sizeof(fibre));

	//fibre routineRegs[3];

	moo myMoo(4);
	moo thisAo(10);

	int crs = 0;
	fibre fibres[3];
	fibres[0].setup((baseTest *)&myMoo, 1000, &crs);
	fibres[1].setup((baseTest *)&myMoo, 1000, &crs);
	fibres[2].setup((baseTest *)&thisAo, 1000, &crs);


	//start the fibres
	fibres_start(fibres, &crs);

	printf("Fibres finished\n");

	return 0;
}
