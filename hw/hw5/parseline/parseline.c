#include "readLongLine.h"
#include "parseline.h"
#include <stdint.h>
#include <stdio.h>

/* ==================================================== */
/*================Debuggin fucntions=============== */
void handle_SEGFAULT(int signo){
	if(signo == SIGSEGV)
		exit(EXIT_FAILURE);
}

/* ================================================ */

/*=================SAFE FUNCTION==================== */
/*takes in a process to be assigned a fork if successful*/
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
/* mallocs a buffer the sice of word_size passed in pointing to p*/
void init_word_buff(char **p, int word_size)
{
	if( (*p = (char *)malloc(sizeof(char)*word_size)) == NULL)
	{
		perror("malloc err");
		exit(EXIT_FAILURE);
	}
	memset(*p, '\0', word_size);
}

/* takes in a triple pointer of "programs" that will be malloced and have their word buffer initalized   */
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

/*   */
void init_progs_buff(char ****p, int progs_size, int progv_size, int word_size){
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

void clear_progv(char *** progv, int size){
	int i;
	for(i = 0; i< size; i++){
		memset(progv[0][i], '\0', size);
	}
}
void memset_progs(char ***progs_nth, char **progv, int size){
	int i;
	/* Step 1 - copy all the values to progv -> progs[ */
	for(i = 0; i< size; i++){
		strcpy(progs_nth[0][i], progv[i]);
	}
}

/*===================================================*/

/*==============Parsing functions=================== */


void parse_progv(char **progv, stage_t *stage)
{

	int cmd_line_ptr;
	for (cmd_line_ptr = 0; progv[cmd_line_ptr] != NULL; cmd_line_ptr++)
	{
		strcpy(stage->cmd_line[cmd_line_ptr],progv[cmd_line_ptr]);
	}
	stage->cmd_line[cmd_line_ptr] = NULL;
}
/*Takes in a progs and creates a size num of stage */
stage_t *new_stages(char ***progs, int size)
{
	int i, k;
	stage_t *stages;

	if ((stages = (stage_t *)malloc(sizeof(stage_t) * size)) == NULL)
	{
		free(stages);
		perror("malloc err");
		exit(EXIT_FAILURE);
	}
	/*Step 1 - (mallocing)setting up all members of stages */
	for (i = 0; i < size; i++)
	{
		if (progs[i] != NULL)
		{
			/*=================Setting up ============================  */
			init_progv_buff(&stages[i].cmd_line, PROGV_MAX, WORD_MAX);
			init_word_buff(&stages[i].in_file, WORD_MAX);
			init_word_buff(&stages[i].out_file, WORD_MAX);
			stages[i].num_args = 0;
			if(i < size -1){
				stages[i].pipe_flag = 1;
			}
			else{
				
				stages[i].pipe_flag = 0;
			}
			
			/*stages[i].in_file = NULL;
			stages[i].out_file = NULL;*/
			/*========================================================= */
			/*=============Set Up cmd_line - End with NULL ptr=================*/
			/*only when i = size -1 when the stage will have pipe_flag == FALSE*/
			parse_progv(progs[i], &stages[i]);
			/*============CHECK REDIRECTION < >  EXIT if error=================*/
			
			/*============update in, out, num_args================== */
			if (!redirect_is_valid(&stages[i]))
			{
				exit(1);
			}
		}
	}
	return stages;
}


int redirect_is_valid(stage_t* stage)
{
	int argc = 0, i = 0, skip = 0;
	/*pass in {"executable", "[flag|<|>|file|"} */
	/*check if the redirection is valid
    if valid: return TRUE 
    if not: print input| output redirect error message and return FALSE
    */
	char str[WORD_MAX] = {'\0'};
	char next[WORD_MAX] = {'\0'};
	int o = 0, in = 0; /* test if there is redundant redirection sign*/
	

	while (stage->cmd_line[i])
	{
		strncpy(str, stage->cmd_line[i], WORD_MAX);
		if(stage->cmd_line[i+1]){
			strncpy(next, stage->cmd_line[i+1], WORD_MAX);
		}
		else{
			*next = '\0';
		}
		

		/*else if (strcmp(str, ">"))*/
		if(!strcmp(str, ">"))
		{
			/*printf(" this is a > ");*/
			if (!next || !*next)
			{
				return FALSE;
				/* if > is the last arg - ERROR*/
			}
			/*if two redirect signs stack together* - ERROR*/
			if (*next == '>' || *next == '<')
			{
				return FALSE;
			}
			/*----- update Stage's outfile -------*/
			strncpy(stage->out_file, next, strlen(next));
			skip = 1;
			o += 1;
		}
		else if(!strcmp(str, "<"))
		{
			/*printf(" this is a < ");*/
			if (!*next || !next)
			{
				return FALSE;
				/* if > is the last arg - ERROR*/
			}
			/*if two redirect signs stack together* - ERROR*/
			if (*next == '>' || *next == '<')
			{
				return FALSE;
			}
			/*----- update Stage's infile -------*/
			strncpy(stage->in_file, next, strlen(next));
			skip = 1;
			in += 1;
		}
		else if(skip!= 1)
		{
		
			argc += 1;
			skip = 0;
		}
		i++;
	}
	/*since we cant have two outfile*/
	if (in > 1)
	{
		bad_input(stage->cmd_line[0]);
		return FALSE;
	}
	if (o > 1)
	{
		bad_output(stage->cmd_line[0]);
		return FALSE;
	}
	stage->num_args = argc;
	return TRUE;
}


void print_stage(stage_t *stages, int size)
{
	/* takes list of stage entities and size of the list and a cmd line in one line not a list*/
	int i, j = 0, skip = 0;
	char *cmd_full, *arg_line, *stin, *stout;

/*
	char cmd_full[WORD_MAX] = {'\0'};
	char arg_line[WORD_MAX] = {'\0'};*/
	if (stages == NULL)
	{
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < size; i++)
	{   
		init_word_buff(&stin, WORD_MAX+10);
		init_word_buff(&stout, WORD_MAX+10);
		init_word_buff(&cmd_full, WORD_MAX);
		init_word_buff(&arg_line, WORD_MAX);
		/* getting the full command and arguments only 
		by parsing through and filtering out < > in/out file*/
		/*======= retrive stdin =====*/ 
		if (*stages[i].in_file){
			if(i>0){
				ambiguous_input(stages[i].cmd_line[0]);
				exit(1);
			}
			sprintf(stin, "%s\n", stages[i].in_file);
		}
		else if (!*stages[i].in_file && i > 0){
			sprintf(stin, "pipe from stage %i\n", i - 1);}

		else{
			sprintf(stin, "original stdin\n");}
		/*======= retrive stdout =====*/ 
		if (*stages[i].out_file){
			/*if there is outfile and also pipe after --> error*/
			if(stages[i].pipe_flag){
				ambiguous_output(stages[i].cmd_line[0]);
				exit(1);
			}
			/*if there is an outfile*/
			sprintf(stout, "%s\n", stages[i].out_file);}
		else if (!*stages[i].out_file && stages[i].pipe_flag){
			/*if there is a pipe afterwards and no outfile*/
			sprintf(stout, "pipe to stage %i\n", i + 1);}
		else {
			sprintf(stout, "original stdout\n");}
		/*========save arg and cmd line into a buffer =======*/
		while(stages[i].cmd_line[j] && *stages[i].cmd_line[j]){
			if (skip){
				skip = 0;
			}
			else if(*stages[i].cmd_line[j] =='>'|| *stages[i].cmd_line[j] == '<'){
				skip = 1;
			}	
			else{
				sprintf(&arg_line[strlen(arg_line)], "\"%s\",", stages[i].cmd_line[j]);
				/*strcat(arg_line+strlen(arg_line, " ");*/
			}/*else */
			
			if(strlen(cmd_full) > CMD_LINE_MAX){
				many_arg(stages[i].cmd_line[0]);
				exit(1);
			}			
			sprintf(&cmd_full[strlen(cmd_full)], "%s ", stages[i].cmd_line[j]);	
			j++;
		}	/*for loop*/

		arg_line[strlen(arg_line)-1] = '\0'; /*take off the comma */
		cmd_full[strlen(cmd_full)-1] = '\0';
		printf("\n--------\n");
		printf("Stage %d: \"%s\"\n", i, cmd_full);
		printf("--------\n");
		printf("%10s: %s", "input", stin);


		printf("%10s: %s", "output", stout);
		

		
		printf("%10s: %d\n", "argc", stages[i].num_args);
		printf("%10s: %s\n", "argv", arg_line);
		/*
		memset(cmd_full, '\0',WORD_MAX*sizeof(char)); 
		memset(arg_line, '\0',WORD_MAX*sizeof(char));
		*/
		free(cmd_full);
		free(arg_line);
		free(stin);
		free(stout);
		/*==== free each stages==*/
		free(stages[i].in_file);
		free(stages[i].out_file);
		free_progv_buff(stages[i].cmd_line, PROGV_MAX);
		j = 0;
	}
}

/*=========================================================*/


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
	int i, argc;
	/* i - line ptr */
	int prog_argc, pipe_argc;
	/*Step 0 - initalize mem for all buffers */
	init_word_buff(&word_buff, WORD_MAX);
	init_progv_buff(&progv_buff, PROGV_MAX, WORD_MAX);
	init_progs_buff(&progs_buff, PROGS_MAX, PROGV_MAX, WORD_MAX);
	for(i = 0, word_ptr = 0, progv_ptr = 0, progs_ptr = 0; line[i] != '\0'; i++){
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
				if(i < WORD_MAX-3 && line[i+3] == '|'){
					empty_stage();
				}
				strcpy(progv_buff[progv_ptr], word_buff);
				int f;
				for(f = 0; f< PROGV_MAX; f++){
					strcpy(progs_buff[progs_ptr][f], progv_buff[f]);
				}

				progs_buff[progs_ptr][progv_ptr+1] = NULL;
				/*ATTENTION: make char* buff[][] null will cause memory lost */
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
				printf("Not a valid input");
				exit(EXIT_FAILURE);
			/*Case 3 - not a new program or word*/
			}else{				
				if(line[i] == '|'){
					/* dont add it to the word */
					if(line[i+1] == ' ' && line[i+2] == '|'){ 
						printf("Not a valid command\n");
						exit(EXIT_FAILURE);
					}
					/* else -- dont add anything in the buffer*/
				}else if(line[i] == ' '){
					/* dont add anything in the buffer */
					;
				}else{
					word_buff[word_ptr] = line[i];
					word_ptr++;
				}
			}
	}/* for loop */
	/* store the last progv in to progs */
	if(word_buff[0] != '\0'){
		strcpy(progv_buff[progv_ptr], word_buff);
		int f;
		for(f = 0; f< PROGV_MAX; f++){
			strcpy(progs_buff[progs_ptr][f], progv_buff[f]);
			
		}
		progs_buff[progs_ptr][progv_ptr+1] = NULL;
		/*ATTENTION: make char* buff[][] null will cause memory lost */
		argc += progv_ptr+1;
		progs_ptr++;
	}
	free_word_buff(word_buff);
	free_progv_buff(progv_buff, PROGV_MAX);
	return progs_buff;
}
/*======================================================================== */


int main()
{
	char ***progs = NULL;
	int fdTest = 0, num_pipes=0, size, i;
	char *line = NULL;
	stage_t *stages;
	/*fdTest = open("test02", O_RDWR);*/
	printf("line: ");
	fflush(stdout);
	line = read_long_line(fdTest);

	printf("/n");
	printf("Line contains at least %s",line);


	/*============== Test 1 - parse comand line ===============*/

	/*  
	if(signal(SIGSEGV, handle_SEGFAULT) == SIG_ERR) {
	    fputs("An error occurred while setting a signal handler.\n", stderr);
		exit(EXIT_FAILURE);
	}
	*/

	progs=get_progs_with_options(line);
	/* assums that get_pros_with_options handles | next to a char and exits */
	num_pipes = count_pipes(line);
	if (num_pipes >= PROGV_MAX){
        pipe_limit();
        exit(2);
    }
	/*stages is malloced within the funtion */ 
	
	/*For test 1 - is good */
	/*For Test 2 - is good */
	/*For Test 3 - not getting -la  */
	/*===============Test 3 - stage testing ================= */
	size = num_pipes+1;
	stages = new_stages(progs, size);
	/*===========================================================================================*/
	free_prog_buff(progs, PROGV_MAX, PROGS_MAX);
	print_stage(stages, size);
	free(line);
	
	return 0;
}
