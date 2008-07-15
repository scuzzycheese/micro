#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include "coroData.h"

#ifdef WIN32
	#include <windows.h>
#endif

jmp_buf tsk[3], mainTsk[3], mainTask;

struct CORO_STATE
{
	int state;
	void *resume;
};

int yielder()
{
	static int time = 0;

	if(time > 5)
	{
		time = 0;
		return 1;
	}
	time ++;
	return 0;
}

#define CORO_START static struct CORO_STATE pt = {0, NULL}; if(pt.resume) { printf("Resuming\r\n"); goto *pt.resume; }
#define CORO_YIELD { __label__ resume; resume: pt.resume = &&resume; } if(yielder()) return 0

int func1(int tskNo);
int func2(int tskNo);

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

void blah(int i)
{
	int count = 0;
	printf("Starting blah()\n");

	while(count < 6)
	{
		printf("looping in blah() routineId: %d count: %d\n", routineId, count);

		//This should be wrapped up in a yield
		routineRegs[routineId].jmpStatus = JMPFROMROUTINE;
		getExecAdd(routineRegs[routineId].retAdd, 0);
		if(routineRegs[routineId].jmpStatus == JMPFROMROUTINE)
		{
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

	routineRegs[0].jmpStatus = JMPFROMMAIN;
	routineRegs[0].callStatus = CALL;
	routineRegs[0].finished = 0;
	routineRegs[0].sheduled = 1;
	routineRegs[0].retAdd = blah;

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
				regSave(&routineRegs[routineId]);
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
	if(!setjmp(mainTask)) func1(0);
	if(!setjmp(mainTask)) func1(1);


	while(1)
	{
		//func1(0);
		//func1(1);
		printf("Main\n");
		if(!setjmp(mainTask)) longjmp(tsk[0], 1);
		if(!setjmp(mainTask)) longjmp(tsk[1], 1);
	}
}


int func1(int tn)
{
	char space[10000];
	space[9999] = 1;
	//CORO_START;
	int state = 0;
	int blah = 0;
	int tskNo = tn;
	printf("I should not get called when resuming: %d\n", tskNo);
	while(1)
	{

		if(!setjmp(tsk[tskNo])) longjmp(mainTask, 1);
		
		/*
		if(!setjmp(tsk[tskNo]))
		{
			CORO_YIELD;
			longjmp(tsk[tskNo], 0);
		}
		*/

		printf("hello from func1(%d): %d\r\n", tskNo, blah ++);
	}
}

int func2(int tskNo)
{
	CORO_START;
	int state = 0;
	int blah = 0;
	printf("I should not get called when resuming\r\n");
	while(1)
	{
		//if(!setjmp(childTask2))
		{
			CORO_YIELD;
			//longjmp(childTask2, 1);
		}

		char buffer[20];
		printf("hello from func2: %d\r\n", blah ++);
	}
}

