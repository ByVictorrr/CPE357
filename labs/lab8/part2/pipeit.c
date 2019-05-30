/*
 * pipeit.c
 * Copyright (C) 2019 victor <victor@TheShell>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#define INIT_SIZE 100

enum progSection{PROG1, PROG2};

void safe_fork(pid_t *pid)
{
	if((*pid = fork()) < 0){
		perror("fork err");
		exit(EXIT_FAILURE);
	}
}


void debug_progv(char **argv, int size)
{
	int i;
	printf("progv = {"); 
	for(i = 0; i < size; i++){
		printf("%s, ", argv[i]);
	}
	printf("}\n"); 

}

/*usage: pipeit <prog1 [options]> \; <prog2 [options]>*/ 

int main(int argc, char **argv)
{
	/*Step 1 - parse command line args*/
	int i, j, indicator; /*incator - tells if we what progv we are storing into*/
	char **progv1, **progv2;
	int argc_progv1 = 0, argc_progv2 = 0;

	int pipes[2], status;

	pid_t child1, child2;

	if(argc == 1){
		printf("usage: pipeit <prog1 [options]> \\; <prog2 [options]>\n");
		exit(0);
	}
	/*Malloc check*/
	if((progv1 = (char **)malloc(sizeof(char)*INIT_SIZE)) == NULL || (progv2 = (char **)malloc(sizeof(char)*INIT_SIZE)) == NULL ){
		perror("malloc erro");
		exit(EXIT_FAILURE);
	}

	for(indicator = PROG1, i = PROG1+1; argv[i] != NULL; i++){
		
		if(strcmp(argv[i], ";")  == 0) {
			indicator = PROG2;
			j = i+1;
		}else{ /*store argv into progv1*/
			if(indicator == PROG1){
				progv1[i-1] = argv[i];
				argc_progv1++;
			}else{
				progv2[i-j] = argv[i]; 
				argc_progv2++;
			}
		}
	}
	progv1[argc_progv1] = NULL;
	progv2[argc_progv2] = NULL;


	/*Step 2 - pipe(pipes) , then fork() two times, then exec*/
	pipe(pipes);
	
	safe_fork(&child1);

	if(child1 == 0){
		/*prog 1*/
		close(pipes[0]);
		dup2(pipes[1], STDOUT_FILENO);
		if(execv(progv1[0], progv1) < 0){
			perror(progv1[0]);
			exit(-1);
		}
		exit(0);
	}else{ /*parent*/
		wait(&status);
		if(WEXITSTATUS(status) !=0){
			printf("\nProcess %d exited with an error value\n", child1);
		}else{
			printf("\nProcess %d suceeded\n", child1);
		}	
	}
	
	safe_fork(&child2);

	if(child2 == 0){
		/*prog 2*/
		close(pipes[1]);
		dup2(pipes[0], STDIN_FILENO);
		if(execv(progv2[0], progv2)  < 0){
			perror(progv2[0]);
			exit(-1);
		}
		exit(0);
	}else{ /*parent*/
		wait(&status);
		if(WEXITSTATUS(status) !=0){
			printf("\nProcess %d exited with an error value\n", child1);
		}else{
			printf("\nProcess %d suceeded\n", child1);
		}	
	
	}
	free(progv1);
	free(progv2);
	
	exit(0);
}
