#include <math.h>
#include "part3.h"

int sum(int arr[],int size)
{
	int sum = 0;
	int i;
	for (i = 0; i<size; ++i)
	   sum = arr[i] + sum;

	return sum;
}
