#include "testoo.h"
#include "fibre.h"
#include "moo.h"

int main(int argc, char **argv)
{
	printf("Co-Routine storage size: %d\n", sizeof(fibre));

	//fibre routineRegs[3];

	moo myMoo(4);
	moo thisAo(10);

	int crs = 0;
	fibre fibres[3];
	fibres[0].setup((baseTest *)&myMoo, 1000, &crs);
	fibres[1].setup((baseTest *)&myMoo, 1000, &crs);
	fibres[2].setup((baseTest *)&thisAo, 1000, &crs);


	//start the fibres
	fibre::start(fibres, &crs);

	printf("Fibres finished\n");

	return 0;
}
