/*
 * parseline.c
 * Copyright (C) 2019 victor <victor@localhost>
 *
 * Distributed under terms of the MIT license.
 */

#include "parseline.h"

void safe_malloc_2(char ***p)
{
	if( **p = (char **)malloc(sizeof(char)*size) == NULL)
	{
		perror("malloc err");
		exit(EXIT_FAILURE):
	}
}

void safe_malloc_1(char **p)
{
	if( *p = (char *)malloc(sizeof(char)*size) == NULL)
	{
		perror("malloc err");
		exit(EXIT_FAILURE):
	}
}



/*reads a line from user and returns the valid files*/ 
char *get_files_progs(char *line){
	char **files, *word_buff;
	int i,j;
	safe_malloc_2(&files);
	safe_malloc_1(&word_buff);


	for(i = 0, j=0; line[i] != '\0'; i++, j++){
		
		/*Step 1- Check to see if recorded word is a valid file/prog*/
		if(line[i] == ' ')
		{
			/*check word then decide to ad to files*/
			if(strcmp(word_buff, ">") != 0 || strcmp(word_buff, "<") != 0|| strcmp(word_buff, "|") !=0 ){
				/*Its a syntax of a file*/
				/*Step 2 - check if its a valid file/prog*/

			}
		}else{
			word_buff[j] =  line[i];
		}
	}
	





}

int main(int argc, char **argv)
{
	

}
