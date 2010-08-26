#include <stdio.h>
#include <stdlib.h>
#include "coroData.h"

__volatile__ static coStData mainRegs;

//this has to get routineRegs dynamically
void fibre_yield(coStData *rt) __attribute__((noinline));
void fibre_yield(coStData *rt)
{
	SETBIT(rt->flags, JMPBIT); // = JMPFROMROUTINE
	//rt->retAdd = &&FIBRET;
	__asm__("FIBRET:");
	if(GETBIT(rt->flags, JMPBIT))
	{
		//I think it's safer for the routine to save it's own registers and stack data
		//it means that it can self unschedule
		//regSave(rt);
		//jmpToAdd(mainRegs.retAdd);
		regSaveAndJumpToMain(rt);
	}
}

void blah(coStData *rt)
{
	int count = 0;
	#ifndef __AVR__
	printf("Starting blah()\n");
	#endif

	#ifndef __AVR__
	printf("blah() count: %d\n", count);
	#endif
	count ++;
	fibre_yield(rt);

	#ifndef __AVR__
	printf("blah() count: %d\n", count);
	#endif
	count ++;
	fibre_yield(rt);

	#ifndef __AVR__
	printf("blah() count: %d\n", count);
	#endif
	count ++;
	fibre_yield(rt);

	#ifndef __AVR__
	printf("blah() count: %d\n", count);
	#endif
}


void fibre_create(coStData *regs, fibreType rAdd, int stackSize, char *stackPointer)
{
	CLRBIT(regs->flags, JMPBIT); // = JMPFROMMAIN
	CLRBIT(regs->flags, CALLSTATUS); // = CALL
	CLRBIT(regs->flags, FINISHED);
	SETBIT(regs->flags, SHEDULED);

	regs->retAdd = rAdd;
	regs->mallocStack = stackPointer;
	regs->sp = regs->mallocStack + (stackSize - 1);

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

	regSave(&mainRegs);
	while(mainRegs.next != NULL)
	{
		CLRBIT(curCoRo->flags, JMPBIT); // = JMPFROMMAIN

		__asm__("MAINRET:");
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
				curCoRo->sp -= sizeof(coStData *);
				//I think this will always be on aligned data, but must double check, otherwise
				//it'll cause a bus error on some architechtures if it's not aligned
				*((coStData **)curCoRo->sp) = curCoRo;

				//This is designed to replace to two calls below
				setStackAndCallToAdd(curCoRo->sp, curCoRo->retAdd);
				//Put us back into the right stack frame
				regRestore(&mainRegs);
				//Believe if or not, if we get here, the routine is finished
				SETBIT(curCoRo->flags, FINISHED);
			}
			else
			{
				//This is designed to replace to two calls below
				regRestoreAndJmpToYeild(curCoRo);
			}
		}
		if(GETBIT(curCoRo->flags, FINISHED) && curCoRo->mallocStack)
		{
			if(curCoRo->prev->next == curCoRo->next)
			{
				mainRegs.next = NULL;
			}
			else
			{
				curCoRo->prev->next = curCoRo->next;
			}
		}
		curCoRo = curCoRo->next;
		//printf("End loop\n");
	}
}


int main(int argc, char **argv)
{
	#ifndef __AVR__
	printf("Co-Routine storage size: %d\n", sizeof(coStData));
	#endif

	coStData routineRegs[3];
	#ifndef __AVR__
	char stack[3][10000];
	#else
	char stack[3][100];
	#endif

	//set up the fibres
	#ifndef __AVR__
	fibre_create(&(routineRegs[0]), blah, 10000, stack[0]);
	fibre_create(&(routineRegs[1]), blah, 10000, stack[1]);
	fibre_create(&(routineRegs[2]), blah, 10000, stack[2]);
	#else
	fibre_create(&(routineRegs[0]), blah, 100, stack[0]);
	fibre_create(&(routineRegs[1]), blah, 100, stack[1]);
	fibre_create(&(routineRegs[2]), blah, 100, stack[2]);
	#endif

	//start the fibres
	fibres_start();

	#ifndef __AVR__
	printf("Fibres finished\n");
	#endif

	return 0;
}
