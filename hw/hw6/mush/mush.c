#include "parseline.h"
#include "readLongLine.h"
#include <sys/types.h>
#include <sys/stat.h>
#define PIPE_MAX PROGS_MAX - 1
#define SCRIPT 1
#define INTERACTIVE 0

typedef int pipe_t [2];
enum Pipe_ends{READ, WRITE};
/*==================Globals var====================  */
pid_t child;
extern char **environ;
struct sigaction sa;
/*=================================================== */
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

/*================SIGNAL stuff==========================================*/

void sig_handler_control_C_kill_child(int signo){
	if(signo == SIGINT){
		kill(child, SIGTERM);
	}
}
void sig_handler_control_C_block(int signo){

		if(signo == SIGINT){
			printf("\n8-P: ");
		}
		sigaction(SIGINT, &sa, NULL);
}



/*======================================================================== */


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
		return;
 
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
void pipe_line(stage_t *stages, int num_progs, int num_pipes, pipe_t pipes[PIPE_MAX], struct sigaction *sa){

	struct sigaction new;

	sigemptyset(&new.sa_mask);
	sigaddset(SIGINT, &new.sa_mask);
	sigprocmask(SIG_SETMASK, &new.sa_mask, NULL);
	new.sa_handler = sig_handler_control_C_kill_child;

	int re_dir = -1;
	/*base case   */
	if(num_progs == 0){
		return;
	}else{
		safe_fork(&child);
		if(child == 0){
			close_uncess_pipes(num_pipes, num_progs-1, num_progs-1, 1, pipes);
			/*Case 1 - if the last program, leave stdout alone*/
			if(num_pipes + 1 == num_progs){	
				close(pipes[num_progs-2][WRITE]);
				/*See if any redirectino*/
				if((re_dir = redir(stages[num_progs-1], num_pipes, pipes[num_progs-2], pipes[num_progs-1], 1)) != -1){	
					if (re_dir == 2){
						
					}
					else if(re_dir == 0){
						/*read from std in  */
						
					}else{
						/*read from std out  */
						dup2(pipes[num_progs-2][READ], STDIN_FILENO);
					}
				}else{
					dup2(pipes[num_progs-2][READ], STDIN_FILENO);
				}
						/*Case 2 - first program */
			}else if (num_progs == 1){
				close(pipes[num_progs-1][READ]);
				if((re_dir = redir(stages[num_progs-1], num_pipes, pipes[num_progs-2], pipes[num_progs-1], 1)) != -1){
					/*Case 3.1 - double redirection*/
					if (re_dir == 2){	
						
					}
					/*Case 3.2 - < redirection */
					else if(re_dir == 0){
						/*read from std in  */	
						dup2(pipes[num_progs-1][WRITE], STDOUT_FILENO);
					/*Case 3.3 - > redirection  */
					}else{
						/*read from std out  */	
					}
				}else{
					dup2(pipes[num_progs-1][WRITE], STDOUT_FILENO);
				}
			/*Case 3 - general case*/
			}else{		
				close(pipes[num_progs-1][READ]);
				close(pipes[num_progs-2][WRITE]);
				if((re_dir = redir(stages[num_progs-1], num_pipes, pipes[num_progs-2], pipes[num_progs-1], 1)) != -1){
					/*case 3.1 - double redirection */
					if (re_dir == 2){
						
					}
					/*Case 3.2 - < redirection */
					else if(re_dir == 0){
						/*read from std in  */
						
						dup2(pipes[num_progs-1][WRITE], STDOUT_FILENO);
					/*Case 3.3 - > redirection  */
					}else{
						/*read from std out  */
						
						dup2(pipes[num_progs-2][READ], STDIN_FILENO);
					}
				}else{
					close(pipes[num_progs-1][READ]);
					close(pipes[num_progs-2][WRITE]);
					dup2(pipes[num_progs-1][WRITE], STDOUT_FILENO);
					dup2(pipes[num_progs-2][READ], STDIN_FILENO);
				}
				/*close end of pipes reading or righting to */
			}
		
		if(execvpe(stages[num_progs-1].cmd_line[0], stages[num_progs-1].cmd_line, environ) < 0){
			perror(stages[num_progs-1].cmd_line[0]);
			exit(EXIT_FAILURE);
		}
		}else{
			pipe_line(stages, num_progs-1, num_pipes, pipes, sa);
			/*set up handler */
			sigaction(SIGINT, &new, sa);


			/*close everything on the first program  */
			close_uncess_pipes(num_pipes, -1, -1 , 0,pipes);
			wait(NULL);
		}
	}
	/*restore signal action  */
	sigaction(SIGINT, sa, NULL);
}

/*==========================CD error checking============================================ */

/*Checks to see if cd is the first in the pipeline */
int is_cd_first(stage_t *stage_0, int size){
	if(stage_0 == NULL){
		perror("no stage 0");
		exit(EXIT_FAILURE);
	}
	if(strcmp(stage_0[0].cmd_line[0],"cd") == 0 && is_cd_in_pipe_line(stage_0, size))
			return 1;
	return 0;
}
/*checks to see if cd is in the stages  */
int is_cd_in_pipe_line(stage_t *stages, int size){
	int i;
	for(i = 0; i<size; i++){
		if(strcmp(stages[i].cmd_line[0],"cd") == 0)
				return 1;
	}
	return 0;
}
/*input double char pointer, and pass by reference output (single pointer)  */
void char_double_pointer_to_single_with_space(char **input, char *output){
	int i;
	if(input == NULL){
		perror("input double pointer is null");
		exit(EXIT_FAILURE);
	}
	for(i = 0; input[i] != NULL; i++)
	{
		if(i == 0){
			strcpy(output, input[0]);
		}else{
			strcat(output, " ");
			strcat(output, input[i]);
		}
	}
}
/*=========Redirection functions=========================================*/
/*Determien if a stage has redirection */
/*returns values: -1 - no redirection
 *				  1 - > rediection
 *				  2 - < > multiple redirection
 *				  0 - < redirection 
*/
int has_redirection(stage_t stage){

	/*Case 1 - stage has multiple redirection*/
	if(stage.out_file != NULL && stage.in_file != NULL)
		return 2;
	/*case 2 - stage has only out redirection  */
	else if(stage.out_file != NULL)
		return 1;
	/*Case 3 - stage has in redirection  */
	else if (stage.in_file != NULL)
		return 0;

	return -1;
}

int safe_open(char *path, int modes, int flags){
	int fd;
	if((fd = open(path, modes, flags)) < 0){
		perror("open err");
		exit(EXIT_FAILURE);
	}
	return fd;
}

/*If at any stage there is a redirection it stops the pipeline at first  */
/* use std_stream == 0 for stdin
 * use std_stream == 1 for stdout
 * use std_stream == -1 using pipes(read from the same pipe_i)
 * */
int redir(stage_t stage, int num_pipes, pipe_t in, pipe_t out, int std_stream){
	int in_fd;
	int out_fd;
		
		/*Case 1 - out file redirection*/
		if (has_redirection(stage) == 2){
			out_fd = safe_open(stage.out_file, O_TRUNC | O_CREAT | O_WRONLY, 0644);
			in_fd = safe_open(stage.in_file, O_RDONLY | O_CREAT, 0644);
			dup2(out_fd, STDOUT_FILENO);
			dup2(in_fd, STDIN_FILENO);
		}
		/*Case 2 - out file redirection*/
		else if(has_redirection(stage) == 1){
			out_fd = safe_open(stage.out_file, O_TRUNC | O_CREAT | O_WRONLY, 0644);
			dup2(out_fd, STDOUT_FILENO);
		}
		/*Case 2 - read from in file*/
		else if (has_redirection(stage) == 0){
			in_fd = safe_open(stage.in_file, O_RDONLY | O_CREAT, 0644);
			dup2(in_fd, STDIN_FILENO);
		}

	return has_redirection(stage);
}
/*=========================================================================*/




/*for script version for prompt version  */
void run_shell(FILE *stream, int script, struct sigaction *sa){
			stage_t *stages;
			char *line;
			char cd[WORD_MAX];
			int num_pipes;
			char ***progs;
			pipe_t pipes[PIPE_MAX];
			/*set up handler */
start:
		while(1){
			line = read_long_line(stream, script);
			num_pipes = count_pipes(line);
			/*Error check 1 - to many programs  */
			if(num_pipes >= PROGV_MAX){
				pipe_limit();
				free(line);
				/*script mode  */
				if(script == SCRIPT){
					return;
				}
				goto start; 
			}
			/*Error check 2 - to many arguments for one program  */
			if((progs=get_progs_with_options(line)) == NULL){
				free(line);
				/*script mode  */
				if(script == SCRIPT){
					return;
				}

				goto start;
			}
			/*Error check 3 - ambigous_output and bad_output and input */
			if((stages = new_stages(progs, num_pipes+1)) == NULL){
				free(line);
				free(progs);
				/*script mode  */
				if(script == SCRIPT){
					return;
				}
				goto start;
			}
			/*Case 1 - first program is cd */
			if(is_cd_first(stages, num_pipes+1)){
				chdir(stages[0].cmd_line[1]);
			}else{
				get_pipes(pipes, num_pipes);
				pipe_line(stages, num_pipes+1, num_pipes, pipes, sa);
			}
			/*frees  */
			free(line);
			free(stages);
			/*For script only run once */
			if(script == SCRIPT)
				break;
		}
}


/*TODO : fix parsing in parseline, frees, signals*/
int main(int argc, char **argv){

	FILE  *script;
	mode_t f_mask= 0000;
	umask(f_mask);
	/* signals */
	sigemptyset(&sa.sa_mask);
	sigaddset(SIGINT, &sa.sa_mask);
	sigprocmask(SIG_SETMASK, &sa.sa_mask, NULL);
	sa.sa_handler = sig_handler_control_C_block;
	sigaction(SIGINT, &sa, NULL);

	/*Case 0 - see if the input is valid*/
	if(argc != 1 && argc != 2){
		perror("usage: mush [shell script]\n");
		exit(EXIT_FAILURE);
	}
	/*Case 1 - see if we have a script inputted  */
	if(argc == 2){
		if((script = fopen(argv[1], O_RDONLY)) < 0){
			perror(argv[1]);
			exit(EXIT_FAILURE);
		}else{
			/*run shell scrpt */
			run_shell(script, SCRIPT, &sa);
		}
	/*Case 2 - no script regular prompting */
	}else{
		run_shell(stdin, INTERACTIVE, &sa);
	}
	/*===================================================*/
return 0;
}


