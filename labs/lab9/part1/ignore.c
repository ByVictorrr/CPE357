/*
 * ignore.c
 * Copyright (C) 2019 victor <victor@TheShell>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#define MAX_LINE 5000



void sig_handler(int signo)
{
	if (signo == SIGINT){
		printf("type quit to exit the program\n");
	}
	
}


int main(int argc, char **argv)
{
	char line[MAX_LINE];
	int i = 0, c, pending;
	struct sigaction sa;
	
	sa.sa_handler = sig_handler;
	/*Step 2 - emtpy the new_mask*/
	/*
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);

	if(sigprocmask(SIG_BLOCK, &sa.sa_mask, NULL) < 0){
		perror("sigprocmaskeerr");
		exit(EXIT_FAILURE);
	}
*/

	/*Step 1 - set the signal to do the action in handler*/
	if(sigaction(SIGINT, &sa, NULL) < 0){
		perror("siaction err");
		exit(EXIT_FAILURE);
	}

	memset(line, '\0', MAX_LINE);
	/*Step 2 - go through lines until ^C is taken*/
	while(strcmp(line, "quit") != 0){
		
		if((c = getchar()) != EOF){
			if((line[i] = c) == '\n'){
				memset(line, '\0', MAX_LINE);
				i=0;
			}else{
				i++;
			}	
		}

	}
	return 0;
}
