#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <regex.h>
#include <signal.h>
#include <unistd.h>
#include "readLongLine.h"
#define WORD_MAX 10
#define PROGV_MAX 10
#define PROGS_MAX 10

/*====================GLOBAL VARS===============================*/
int argc = 0;

/* ==================================================== */
/*================Debuggin fucntions=============== */
void handle_SEGFAULT(int signo){
	if(signo == SIGSEGV)
		exit(EXIT_FAILURE);
}
void print_progv(char **progv, int size){
	int i;
	char empty[PROGV_MAX] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
	for(i = 0; i< size; i++)
		if(strcmp(progv[i], empty) != 0)
			printf("progv[%d] = %s\n", i, progv[i]);
}

/* ================================================ */

/*=================SAFE FUNCTION==================== */
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

/*=================================================== */

/*==============Utility Functions====================*/
void init_word_buff(char **p, int word_size)
{
	if( (*p = (char *)malloc(sizeof(char)*word_size)) == NULL)
	{
		perror("malloc err");
		exit(EXIT_FAILURE);
	}
	memset(*p, '\0', word_size);
}
void init_progv_buff(char ***p, int progv_size, int word_size)
{
	int i;
	if( (*p = (char **)malloc(sizeof(char*)*progv_size)) == NULL)
	{
		perror("malloc err");
		exit(EXIT_FAILURE);
	}
	for(i = 0; i < progv_size; i++){
		init_word_buff(&p[0][i], word_size);
	}
}
void init_progs_buff(char ****p, int progs_size, int progv_size, int word_size)
{
	int i;
	if( (*p = (char ***)malloc(sizeof(char**)*progs_size)) == NULL)
	{
		perror("malloc err");
		exit(EXIT_FAILURE);
	}
	for(i = 0; i < progs_size; i++){
		init_progv_buff(&p[0][i], progv_size, word_size);
	}

}

void free_word_buff(char *ptr_word){
	if(ptr_word != NULL)
		free(ptr_word);
}

void free_progv_buff(char **ptr_progv, int size){
	int k;
	for(k = 0; k < size; k++){
		if(ptr_progv[k] != NULL)
			free_word_buff(ptr_progv[k]);
	}
	if(ptr_progv != NULL)
		free(ptr_progv);
}

void free_prog_buff(char ***prog, int progv_size, int progs_size){
	int k;
	for(k = 0; k < progs_size; k++){
		if(prog[k] != NULL)
			free_progv_buff(prog[k], progv_size);
	}
	if(prog != NULL)
		free(prog);
	
}

void clear_progv(char *** progv, int size)
{
	int i;
	for(i = 0; i< size; i++){
		memset(progv[0][i], '\0', size);
	}
}
void memset_progs(char ***progs_nth, char **progv, int size)
{
	int i;
	/* Step 1 - copy all the values to progv -> progs[ */
	for(i = 0; i< size; i++){
		strcpy(progs_nth[0][i], progv[i]);
	}
}

/*===================================================*/

/*==============Parsing functions=================== */
int count_pipes(char *line){

	int i;
	int num_pipes = 0;
	for( i = 0; line[i] != '\0'; i++){
		if(line[i] == '|')
			num_pipes++;
	}
	return num_pipes;
}

/*get_progs_with_options: gets a line inputed from user 
 *
 *returns: an array of strings
 *
 *programs are deperated by 
 * */ 


/*Treat > and < part of the the progn */
/*   */

/* TODO : account for | | isnt a valid comand */
char ***get_progs_with_options(char *line){

	char ***progs_buff, **progv_buff, *word_buff;
	int  word_ptr, progv_ptr, progs_ptr;
	int i;
	/* i - line ptr */

	/*Step 0 - initalize mem for all buffers */
	init_word_buff(&word_buff, WORD_MAX);
	init_progv_buff(&progv_buff, PROGV_MAX, WORD_MAX);
	init_progs_buff(&progs_buff, PROGS_MAX, PROGV_MAX, WORD_MAX);

	for( i = 0, word_ptr = 0, progv_ptr = 0, progs_ptr = 0; line[i] != '\0'; i++){
			/*Case 1- new word*/
			if(line[i] == ' ' && line[i+1] != '|' && word_buff[0] != '\0'){
				/*Step 1 - add this word to the progv*/
				strcpy(progv_buff[progv_ptr], word_buff);
				progv_ptr++;
				/*========reset word============= */
				memset(word_buff,'\0', WORD_MAX);
				word_ptr = 0;
				/*=============================== */
			/*Case 2 - new prog */
			}else if(line[i] == ' ' && line[i+1] == '|'){
				strcpy(progv_buff[progv_ptr], word_buff);
				print_progv(progv_buff, PROGV_MAX);
				/*memcpy(progs_buff[progs_ptr], progv_buff, PROGV_MAX);*/
				/*memset_progs(progv_buff[progs_ptr], progv_buff, PROGV_MAX);*/
				int f;
				for(f = 0; f< PROGV_MAX; f++){
					strcpy(progs_buff[progs_ptr][f], progv_buff[f]);
				}

				progs_buff[progs_ptr][progv_ptr+1] = NULL;
				progs_ptr++;
				/*=====reset word and progv =======*/
				memset(word_buff, '\0', WORD_MAX);
				clear_progv(&progv_buff, PROGV_MAX);
				argc += progv_ptr + 1;
				word_ptr = 0; /* new word  */
				progv_ptr = 0;
				/*=============================== */
			/*Case 3 - if prog1 [options]| prog2 [options]: exit not a valid input */
			}else if(line[i] != ' ' && line[i+1] == '|'){
				
				/* free everything  */
				printf("not a valid input");
				exit(EXIT_FAILURE);
			/*Case 3 - not a new program or word*/
			}else{
				
				if(line[i] == '|'){
					/* dont add it to the word */
					if(line[i+1] == ' ' && line[i+2] == '|'){ 
						printf("Not a valid command\n");
						/*free_everyThing(word_buff, progv_buff, progs_buff);*/
						exit(EXIT_FAILURE);
					}else{
						/* dont add anything in the buffer */
						printf("dont do anything");
					}
				}else if(line[i] == ' '){
					/* dont add anything in the buffer */
					printf("dont do anything");
				}else{
					word_buff[word_ptr] = line[i];
					word_ptr++;
				}
			}
	}/* for loop */
	/* store the last progv in to progs */
	if(word_buff[0] != '\0'){
		strcpy(progv_buff[progv_ptr], word_buff);
		print_progv(progv_buff, PROGV_MAX);
		/*memset_progs(&progv_buff[progs_ptr], progv_buff, PROGV_MAX);*/
		int f;
		for(f = 0; f< PROGV_MAX; f++){
			strcpy(progs_buff[progs_ptr][f], progv_buff[f]);
		}
		progs_buff[progs_ptr][progv_ptr+1] = NULL;
		argc += progv_ptr+1;
		progs_ptr++;
	}

	/*free_word_buff(word_buff);
	free_progv_buff(progv_buff, PROGV_MAX);
	*/

	return progs_buff;
}
/*======================================================================== */




/*====================Shell/Exec function============================= */

/*typedef int pipe_t [2];*/

void get_pipes(int num_pipes, int **(pipes)[2]){
	int i;
	if(num_pipes == 0){
		return NULL;
	}else{	
		if((*pipes = (int**)malloc(sizeof(int[2])*num_pipes)) == NULL){
			perror("malloc err");
			exit(EXIT_FAILURE);
		}
		for(i = 0; i<num_pipes; i++){
			safe_pipe(*pipes);
		}
	}
}



void close_uncess_pipes(int num_pipes, int ith_prog, int **(pipes)[2]){
	int i;
	int right, left;
	printf(" %d ", pipes);
	if(num_pipes  == 0)
		printf("no pipes therefore cant close any\n");

		/*Case 1 - not able to close any pipes to the left of ith_pipe*/
		if(!(ith_prog -2 < 0)){
			close(*pipes[ith_prog-2][0]);
			close(*pipes[ith_prog-2][1]);
			close_uncess_pipes(num_pipes, ith_prog-1, pipes);
		}
		/*Case 2 - not able to close any pipes to right of the ith_progs*/
		if(ith_prog + 1 < num_pipes){
			close(*pipes[ith_prog+1][0]);
			close(*pipes[ith_prog+1][1]);
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
	fdTest = open("inputs/test4", O_RDWR);
	line = read_long_line(fdTest);

	if(signal(SIGSEGV, handle_SEGFAULT) == SIG_ERR) {
	    fputs("An error occurred while setting a signal handler.\n", stderr);
		exit(EXIT_FAILURE);
	}

	progs=get_progs_with_options(line);
	/* assums that get_pros_with_options handles | next to a char and exits */
	num_pipes = count_pipes(line);
	
	printf("num pipes - %d\n", num_pipes);
	printf("argc - %d\n", argc);
	
	/*For test 1 - is good */
	/*For Test 2 - is good */
	/*For Test 3 - not getting -la  */
	
	/*==============Test 2 - exec command =====================*/
	pid_t child;
	int ptr_child = 0;
	int *(pipes)[2];
	int i, fd_std_out;
/*=========================Test 3 - close uncess pipes======================================*/
	get_pipes(num_pipes, &pipes);
	/*=============== Close =================*/
	printf(" %d ", pipes);
	close_uncess_pipes(num_pipes, 4, &pipes);
	printf(" %d ", pipes);
	
/*===========================================================================================*/
	return 0;
}
