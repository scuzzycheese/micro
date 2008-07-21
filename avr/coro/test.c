#include <stdio.h>
#include <stdlib.h>
#include "coroData.h"

#ifdef WIN32
	#include <windows.h>
#endif


__volatile__ static coStData mainRegs;

//this has to get routineRegs dynamically
void fibre_yield(coStData *rt)
{
	rt->jmpStatus = JMPFROMROUTINE;
	getExecAdd(rt->retAdd);
	if(rt->jmpStatus == JMPFROMROUTINE)
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
	rt->finished = 1;
	//i think it's always safe to jump back
	jmpToAdd(mainRegs.retAdd);
}

void blah(coStData *rt)
{
	int count = 0;
	printf("Starting blah()\n");

	while(count < 6)
	{
		//for some reason, printf behaves strangely in windows when it has a new stack.
		//sounds like hackery jiggery going on underneith
		printf("looping in blah() count: %d\n", count);
		//flog(routineId);

		//Let this decide if I should yield or not
		fibre_yield(rt);

		count ++;
	}
	//if you don't put this on, it's all gonna be bad!
	fibre_end(rt);
}


void fibre_create(__volatile__ coStData *regs, fibreType rAdd, int stackSize, int *coRoSem)
{
	regs->jmpStatus = JMPFROMMAIN;
	regs->callStatus = CALL;
	regs->finished = 0;
	regs->sheduled = 1;
	regs->retAdd = rAdd;
	regs->mallocStack = malloc(stackSize);
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
			routineRegs[routineId].jmpStatus = JMPFROMMAIN;

			regSave(&mainRegs);
			getExecAdd(mainRegs.retAdd);
			regRestore(&mainRegs);

			//This might be a few too many checks
			if(routineRegs[routineId].jmpStatus == JMPFROMMAIN && !(routineRegs[routineId].finished) && routineRegs[routineId].sheduled)
			{
				if(routineRegs[routineId].callStatus == CALL)
				{
					//We should onyl get in here once per routine,
					//there after we jmp back, not call back
					routineRegs[routineId].callStatus = JMP;

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
			if(routineRegs[routineId].finished && routineRegs[routineId].mallocStack)
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

	coStData routineRegs[2];
	int crs = 0;

	//set up the fibres
	fibre_create(&(routineRegs[0]), blah, 10000, &crs);
	fibre_create(&(routineRegs[1]), blah, 10000, &crs);

	//start the fibres
	fibres_start(routineRegs, &crs);

	printf("Fibres both finished\n");

	return 0;
}
