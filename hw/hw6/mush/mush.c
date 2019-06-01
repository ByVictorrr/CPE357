#include "parseline.h"
#include "readLongLine.h"
typedef int pipe_t [2];
enum Pipe_ends{READ, WRITE};

extern char **environ;
/*==================Safe Function ========================= */
void safe_pipe(pipe_t *pipes){
	if(pipe(*pipes) < 0){
		perror("pipe err");
		exit(EXIT_FAILURE);
	}
}
void safe_fork(pid_t *pid){
	if((*pid = fork()) < 0){
		perror("fork err");
		exit(EXIT_FAILURE);
	}
}

void clear_pipe_buff(int fd_read){
	char c;
	while(read(fd_read, &c, sizeof(c)) > 0){
		printf("%c", c);
	}
}

/*=================================================== */
/*====================Shell/Exec function============================= */

/*======================================================================== */

int main()
{
	char ***progs;
	int fdTest;
	char *line;
	int num_pipes;

	/*============== Test 1 - parse comand line ===============*/
	fdTest = open("inputs/test3", O_RDWR);
	line = read_long_line(fdTest);

	progs=get_progs_with_options(line);
	/* assums that get_pros_with_options handles | next to a char and exits */
	num_pipes = count_pipes(line);
	
	printf("num pipes - %d\n", num_pipes);
	
	/*For test 1 - is good */
	/*For Test 2 - is good */
	/*For Test 3 - not getting -la  */
	
	/*==============Test 2 - exec command =====================*/
	pid_t child;
	int ptr_child = 0;
	pipe_t pipes[2];
	int i, fd_std_out;
	stage_t *stages = new_stages(progs, num_pipes+1);
	safe_pipe(pipes[0]);
	safe_pipe(pipes[1]);

	/*
	printf("environ\n: - ");
	while(environ[i]) {
		  printf("%s\n", environ[i++]); 
	}
	*/

	if(num_pipes > 0){
		for(i = 0; i < num_pipes+1; i++){
				
			if((child = fork()) < 0){
				perror("bad fork");
				exit(EXIT_FAILURE);
			}else if(child == 0){
				printf("i = %d\n", i);
				/*if the very first process */
				if (i == 0){
					close(STDOUT_FILENO);
					close(pipes[1][0]);
					close(pipes[1][1]);
					close(pipes[0][READ]);
					dup(pipes[0][WRITE]);
					close(pipes[0][WRITE]);

					execvpe(stages[i].cmd_line[0], stages[i].cmd_line, environ);
					exit(EXIT_FAILURE);
				/* general case */
				}else{
					/* last program  */
					if(i == num_pipes){
						close(STDIN_FILENO);
						close(pipes[1][0]);
						close(pipes[1][1]);
						/*return saved stdout to its process */
						close(pipes[0][WRITE]);
						dup(pipes[0][READ]);
						close(pipes[0][READ]);
					}else{
						/*Read from last process */
						close(pipes[0][WRITE]);
						dup2(pipes[0][READ], STDIN_FILENO);
						/*Write to the the next process */
						close(pipes[1][READ]);
						dup2(pipes[1][WRITE], STDOUT_FILENO);
					}				
					execvpe(stages[i].cmd_line[0], stages[i].cmd_line, environ);
					exit(EXIT_FAILURE);
				}
			}else{
				if(i==0){
					close(pipes[0][0]);
					close(pipes[0][1]);
					close(pipes[1][0]);
					close(pipes[1][1]);
				}
				wait(NULL);
				safe_pipe(pipes[0]);
				safe_pipe(pipes[1]);

			}
		}/* for loop */
		printf("hi");
	}
	return 0;
}


