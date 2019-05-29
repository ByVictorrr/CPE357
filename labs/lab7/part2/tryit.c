#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


int main(int argc, char *argv[])
{
	pid_t pid;
	int status;
	if(argc <= 1 ){
		printf("usage: tryit command\n");
		exit(EXIT_FAILURE);
	}
	if((pid = fork()) < 0){
			perror("fork err");
			exit(EXIT_FAILURE);
	}else if(pid == 0){ /*child*/
		if(execl(argv[1],argv[1], (char *)0)  < 0){
			perror(argv[1]);	
			exit(-1);
		}
	}else{ /*parent*/
		wait(&status);
		if(WIFEXITED(status) && WEXITSTATUS(status) !=0){
			printf("Process %d exited with an error value\n", pid);
		}
		else{
			printf("Process %d suceeded\n", pid);
		}

	}
	exit(0);
}
