/*
 * timeout.c
 * Copyright (C) 2019 victor <victor@TheShell>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <wait.h>

#define INIT_MAX 100

void safe_fork(pid_t *pid)
{
	if((*pid = fork()) < 0){
		perror("fork err");
		exit(EXIT_FAILURE);
	}
}



void sig_handler(int signo)
{
	if (signo == SIGALRM){
		printf("killing child process\n");
		exit(0);
	}
	
}


/*usage: timout <integer of seconds>  <prog[options]>*/
int main(int argc, char **argv)
{
	pid_t child;
	struct itimerval tv;
	struct sigaction sa;
	char **prog;
	int status,i;
	
	/*Step 0 - validity check*/
	if(argc < 3){
		printf("usage: timout <integer of seconds>  <prog[options]>");
		exit(EXIT_FAILURE);
	}
	
	if((prog = (char **)malloc(sizeof(char)*INIT_MAX)) == NULL){
		perror("malloc err");
		exit(EXIT_FAILURE);
	}
	

	/*Step 1 - parse from argv[2] -> argv[n];*/
	for(i = 0; i< argc-2; i++){
		prog[i] = argv[2+i];
	}
	tv.it_value.tv_sec = atoi(argv[1]);
	tv.it_value.tv_usec = 0;
	tv.it_interval.tv_sec = 0;
	tv.it_interval.tv_usec = 0;
	sa.sa_handler = sig_handler;
	

	/*step 2- set timer for child process*/
	if(sigaction(SIGALRM, &sa, NULL) < 0){
		perror("sigaction err");
		exit(EXIT_FAILURE);
	}
	if(setitimer(ITIMER_REAL, &tv, NULL) < 0){
		perror("setitimer err");
		exit(EXIT_FAILURE);
	}

	safe_fork(&child);
	
	if(child == 0){
		if(execv(prog[0], prog) < 0){
			perror("exec err");
			exit(EXIT_FAILURE);
		}
	}else{
		wait(&status);
		if( WEXITSTATUS(status) !=0){
			printf("Process %d exited with an error value\n", child);
		}
		else{
			kill(child, SIGKILL);
			printf("child sent a kill\n");
			exit(EXIT_FAILURE);
		}

	}


	return 0;
}
