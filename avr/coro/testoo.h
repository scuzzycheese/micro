#ifndef TESTOOH
#define TESTOOH

#include <stdio.h>
#include <stdlib.h>
#include "coroDataOO.h"
#ifdef WIN32
	#include <windows.h>
#endif

void fibre_yield(coStData *rt);
void fibre_end(coStData *rt);
void fibre_create(__volatile__ coStData *regs, fibreType rAdd, int stackSize, int *coRoSem);
void fibres_start(coStData *routineRegs, int *coRoSem);

#endif
