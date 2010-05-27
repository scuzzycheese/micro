#include <math.h>
#include <stdio.h>


int main()
{


	double i;
	int counter = 0;
	int intCount = 1;
	for(i = 0; i < 6.28318; i += 0.024543672)
	{
		printf("% 4d,", (int)((sin(i + 4.6) * 128) + 128));
		if(intCount > 20)
		{
			intCount = 0;
			printf("\n");
		}
		intCount ++;
		counter ++;
	}

}
