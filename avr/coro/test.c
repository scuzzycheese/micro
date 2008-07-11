#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
#include <setjmp.h>


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

void blah()
{
	printf("hello from blah()\n");
}

int main(int argc, char **argv)
{

	char c = 'b';
	stack_growth(&c);

	//Allocate roughly 10k
	void *newStackBegPointer = malloc(10000);
	void *newStackData = newStackBegPointer + 9999;
	//Because on an intel, our stack grows down, we need to place this pointer at the end of the allocated space
	printf("NEW STACK SPACE ADDRESS: %X\n", newStackData);

	static int stackData[20];
	//Save our registers!
	__asm__
	(
		"movl %%ebx, (%%eax)\n" 
		"movl %%esi, (4)(%%eax)\n"
		"movl %%edi, (8)(%%eax)\n"
		"movl %%esp, (12)(%%eax)\n"
		"movl %%ecx, (16)(%%eax)\n"
		"movl %%ebp, (20)(%%eax)\n"
		
		:
		:"a"(stackData)
	);
	printf("ESP OUTER: %X\n", stackData[3]);
	printf("EBP OUTER: %X\n", stackData[5]);
	int ESP = stackData[3];
	int EBP = stackData[5];


	//Set out stack to point to the allocated space, see if it works
	__asm__
	(
		"movl %%eax, %%ebp\n"
		"movl %%eax, %%esp\n"
		
		:
		:"a"(newStackData)
	);
	blah();
	//Restore our stack pointers
	__asm__
	(
		//"movl (%%eax), %%ebx\n"
		//"movl (4)(%%eax), %%esi\n"
		//"movl (8)(%%eax), %%edi\n"
		"movl (12)(%%eax), %%esp\n"
		"movl (16)(%%eax), %%ecx\n"
		"movl (20)(%%eax), %%ebp\n"
		
		:
		:"a"(stackData)
	);


	printf("finished stack manipulation\n");
	
	stackPrint();
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

