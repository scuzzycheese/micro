#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include "coroData.h"

#ifdef WIN32
	#include <windows.h>
#endif

jmp_buf tsk[3], mainTsk[3], mainTask;



//a simple method to determine the direction of the stack growth.
void stack_growth(char *function_parameter)
{
	char local;
	if(&local > function_parameter) printf("The stack grows up\n");
	else printf("The stack grows down\n");
}

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

void fibre_create(__volatile__ coStData *regs, fibreType rAdd, int stackSize)
{
	regs->jmpStatus = JMPFROMMAIN;
	regs->callStatus = CALL;
	regs->finished = 0;
	regs->sheduled = 1;
	regs->retAdd = rAdd;
	regs->mallocStack = malloc(stackSize);
	regs->SP = regs->mallocStack + (stackSize - 1);
}

//TODO:
//		The scheduler needs to be more dynamic (routineId) and more...
void fibres_start(__volatile__ coStData *rRegs)
{
	//This is a nasty hack, to make this work
	static __volatile__ coStData *routineRegs;
	routineRegs = rRegs;

	printf("blah: \t\t\t\t%X\n", blah);
	printf("routineRegs[0].retAdd: \t\t%X\n", routineRegs[routineId].retAdd);
	printf("routineRegs[0].mallocStack: \t%X\n", routineRegs[routineId].mallocStack);
	printf("routineRegs[0].SP: \t\t%X\n", routineRegs[routineId].SP);
	while(1)
	{
		for(routineId = 0; routineId < 2; routineId ++)
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
			printf("End loop\n");
		}
	}
}


int main(int argc, char **argv)
{

	char c = 'b';
	stack_growth(&c);
	
	//Because on an intel, our stack grows down, we need to place this pointer at the end of the allocated space
	//printf("NEW STACK SPACE ADDRESS: %X\n", newStackData);

	//This needs to be static otherwise we end up with an interesting problem
	//that we can't get back to this data once the stack has been changed (duh)

	printf("OFFSET: %d\n", OFFSET(coStData, ebx));

	//set up the fibres
	fibre_create(&(routineRegs[0]), blah, 1000);
	fibre_create(&(routineRegs[1]), blah, 1000);

	//start the fibres
	fibres_start(routineRegs);

	printf("finished stack manipulation\n");

	//free(newStackBegPointer[0]);
	//free(newStackBegPointer[1]);

	//stackPrint();
	
	printf("Finished calling stackPrint()\n");

	return 0;
}
