#include "parseline.h"
#include "readLoneLine.h"

/*==================Safe Function ========================= */
void safe_pipe(int pipes[2])
{
	if(pipe(pipes) < 0){
		perror("pipe err");
		exit(EXIT_FAILURE);
	}
}
void safe_fork(pid_t *pid)
{
	if((*pid = fork()) < 0){
		perror("fork err");
		exit(EXIT_FAILURE);
	}
}
/*=================================================== */
/*====================Shell/Exec function============================= */

typedef int pipe_t [2];

void get_pipes(int num_pipes, pipe_t **pipes){
	int i;
	if(num_pipes == 0){
		return NULL;
	}else{	
		if((*pipes = (pipe_t*)malloc(sizeof(pipe_t)*num_pipes)) == NULL){
			perror("malloc err");
			exit(EXIT_FAILURE);
		}
		for(i = 0; i<num_pipes; i++){
			safe_pipe(*pipes);
		}
	}
}
void close_uncess_pipes(int num_pipes, int ith_prog, pipe_t **pipes){
	int i;
	int right, left;
	printf(" pipes[2][0] = %d ", pipes[0][2][0]);
	if(num_pipes  == 0)
		printf("no pipes therefore cant close any\n");

		/*Case 1 - not able to close any pipes to the left of ith_pipe*/
		if(!(ith_prog -2 < 0)){
			close(pipes[ith_prog-2][0]);
			close(pipes[ith_prog-2][1]);
			close_uncess_pipes(num_pipes, ith_prog-1, pipes);
		}
		/*Case 2 - not able to close any pipes to right of the ith_progs*/
		if(ith_prog + 1 < num_pipes){
			close(pipes[ith_prog+1][0]);
			close(pipes[ith_prog+1][1]);
			close_uncess_pipes(num_pipes, ith_prog+1, pipes);
		}/*cant close pipes */
}

/*======================================================================== */

int main()
{
	char ***progs;
	int fdTest;
	char *line;
	int num_pipes;

	/*============== Test 1 - parse comand line ===============*/
	fdTest = open("inputs/test5", O_RDWR);
	line = read_long_line(fdTest);

	/*  
	if(signal(SIGSEGV, handle_SEGFAULT) == SIG_ERR) {
	    fputs("An error occurred while setting a signal handler.\n", stderr);
		exit(EXIT_FAILURE);
	}
	*/

	progs=get_progs_with_options(line);
	/* assums that get_pros_with_options handles | next to a char and exits */
	num_pipes = count_pipes(line);
	
	printf("num pipes - %d\n", num_pipes);
	printf("argc - %d\n", argc);
	
	/*For test 1 - is good */
	/*For Test 2 - is good */
	/*For Test 3 - not getting -la  */
	/*===============Test 3 - stage testing ================= */
	 stage_t *stages = new_stages(progs, num_pipes+1);




	/*========================================================*/


	/*==============Test 2 - exec command =====================*/
	pid_t child;
	int ptr_child = 0;
	pipe_t *pipes;
	int i, fd_std_out;
/*=========================Test 3 - close uncess pipes======================================*/
	get_pipes(num_pipes, &pipes);
	/*=============== Close =================*/
	printf(" pipes[2][0] - %d ", pipes[2][0]);
	close_uncess_pipes(num_pipes, 4, pipes);
	/*printf(" %d ", pipes);*/
	
/*===========================================================================================*/
	return 0;
}



