#include <stdio.h>
#include <stdlib.h>
#include "coroData.h"

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

void blah(coStData *rt)
{
	int count = 0;
	printf("Starting blah()\n");

	while(count < 4)
	{
		//for some reason, printf behaves strangely in windows when it has a new stack.
		//sounds like hackery jiggery going on underneith
		printf("looping in blah() count: %d\n", count);
		//flog(routineId);

		//Let this decide if I should yield or not
		fibre_yield(rt);

		count ++;
	}
}


void fibre_create(coStData *regs, fibreType rAdd, int stackSize)
{
	CLRBIT(regs->flags, JMPBIT); // = JMPFROMMAIN
	CLRBIT(regs->flags, CALLSTATUS); // = CALL
	CLRBIT(regs->flags, FINISHED);
	SETBIT(regs->flags, SHEDULED);

	regs->retAdd = rAdd;
	regs->mallocStack = (char *)malloc(stackSize);
	regs->SP = regs->mallocStack + (stackSize - 1);

	if(mainRegs.next == NULL)
	{
		mainRegs.next = regs;
		mainRegs.last = regs;
		regs->next = regs;
		regs->prev = regs;
	}
	else
	{
		mainRegs.last->next = regs;
		regs->prev = mainRegs.last;
		mainRegs.last = regs;
		regs->next = mainRegs.next;

		mainRegs.next->prev = mainRegs.last;
	}
}

void fibres_start()
{
	coStData *curCoRo = mainRegs.next;

	//This is the sheduler, it needs lots of work
	//and carefully
	while(mainRegs.next != NULL)
	{
		printf("Begin loop\n");
		CLRBIT(curCoRo->flags, JMPBIT); // = JMPFROMMAIN

		//TODO: check this out
		//I might be able to move this out the while loop, as any changes
		//to the registers up to this point are inconsiquential
		regSave(&mainRegs);
		getExecAdd(mainRegs.retAdd);
		regRestore(&mainRegs);

		//This might be a few too many checks
		if(GETBIT(curCoRo->flags, JMPBIT) == JMPFROMMAIN && !GETBIT(curCoRo->flags, FINISHED) && GETBIT(curCoRo->flags, SHEDULED))
		{
			if(GETBIT(curCoRo->flags, CALLSTATUS) == CALL)
			{
				//We should onyl get in here once per routine,
				//there after we jmp back, not call back
				SETBIT(curCoRo->flags, CALLSTATUS); // = JMP

				//copy a pointer to the specific routine's reg data structure
				//onto it's stack so it's passed in as an argument
				curCoRo->SP -= sizeof(coStData *);
				//I think this will always be on aligned data, but must double check, otherwise
				//it'll cause a bus error on some architechtures if it's not aligned
				*((coStData **)curCoRo->SP) = curCoRo;

				//This is designed to replace to two calls below
				setStackAndCallToAdd(curCoRo->SP, curCoRo->retAdd);
				//Put us back into the right stack frame
				regRestore(&mainRegs);
				//Believe if or not, if we get here, the routine is finished
				SETBIT(curCoRo->flags, FINISHED);
			}
			else
			{
				//This is designed to replace to two calls below
				regRestoreAndJmpToAdd(curCoRo);
			}
		}
		if(GETBIT(curCoRo->flags, FINISHED) && curCoRo->mallocStack)
		{
			//now that our routine is finished, get rid of it's stack
			free(curCoRo->mallocStack);
			curCoRo->mallocStack = NULL;
			if(curCoRo->prev->next = curCoRo->next)
			{
				mainRegs.next = NULL;
			}
			else
			{
				curCoRo->prev->next = curCoRo->next;
			}
		}
		curCoRo = curCoRo->next;
		printf("End loop\n");
	}
}


int main(int argc, char **argv)
{
	printf("Co-Routine storage size: %d\n", sizeof(coStData));

	coStData routineRegs[3];

	//set up the fibres
	fibre_create(&(routineRegs[0]), blah, 10000);
	fibre_create(&(routineRegs[1]), blah, 10000);
	fibre_create(&(routineRegs[2]), blah, 10000);

	//start the fibres
	fibres_start();

	printf("Fibres finished\n");

	return 0;
}
