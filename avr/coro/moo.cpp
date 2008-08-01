#include "moo.h"
using namespace std;
void moo::RunL(fibre *rt)
{
	int count = 0;
	cout << "Starting RunL()" << endl;

	while(count < 20)
	{
		//for some reason, printf behaves strangely in windows when it has a new stack.
		//sounds like hackery jiggery going on underneith
		cout << "looping in RunL() count: " << count << ", internalVal: " << internalVal << endl;
		//flog(routineId);

		//Let this decide if I should yield or not
		if(count % 2) fibre_yield(rt);

		count ++;
	}
	//if you don't put this on, it's all gonna be bad!

	fibre_end(rt);
}
