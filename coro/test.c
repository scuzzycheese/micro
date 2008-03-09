#include <stdio.h>

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

#define CORO_START static struct CORO_STATE pt = {0, NULL}; if(pt.resume) { printf("Resuming\n"); goto *pt.resume; }
#define CORO_YIELD { __label__ resume; resume: pt.resume = &&resume; } if(yielder()) return 0


int main()
{
	while(1)
	{
		func1();
		func2();
	}
}


int func1()
{
	CORO_START;
	int static state = 0;
	int static blah = 0;
	printf("I should not get called when resuming\n");
	while(1)
	{
		CORO_YIELD;
		printf("hello from func1: %d\n", blah ++);
		sleep(1);
	}
}

int func2()
{
	CORO_START;
	int static state = 0;
	int static blah = 0;
	printf("I should not get called when resuming\n");
	while(1)
	{
		CORO_YIELD;
		printf("hello from func2: %d\n", blah ++);
		sleep(1);
	}
}
