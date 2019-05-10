#include <unistd.h>
#include <limits.h>
#include <stdio.h>

int main()
{
	
	printf("sysconf(CHILD_MAX) = %d\n",sysconf(_SC_CHILD_MAX));
	
	printf("sysconf(OPEN_MAX) = %d\n",sysconf(_SC_OPEN_MAX));
	printf("sysconf(PAGE_SIZE) = %d\n",sysconf(_SC_PAGE_SIZE));

	return 0;
}

