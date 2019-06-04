/*
 * stage.c
 * Copyright (C) 2019 victor <victor@TheShell>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define CMD_LINE_MAX  10

enum boolean{FALSE, TRUE};

typedef struct stage{
	/*command options files */
	char **cmd_line;
	char *in_file;
	char *out_files;
	int num_args; /*counts the number of string in cmd_line  */
	boolean pipe_flag; /*set if there is a pipe to the right*/
}stage_t;



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





/*Takes in a progs and creates a size num of stage */
stage_t *new_stages(char ***progs, int size) 
{
	int i,k;
	stage_t *stages;

	if((stages = (stage_t*)malloc(sizeof(stage_t)*size)) == NULL){
		perror("malloc err");
		exit(EXIT_FAILURE);
	}
	/*Step 1 - (mallocing)setting up all members of stages */
	for(i = 0; i< size; i++){
		if(progs[i] != NULL){
			/*=================Setting up ============================  */
			init_progv_buff(&stages[i]->cmd_line, CMD_LINE_MAX, WORD_MAX);
			init_word_buff(&stages[i]->in_file, WORD_MAX);
			init_word_buff(&stages[i]->out_files, WORD_MAX);
			stages[i]->num_args = 0;
			pipe_flag = FALSE;
			/*========================================================= */
			/*=============Parse Prog[i] -> stages[i]================== */
			/*only when i = size -1 when the stage will have pipe_flag == FALSE*/
			parse_progv(progs[i], stages[i]);
		}
	}
	return stages;
}


void parse_progv(char **progv, stage_t *stage){
	int i;
	int cmd_line_ptr;
	for (i=0, cmd_line_ptr = 0; progv != NULL; i++){
		/*Case 1 - just seperate cmd_line string */
		if(strcmp(progv[i], "<") != 0 || strcmp(progv[i], ">") != 0){
			stage->cmd_line[cmd_line_ptr] = progv[i];
			num_args++;
		/*Case 2 - currently at a < or >*/
		}else{
			/*Case 2.1 - at a < */
			if(strcmp(progv[i], "<") == 0 ){
				stage->in_file = progv[i+1];
				i++;
			/*Case 2.2 - at a >  */
			}else{
				stage->out_file = progv[i+1];
				i++;
			}
			
		}
	}

}
#define PROGS 10
#define PROGV 10
int main(int argc, char **argv)
{
	char progs[PROGS][PROGV][WORD_MAX];

	return 0;
}
