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

void blah(int i)
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
		getExecAdd(routineRegs[routineId].retAdd, 0);
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

int main(int argc, char **argv)
{

	char c = 'b';
	stack_growth(&c);
	
	//Allocate roughly 10k per thread
	void *newStackBegPointer[2]; 
	newStackBegPointer[0] = malloc(10000);
	newStackBegPointer[1] = malloc(10000);
	void *newStackData[2];
	newStackData[0] = newStackBegPointer[0] + 9999;
	newStackData[1] = newStackBegPointer[1] + 9999;

	//Because on an intel, our stack grows down, we need to place this pointer at the end of the allocated space
	printf("NEW STACK SPACE ADDRESS: %X\n", newStackData);

	//This needs to be static otherwise we end up with an interesting problem
	//that we can't get back to this data once the stack has been changed (duh)

	printf("OFFSET: %d\n", OFFSET(coStData, ebx));

	//set up the info required for routine 0
	routineRegs[0].jmpStatus = JMPFROMMAIN;
	routineRegs[0].callStatus = CALL;
	routineRegs[0].finished = 0;
	routineRegs[0].sheduled = 1;
	routineRegs[0].retAdd = blah;

	//set up the info required for routine 1
	routineRegs[1].jmpStatus = JMPFROMMAIN;
	routineRegs[1].callStatus = CALL;
	routineRegs[1].finished = 0;
	routineRegs[1].sheduled = 1;
	routineRegs[1].retAdd = blah;

	while(1)
	{
		for(routineId = 0; routineId < 2; routineId ++)
		{
			printf("Begin loop\n");
			regSave(&mainRegs);
			routineRegs[routineId].jmpStatus = JMPFROMMAIN;
			getExecAdd(mainRegs.retAdd, 1);
			//This might be a few too many checks
			if(routineRegs[routineId].jmpStatus == JMPFROMMAIN && !(routineRegs[routineId].finished) && routineRegs[routineId].sheduled)
			{
				if(routineRegs[routineId].callStatus == CALL)
				{
					//We should onyl get in here once per routine,
					//there after we jmp back, not call back
					routineRegs[routineId].callStatus = JMP;
					//point the stack to the new data
					setStack(newStackData[routineId]);
					//call our function
					callToAdd(routineRegs[routineId].retAdd);
				}
				else
				{
					regRestore(&routineRegs[routineId]);
					jmpToAdd(routineRegs[routineId].retAdd);
				}
			}
			else
			{
				//in theory, this should not be called, if the task is unsheduled or finished(tho finished doesn't really matter)
				//because it'll be saving the registers of another routine to it's own store, which is bad.
				//TODO: I have to figure out how to let a thread unshedule ittself, but stull get it to save it's
				//registers (this may require the thread always saving it's own registers)
				//UPDATE: I think it's better to let the routine handle the saving of it's registers and stack information
				//regSave(&routineRegs[routineId]);
			}
			regRestore(&mainRegs);
			printf("End loop\n");
		}
	}
		
	
	printf("finished stack manipulation\n");

	free(newStackBegPointer[0]);
	free(newStackBegPointer[1]);

	//stackPrint();
	
	printf("Finished calling stackPrint()\n");

	return 0;
}
