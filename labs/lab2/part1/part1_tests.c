#include <stdio.h>
#include "swap.h"
#include "checkit.h"


void test_swap()
{
	int int1  = 8;
	int int2 = 9;

	swap(&int1,&int2);
	checkit_int(int1, 9);
	checkit_int(int2, 8);
}
void test_all()
{
   test_swap();
}

int main(void)
{
   test_all();

   return 0;
}
