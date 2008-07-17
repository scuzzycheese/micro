#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include "coroData.h"

#ifdef WIN32
	#include <windows.h>
#endif


__volatile__ static coStData mainRegs;
__volatile__ static coStData routineRegs[2];
static int routineId;

int flog(int id)
{
	printf("HI FROM FLOG: %d\n", id);
	return id;
}

void blah()
{
	int count = 0;
	printf("Starting blah()\n");

	while(count < 6)
	{
		//for some reason, printf behaves strangely in windows when it has a new stack.
		//sounds like hackery jiggery going on underneith
		printf("looping in blah() routineId: %d count: %d\n", routineId, count);
		flog(routineId);

		//This should be wrapped up in a yield
		routineRegs[routineId].jmpStatus = JMPFROMROUTINE;
		getExecAdd(routineRegs[routineId].retAdd);
		if(routineRegs[routineId].jmpStatus == JMPFROMROUTINE)
		{
			//I think it's safer for the routine to save it's own registers and stack data
			//it means that it can self unschedule
			regSave(&routineRegs[routineId]);
			jmpToAdd(mainRegs.retAdd);
		}

#ifdef WIN32
		Sleep(1000);
#else
		sleep(1);
#endif
		count ++;
	}
	
	//This stuff needs to be wrapped in a macro
	//we are finished.
	routineRegs[routineId].finished = 1;
	//i think it's always safe to jump back
	jmpToAdd(mainRegs.retAdd);
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

//TODO:
//		The scheduler needs to be more dynamic (routineId) and more...
void fibres_start(__volatile__ coStData *rRegs, int *coRoSem)
{
	//This is a nasty hack, to make sure that nothing
	//we access is on a stack (which we can't get to)
	static __volatile__ coStData *routineRegs;
	routineRegs = rRegs;

	int numOfRoutines = (*coRoSem);

	//This is the sheduler, it needs lots of work
	//and carefully
	while((*coRoSem))
	{
		for(routineId = 0; routineId < numOfRoutines; routineId ++)
		{
			printf("Begin loop\n");
			regSave(&mainRegs);
			routineRegs[routineId].jmpStatus = JMPFROMMAIN;
			getExecAdd(mainRegs.retAdd);
			//This might be a few too many checks
			if(routineRegs[routineId].jmpStatus == JMPFROMMAIN && !(routineRegs[routineId].finished) && routineRegs[routineId].sheduled)
			{
				if(routineRegs[routineId].callStatus == CALL)
				{
					//We should onyl get in here once per routine,
					//there after we jmp back, not call back
					routineRegs[routineId].callStatus = JMP;
					//point the stack to the new data
					setStack(routineRegs[routineId].SP);
					//call our function
					callToAdd(routineRegs[routineId].retAdd);
				}
				else
				{
					regRestore(&routineRegs[routineId]);
					jmpToAdd(routineRegs[routineId].retAdd);
				}
			}
			regRestore(&mainRegs);
			if(routineRegs[routineId].finished)
			{
				//now that our routine is finished, get rid of it's stack
				free(routineRegs[routineId].mallocStack);
				(*coRoSem) --;
			}
			printf("End loop\n");
		}
	}
}


int main(int argc, char **argv)
{

	int crs = 0;
	//set up the fibres
	fibre_create(&(routineRegs[0]), blah, 1000, &crs);
	fibre_create(&(routineRegs[1]), blah, 1000, &crs);

	//start the fibres
	fibres_start(routineRegs, &crs);

	printf("Fibres both finished\n");

	return 0;
}
