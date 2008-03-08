#include <stdio.h>

struct PTSTATE
{
	int state;
	void *resume;
};

int main()
{
	while(1)
	{
		func1();
		func2();
	}
}

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

int func1()
{
	static struct PTSTATE pt = {0, NULL};
	int static state = 0;
	int static blah = 0;
	if(pt.resume)
	{
		printf("trying to resume function 1\n");
		goto *pt.resume;
	}
	printf("I should not get called when resuming\n");
	while(1)
	{
		{
			__label__ resume;
			resume: pt.resume = &&resume;
		}
		if(yielder()) return 0;
		printf("hello from func1: %d\n", blah ++);
		sleep(1);
	}
}

int func2()
{
	static struct PTSTATE pt = {0, NULL};
	int static state = 0;
	int static blah = 0;
	if(pt.resume)
	{
		printf("trying to resume function 2\n");
		goto *pt.resume;
	}
	printf("I should not get called when resuming\n");
	while(1)
	{
		{
			__label__ resume;
			resume: pt.resume = &&resume;
		}
		if(yielder()) return 0;
		printf("hello from func2: %d\n", blah ++);
		sleep(1);
	}
}
