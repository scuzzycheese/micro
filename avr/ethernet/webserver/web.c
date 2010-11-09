#include "web.h"
#include "uip.h"
#include <string.h>

#include <stdio.h>

#include "libhash/libhash.h"
#ifdef X86
#include "pages/index-x86.h"
#else
#include "pages/index.h"
#include "pages/404.h"
#include "uart.h"
#endif

#ifdef X86
char stacks[UIP_CONNS][100000] = { 0 };
#else
char stacks[UIP_CONNS][400] = { 0 };
#endif

hshObj fls;
coStData * volatile currentFibre = NULL;

void webAppFunc()
{
	//writeLn("webserver called\r\n");
	enum { NEW_CONNECTION, OLD_CONNECTION } conState;
	while(1)
	{
		//writeLn("entering while loop\r\n");
		if(uip_connected())
		{
			//writeLn("new connection to webserver!\r\n");
			conState = NEW_CONNECTION;
		}
		if(uip_newdata() && conState == NEW_CONNECTION)
		{
			//writeLn("new data detected\r\n");
			uint16_t len = uip_datalen();
			char *dataPtr = (char *)uip_appdata;
			//char *dataPtrBegin = dataPtr;

			if(strncmp(dataPtr, "GET ", 4) != 0)
			{
				conState = OLD_CONNECTION;
				uip_close();
				fibre_yield(currentFibre);
				goto ENDLOOP;
			}

			while(*dataPtr ++ != ISO_space);

			char filename[20] = { 0 };
			//There might be a better way to do this, I dunno
			char argumentData[100] = { 0 };
			struct argData args[5] = { 0 };

			pageFunc comm = NULL;

			if(dataPtr[1] == ISO_space)
			{
				strcpy(filename, "/index.html");
				dataPtr ++;
			}
			else
			{
				char *tmpPtr = filename;
				while(*(tmpPtr ++) = *(dataPtr ++))
				{
					if(*dataPtr == ISO_question || *dataPtr == ISO_space)
					{
						break;
					}
				}
				if(*dataPtr == ISO_question)
				{
					dataPtr ++;
					char *tmpPtr = argumentData;
					uint8_t counter = 0;
					while(counter < 5)
					{
						args[counter].argName = tmpPtr;
						while((*(tmpPtr ++) = *(dataPtr ++)) != ISO_equals);
						*(tmpPtr - 1) = 0x00;
						args[counter].argValue = tmpPtr;
						while(*dataPtr != ISO_amp && *dataPtr != ISO_space) *(tmpPtr ++) = *(dataPtr ++);
						*(tmpPtr ++) = 0x00;
						if(*dataPtr == ISO_space) break;
						dataPtr ++;
						counter ++;
					}
				}
			}


			comm = fls->findIndexString(fls, filename);
			if(comm)
			{
				fib_send("HTTP/1.0 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n", currentFibre);
				comm(args, currentFibre);
			}
			else
			{
				fib_send("HTTP/1.0 404 Not Found\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n", currentFibre);
				error404(args, currentFibre);
			}


			conState = OLD_CONNECTION;
			uip_close();
		}
		ENDLOOP:
		//writeLn("About to Yield\r\n");
		fibre_yield(currentFibre);
		//writeLn("return from yield\r\n");
	}
}


void preUIpInit()
{
	int c;
	for(c = 0; c < UIP_CONNS; ++c)
	{
		//NOTE: This is just a placeholder, there is lots to sort out.
#ifdef X86
		fibre_create(&(uip_conns[c].appstate), webAppFunc, 100000, stacks[c]);
#else
		fibre_create(&(uip_conns[c].appstate), webAppFunc, 400, stacks[c]);
#endif
	}
}

void web_init(void)
{
	fls = newHashObject();
	fls->addIndexString(fls, "/index.html", indexPage);

	uip_listen(HTONS(80));
}

void web_appcall(void)
{
	//writeLn("web_appcall\r\n");
	coStData *curCoRo = &(uip_conn->appstate);
	//There is a global indicator to keep track of the current fibre
	currentFibre = curCoRo;
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
	//writeLn("return to fibre_yield\r\n");
	if(GETBIT(rt->flags, JMPBIT))
	{
		//I think it's safer for the routine to save it's own registers and stack data
		//it means that it can self unschedule
		//regSave(rt);
		//jmpToAdd(mainRegs.retAdd);
		//writeLn("Jumping to main from fibre_yield\r\n");
		regSaveAndJumpToMain(rt);
	}
	//writeLn("gonna return to calling function from fibre_yield now\r\n");
}

void fibre_create(coStData *regs, fibreType rAdd, int stackSize, char *stackPointer)
{
	CLRBIT(regs->flags, JMPBIT); // = JMPFROMMAINw
	CLRBIT(regs->flags, CALLSTATUS); // = CALL
	CLRBIT(regs->flags, FINISHED);
	SETBIT(regs->flags, SHEDULED);

	regs->retAdd = rAdd;
	regs->mallocStack = stackPointer;
	regs->sp = regs->mallocStack + (stackSize - 1);
	//regs->sp = regs->mallocStack + (stackSize);
/*
#ifdef __AVR__
	*((coStData **)(regs->sp - sizeof(arg))) = arg;
	*((coStData **)(regs->sp - sizeof(arg) - sizeof(regs))) = regs;
	regs->sp -= 2;
#elif defined(X86)
	//Copy the arguments a user might want, onto the stack
	regs->sp -= sizeof(arg);
	*((coStData **)regs->sp) = arg;

	//copy a pointer to the specific routine's reg data structure
	//onto it's stack so it's passed in as an argument
	regs->sp -= sizeof(coStData *);
	//I think this will always be on aligned data, but must double check, otherwise
	//it'll cause a bus error on some architechtures if it's not aligned
	*((coStData **)regs->sp) = regs;
#endif
 */
}
