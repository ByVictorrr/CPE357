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
		/*printf("no pipes therefore cant close any\n");*/
 
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

	sigset_t old, new;
	pid_t child;
	int re_dir = -1;
	struct sigaction signalint;
	signalint.sa_handler = sig_handler_control_C;
	sigemptyset(&signalint.sa_mask);
	sigemptyset(&old);
    sigemptyset(&new);
	signalint.sa_flags=0;
	sigaction(SIGINT, &signalint, NULL);
	sigaddset(&new, SIGINT);
	/*base case   */
	if(num_progs == 0){
		return;
	}else{
		sigprocmask(SIG_BLOCK, &new, &old);
		safe_fork(&child);
		if(child == 0){
			sigprocmask(SIG_SETMASK, &old, NULL);
			close_uncess_pipes(num_pipes, num_progs-1, num_progs-1, 1, pipes);
			/*Case 1 - if the last program, leave stdout alone*/
			if(num_pipes + 1 == num_progs){
				printf("last program in pipeline\n");
				close(pipes[num_progs-2][WRITE]);
				/*See if any redirectino*/
				if((re_dir = redir(stages[num_progs-1], num_pipes, pipes[num_progs-2], pipes[num_progs-1], 1)) != -1){
					if(re_dir == 0){
						/*read from std in  */
						printf("reading from file");
					}else{
						/*read from std out  */
						printf("writing to file");
					}
				}else{
					dup2(pipes[num_progs-2][READ], STDIN_FILENO);
				}
						/*Case 2 - first program */
			}else if (num_progs == 1){
				close(pipes[num_progs-1][READ]);
				if((re_dir = redir(stages[num_progs-1], num_pipes, pipes[num_progs-2], pipes[num_progs-1], 1)) != -1){
					if(re_dir == 0){
						/*read from std in  */
						printf("reading from file");
					}else{
						/*read from std out  */
						printf("writing to file");
					}
				}
			dup2(pipes[num_progs-1][WRITE], STDOUT_FILENO);
			/*Case 3 - general case*/
			}else{		
				close(pipes[num_progs-1][READ]);
				close(pipes[num_progs-2][WRITE]);
				if((re_dir = redir(stages[num_progs-1], num_pipes, pipes[num_progs-2], pipes[num_progs-1], -1)) != -1){
					if(re_dir == 0){
						/*read from std in  */
						printf("reading from file");
						dup2(pipes[num_progs-1][WRITE], STDOUT_FILENO);

					}else{
						/*read from std out  */
						printf("writing to file");
						dup2(pipes[num_progs-2][READ], STDIN_FILENO);
					}
				}else{
					dup2(pipes[num_progs-1][WRITE], STDOUT_FILENO);
					dup2(pipes[num_progs-2][READ], STDIN_FILENO);
				}
				/*close end of pipes reading or righting to */
			}
		printf("redir = %d", re_dir);
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
	struct sigaction sig;
    sig.sa_handler = sig_handler_control_C;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sigaction(SIGINT, &sig, NULL);
    wait(NULL);
    printf("\n");

}


/*======================================================================== */

/*=========Redirection functions=========================================*/
/*Determien if a stage has redirection */
/*returns values: -1 - no redirection
 *				  1 - > rediection
 *				  0 - < redirection 
*/
int has_redirection(stage_t stage){

	/*Case 1 - stage has redirection*/
	if (stage.out_file[0] != '\0')
		return 1;
	else if (stage.in_file[0] != '\0')
		return 0;

	printf("stages.out_file_file = %d ", (int)stage.out_file[0]);

	return -1;
}

int safe_open(char *path, int modes){
	int fd;
	if((fd = open(path, modes)) < 0){
		perror("open err");
		exit(EXIT_FAILURE);
	}
	return fd;
}

/*If at any stage there is a redirection it stops the pipeline at first  */
/* use std_stream == 0 for stdin
 * use std_stream == 1 for stdout
 * use std_stream == -1 using pipes
 * */
int redir(stage_t stage, int num_pipes, pipe_t in, pipe_t out, int std_stream){
	int fd;
		/*Case 1 - out file redirection*/
		if (has_redirection(stage) == 1){
			fd = safe_open(stage.out_file, O_TRUNC | O_CREAT | O_RDWR);
			if(std_stream == -1){
				dup2(fd, out[WRITE]);
			}else{
				dup2(fd, STDOUT_FILENO);
			}
		}
			/*Case 2 - read from in file*/
		else if (has_redirection(stage) == 0){
			fd = safe_open(stage.in_file, O_RDONLY | O_CREAT);
			if(std_stream == -1){
				dup2(fd, in[READ]);
			}else{
				dup2(fd, STDIN_FILENO);
			}
		}

	return has_redirection(stage);
}
/*=========================================================================*/



/*TODO : fix parsing in parseline, frees, signals*/
int main(int argc, char **argv){

	char ***progs;
	char *line;
	int num_pipes;
	int script_fd;
	pipe_t pipes[PIPE_MAX];
	stage_t *stages;
	struct sigaction sa;
    sigset_t set, old;

	int i;

    sa.sa_handler = sig_handler_control_C;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigemptyset(&set);
    sigemptyset(&old);
    sigaddset(&set, SIGINT);

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
			/*Case 1 - num_pipes == 0 ; could be redirection*/
			get_pipes(pipes, num_pipes);
			pipe_line(stages, num_pipes+1, num_pipes, pipes);
			free(line);
			free(stages);
		}
	}
	/*===================================================*/
return 0;
}


