#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
	printf("Hello, World!\n");

	pid_t child_pid = fork();
	if( child_pid == 0)
	{
		/*child*/
		printf("This is the child, pid %d\n", getpid());
	}else{
		/*parents8*/
		printf("This is the parent, pid %d\n", getpid());
		printf("This is the parent, pid %d, signing off\n", getpid());
	}

}
