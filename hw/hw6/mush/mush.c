#include "parseline.h"
#include "readLongLine.h"
#define PIPE_MAX PROGS_MAX - 1
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

void get_pipes(pipe_t *pipes, int size){
	int i; 
	if(size > PIPE_MAX){
		perror("to many pipes");
		exit(EXIT_FAILURE);
	}
	for(i=0; i< size; i++)
		safe_pipe(&pipes[i]);
}
void open_pipes(pipe_t *pipes, int size){
	int i; 
	if(size > PIPE_MAX){
		perror("to many pipes");
		exit(EXIT_FAILURE);
	}

}


void close_uncess_pipes(int num_pipes, int ith_prog, int org_ith, int left, pipe_t pipes[PIPE_MAX]){

	if(num_pipes  == 0)
		printf("no pipes therefore cant close any\n");
 
	/* Case 1 - not able to close any pipes to the left of ith_pipe*/
	if(ith_prog -2 >= 0 && left == 1){
		close(pipes[ith_prog-2][0]);
		close(pipes[ith_prog-2][1]);
		close_uncess_pipes(num_pipes, ith_prog-1, org_ith,1, pipes);
		if( org_ith != ith_prog)
			return;
		left = 0;
	}

	/* Case 2 - not able to close any pipes to right of the ith_progs*/
	if(ith_prog + 1 <= num_pipes-1 && left == 0){
		close(pipes[ith_prog+1][0]);
		close(pipes[ith_prog+1][1]);
		close_uncess_pipes(num_pipes, ith_prog+1, org_ith, 0, pipes);
	}/* cant close pipes */
}
/*num_progs = num_pipes+1*/
void pipe_line(stage_t *stages, int num_progs, int num_pipes, pipe_t pipes[PIPE_MAX]){

	pid_t child;
	/*base case   */
	if(num_progs == 0){
		return;
	}else{
		safe_fork(&child);
		if(child == 0){
			close_uncess_pipes(num_pipes, num_progs-1, num_progs-1, 1, pipes);
			/*Case 1 - if the last program, leave stdout alone*/
			if(num_pipes + 1 == num_progs){
				printf("last program in pipeline\n");
				close(pipes[num_progs-2][WRITE]);
				dup2(pipes[num_progs-2][READ], STDIN_FILENO);
			/*Case 2 - first program */
			}else if (num_progs == 1){
				close(pipes[num_progs-1][READ]);
				dup2(pipes[num_progs-1][WRITE], STDOUT_FILENO);
			/*Case 3 - general case*/
			}else{
				close(pipes[num_progs-1][READ]);
				close(pipes[num_progs-2][WRITE]);
				dup2(pipes[num_progs-1][WRITE], STDOUT_FILENO);
				dup2(pipes[num_progs-2][READ], STDIN_FILENO);
				/*close end of pipes reading or righting to */
			}
		if(execvpe(stages[num_progs-1].cmd_line[0], stages[num_progs-1].cmd_line, environ) < 0){
			perror("exec errr");
			exit(EXIT_FAILURE);
		}
		}else{
			pipe_line(stages, num_progs-1, num_pipes, pipes);
			/*close everything on the first program  */
			close_uncess_pipes(num_pipes, -1, -1 , 0,pipes);
			wait(NULL);
		}
	}
}
/*======================================================================== */

/*================SIGNAL stuff==========================================*/

void sig_handler_control_C(int signo){
	if(signo == SIGINT){

	}

}
void sig_handler_control_D(int signo){
	if(signo == SIGKILL){
	}
}


/*======================================================================== */

/*TODO : fix parsing in parseline, frees, signals*/
int main(int argc, char **argv){

	char ***progs;
	char *line;
	int num_pipes;
	int script_fd;
	pipe_t pipes[PIPE_MAX];
	stage_t *stages;

	/*Case 0 - see if the input is valid*/
	if(argc != 1 && argc != 2){
		perror("usage: mush [shell script]\n");
		exit(EXIT_FAILURE);
	}
	/*Case 1 - see if we have a script inputted  */
	if(argc == 2){
		if((script_fd = open(argv[1], O_RDONLY)) < 0){
			perror(argv[1]);
		}else{
			/*run shell scrpt */
			line = read_long_line(script_fd);
			progs=get_progs_with_options(line);
			num_pipes = count_pipes(line);
			stages = new_stages(progs, num_pipes+1);
			get_pipes(pipes, num_pipes);
			pipe_line(stages, num_pipes+1, num_pipes, pipes);
			free(line);
		}
	/*Case 2 - no script regular prompting */
	}else{
		/*  */
		while(1){
			printf("8-P: ");
			line = read_long_line(STDIN_FILENO);
			progs=get_progs_with_options(line);
			num_pipes = count_pipes(line);
			stages = new_stages(progs, num_pipes+1);
			get_pipes(pipes, num_pipes);
			pipe_line(stages, num_pipes+1, num_pipes, pipes);
			free(line);
			free(stages);
		}
	}
	/*===================================================*/
return 0;
}


