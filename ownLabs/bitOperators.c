#include <stdio.h>

typedef struct Thingy
{
	int a;
	char flags;
	Thingy;
};


int main()
{
	Thingy t;
	t.flags = 0;
	t.flags |=1;

	return 0;
}
