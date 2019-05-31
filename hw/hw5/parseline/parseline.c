#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#include "read_long_line.h"
#define WORD_MAX 1000
#define PROGV_MAX 1000
#define PROGS_MAX 1000



/*==============Utility Functions====================*/
void safe_malloc_3(char ****p, int size)
{
	if( ***p = (char ***)malloc(sizeof(char)*size) == NULL)
	{
		perror("malloc err");
		exit(EXIT_FAILURE):
	}
}

void safe_malloc_2(char ***p, int size)
{
	if( **p = (char **)malloc(sizeof(char)*size) == NULL)
	{
		perror("malloc err");
		exit(EXIT_FAILURE):
	}
}

void safe_malloc_1(char **p, int size)
{
	if( *p = (char *)malloc(sizeof(char)*size) == NULL)
	{
		perror("malloc err");
		exit(EXIT_FAILURE):
	}
}
/*===================================================*/




/*get_progs_with_options: gets a line inputed from user 
 *
 *returns: an array of strings
 *
 *programs are deperated by 
 * */ 


/*Treat > and < part of the the progn */
/*   */
char ***get_progs_with_options(char *line){
	char ***progs_buff, **progv_buff, *word_buff;
	int i, word_ptr, progv_ptr, progs_ptr;
	/* i - line ptr */

	/*Step 0 - initalize mem for all buffers */
	safe_malloc_1(&word_buff, WORD_MAX);
	safe_malloc_2(&progv_buff, PROGV_MAX);
	safe_malloc_3(&progs_buff, PROGS_MAX);


	for( i = 0, word_ptr = 0, progv_ptr = 0, progs_ptr = 0; line[i] != '\0'; i++){
			/*Case 1- new word*/
			if(line[i] == ' ' && line[i+1] != '|'){
				/*Step 1 - add this word to the progv*/
				strcpy(progv[progv_ptr], word_buff);
				progv_buff++;
				/*========reset word============= */
				memset(word_ptr,'\0', WORD_MAX);
				word_ptr = 0;
				/*=============================== */
			/*Case 2 - new prog */
			}else if(line[i] == ' ' && line[i+1] == '|'){
				strcpy(progs_buff[progs_ptr], progv_buff);
				progs_ptr++;
				/*=====reset word and progv =======*/
				memset(word_buff, '\0', WORD_MAX);
				memset(progv_buff, NULL, PROGV_MAX);
				word_ptr = 0; /* new word  */
				progv_ptr = 0;
				/*=============================== */
			/*Case 3 - not a new program or word*/
			}else{
				word_buff[word_ptr] = line[i];
				word_ptr++;
			}
	}
}

int main(int argc, char **argv)
{
	char ***progs;
	char *line = read_long_line(STDIN_FILENO);

	progs=get_progs_with_options(line);


}
