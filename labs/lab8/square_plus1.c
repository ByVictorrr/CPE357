#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


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

	safe_pipe(pipes1);
	safe_pipe(pipes2);
	safe_pipe(pipes3);

	while ((c = getch())!= EOF){
	/*Step 1 - fork 1st  children*/
	safe_fork(child1);
	/*Step 1.1 - child1 */
	if(child1 == 0){
		/*step 2.1 - close stdin and stdout*/
		dup2(pipes1[1], 0); /*parent -> child1*/
		close(STDOUT_FILENO);
		close(STDIN_FILENO);
		/*step 2.2 - */


	}else{ /*parent*/
		/*Step 1.1 - save stdin to fd_in_parent*/
		fd_in_parent = dup(0);
		/*step 1.2 - close stdout of parent */
		close(STDOUT_FILENO);
		/*Step 1.3 - pipes1[0] = in, pipes1[1] = out*/
		safe_pipe(pipes1);
		/*step 1.4 - write to child 1*/
		write(pipes1[1], &c, sizeof(c));
		/*step 1.4 - wait until child 1 recieves write*/
		waitpid(child1, NULL, 0);
	}
	/*step 2 - fork the 2nd child*/
	safe_fork(child2);
	/*Step 1.2 - child2*/
	if(child2 == 0){

	}else{
		/*parent*/
	}
	
	
	}
	exit(0);
}
