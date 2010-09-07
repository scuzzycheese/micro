#include "web3.h"
#include "uip.h"
#include <string.h>

#include <stdio.h>
#include "pages/index.h"
#include "libhash/libhash.h"

char stacks[UIP_CONNS][10000];

void webAppFunc(coStData *regs, void *blah)
{
	while(1)
	{
		if(uip_connected())
		{
			fib_send("Welcome\n", regs);
		}
		if(uip_newdata())
		{
			fib_send("ok\n", regs);
		}
		fibre_yield(regs);
	}
}

void preUIpInit()
{
	int c;
	for(c = 0; c < UIP_CONNS; ++c)
	{
		//NOTE: This is just a placeholder, there is lots to sort out.
		fibre_create(&(uip_conns[c].appstate), webAppFunc, 1000, stacks[c], 0);
	}
}

void web_init(void)
{
	uip_listen(HTONS(80));
}

void web_appcall(void)
{
	coStData *curCoRo = &(uip_conn->appstate);
	regSave(&mainRegs);

	CLRBIT(curCoRo->flags, JMPBIT); // = JMPFROMMAIN
	__asm__("MAINRET:");
	regRestore(&mainRegs);

	if(GETBIT(curCoRo->flags, JMPBIT) == JMPFROMMAIN && !GETBIT(curCoRo->flags, FINISHED) && GETBIT(curCoRo->flags, SHEDULED))
	{
		if(GETBIT(curCoRo->flags, CALLSTATUS) == CALL)
		{
			//We should onyl get in here once per routine,
			//there after we jmp back, not call back
			SETBIT(curCoRo->flags, CALLSTATUS); // = JMP

			//This is designed to replace to two calls below
			setStackAndCallToAdd(curCoRo->sp, curCoRo->retAdd);
			//Put us back into the right stack frame
			regRestore(&mainRegs);
			//Believe if or not, if we get here, the routine is finished
			//SETBIT(curCoRo->flags, FINISHED);
		}
		else
		{
			//This is designed to replace to two calls below
			regRestoreAndJmpToYeild(curCoRo);
		}
	}



}




//this has to get routineRegs dynamically
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

void fibre_create(coStData *regs, fibreType rAdd, int stackSize, char *stackPointer, void *arg)
{
	CLRBIT(regs->flags, JMPBIT); // = JMPFROMMAINw
	CLRBIT(regs->flags, CALLSTATUS); // = CALL
	CLRBIT(regs->flags, FINISHED);
	SETBIT(regs->flags, SHEDULED);

	regs->retAdd = rAdd;
	regs->mallocStack = stackPointer;
	regs->sp = regs->mallocStack + (stackSize - 1);


	//Copy the arguments a user might want, onto the stack
	regs->sp -= sizeof(arg);
	*((coStData **)regs->sp) = arg;

	//copy a pointer to the specific routine's reg data structure
	//onto it's stack so it's passed in as an argument
	regs->sp -= sizeof(coStData *);
	//I think this will always be on aligned data, but must double check, otherwise
	//it'll cause a bus error on some architechtures if it's not aligned
	*((coStData **)regs->sp) = regs;
}