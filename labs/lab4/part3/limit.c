#include <unistd.h>
#include <limits.h>


int main()
{
	long maxs[] = {sysconf(CHILD_MAX), sysconf(OPEN_MAX), sysconf(PAGE_MAX)}

	while((n=write(sizeof(long),maxs, sizeof(long)) > 0 )
		;

return 0;
}
