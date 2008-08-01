#ifndef TESTOOH
#define TESTOOH

#include <stdio.h>
#include <stdlib.h>
#include "fibre.h"
#ifdef WIN32
	#include <windows.h>
#endif

#include "moo.h"

void fibre_yield(fibre *rt);
void fibre_end(fibre *rt);
void fibre_create(__volatile__ fibre *regs, fibreType rAdd, int stackSize, int *coRoSem);
void fibres_start(fibre *routineRegs, int *coRoSem);

#endif
