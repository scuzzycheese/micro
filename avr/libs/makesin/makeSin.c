#include <math.h>
#include <stdio.h>


int main()
{


	double i;
	int counter = 0;
	int intCount = 1;
	

	int period = 256;
	float magic = period / (2 * 3.14159);

	for(i = 0; i < 256; i += 4)
	{
		printf("% 4d,", (int)((sin((i - (period / 4)) / magic) * (period / 2)) + (period / 2)));
		if(intCount >= 8)
		{
			intCount = 0;
			printf("\n");
		}
		intCount ++;
		counter ++;
	}

}
