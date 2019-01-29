#include <stdio.h>

#include "checkit.h"
#include "part2.h"

void test_calc_1()
{
   checkit_double(calc(-1.0), 40);
}

void test_calc()
{
   test_calc_1();
}

int main(void)
{
   test_calc();

   return 0;
}
