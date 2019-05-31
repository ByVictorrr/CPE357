#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void safe_fork(pid_t *pid)
{
	if((*pid = fork()) < 0){
		perror("fork err");
		exit(EXIT_FAILURE);
	}
}

void safe_pipe(int pipes[2])
{
	if(pipe(pipes) < 0){
		perror("pipe err");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv)
{

	int c, pipes1[2], pipes2[2], pipes3[3];
	pid_t child1, child2;
	int fd_in_parent;
	int i;

	/*Step 1- initalize all the pipes*/
	safe_pipe(pipes1);
	safe_pipe(pipes2);
	safe_pipe(pipes3);

	/*Step 2 - get input for P*/
	for(i = 0; (c = getchar()) != EOF ; i++){
		c = atoi(&c);
	/*Step 3 - fork 1st  children*/
		safe_fork(&child1);

/*=================CHILD 1=============================*/
	if(child1 == 0){
		/*step 2.1 - wait for a write status from the parent*/
		waitpid(getppid(), NULL, 0);
		close(pipes1[1]);
		printf("child1: reading %d from parent\n", c);
		read(pipes1[0], &c, sizeof(c));

		/*Step 2.2 - now write to the other child c2 */
		close(pipes2[0]);
		write(pipes2[1], &c, sizeof(c));
		printf("child1: writing %d to child2\n", c);
		exit(0);
/*====================================================*/
	}else{ /*parent*/
		/*Step 1.2 - close read side*/
		close(pipes1[0]);
		/*step 1.4 - write to child 1*/
		printf("parent: writing %d to child1\n", c);
		write(pipes1[1], &c, sizeof(c));
		/*step 1.4 - wait until child 1 recieves write*/
		waitpid(child1, NULL, 0);
	}

/*=======================================================*/
	/*step 2 - fork the 2nd child*/
	safe_fork(&child2);
	/*Step 1.2 - child2*/
	if(child2 == 0){
		/*Step 3.1 - read from child 1*/
		close(pipes2[1]);
		printf("child2: reading %d from child1\n", c);
		read(pipes2[0], &c, sizeof(c));

		/*Step 3.2 - write to the parent  */
		close(pipes3[0]);
		printf("child2: writing %d to parent\n", c);
		write(pipes3[1], &c, sizeof(c));
		exit(0);
	}else{
		/*parent*/
		close(pipes3[1]);
		waitpid(child2, NULL, 0);
		printf("parent: reading %d from child2\n", c);
		read(pipes3[0], &c, sizeof(c));
		/*restore the fd_in_parent - so we can read from getch() */
	}
	
	printf("%d - loop %d\n", c, i);
}/*while loop*/

	return 0;
}


