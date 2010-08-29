#include <stdio.h>
#include <stdlib.h>
#include "fibre.h"

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
