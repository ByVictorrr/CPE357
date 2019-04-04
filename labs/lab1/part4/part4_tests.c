#include <stdio.h>

#include "checkit.h"
#include "part4.h"
#define SIZE1 5
#define SIZE2 3
#define SIZE3 3


void test_strLower_1()
{
	char lowered[SIZE1];
	char input[SIZE1] = "APPLE";

	strLower(input, lowered);
	checkit_string(lowered,"apple");
}


void test_strLower_2()
{
	char lowered[SIZE2];
	char input[SIZE2] = {'V','I','C'};

	strLower(input, lowered);
	checkit_string(lowered,"vic");
}

void test_strLower_3()
{
	char lowered[SIZE3];
	char input[SIZE3] = "CpE";

	strLower(input, lowered);
	checkit_string(lowered,"cpe");
}
void test_strLower()
{
   test_strLower_1(); 
   test_strLower_2();
   test_strLower_3();
}

int main(void)
{
   test_strLower();

   return 0;
}
