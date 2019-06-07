#include "parseline.h"

int progs_argc = 0;
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

/*=================================================== */

/*==============Utility Functions====================*/
void init_word_buff(char **p, int word_size){
	if( (*p = (char *)malloc(sizeof(char)*word_size)) == NULL)
	{
		perror("malloc err");
		exit(EXIT_FAILURE);
	}
	memset(*p, '\0', word_size);
}
void init_progv_buff(char ***p, int progv_size, int word_size){
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
			argc++;
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


/*===================================================*/

/*==============Parsing functions=================== */

int parse_progv(char **progv, stage_t *stage){
	int i, in = 0 , o= 0;
	int cmd_line_ptr;
	for (i=0, cmd_line_ptr = 0; progv[i] != NULL; i++){
		/*Case 1 - just seperate cmd_line string */
		if(strcmp(progv[i], "<") != 0 && strcmp(progv[i], ">") != 0){
			strcpy(stage->cmd_line[cmd_line_ptr],progv[i]);
			stage->num_args++;
			cmd_line_ptr++;

		/*Case 2 - currently at a < or >*/
		}else{
			/*Case 2.1 - at a < */
			if(strcmp(progv[i], "<") == 0 ){
				if (!progv[i+1]|| !*progv[i+1])
				{
					bad_input(stage->cmd_line[0]);
					return -1;
					/* if > is the last arg - ERROR*/
				}	
				/*if two redirect signs stack together* - ERROR*/
				if (*progv[i+1] == '>' || *progv[i+1] == '<')
				{
					bad_input(stage->cmd_line[0]);
					return -1;
				}
				/*----- update Stage's outfile -------*/
				init_word_buff(&stage->in_file, WORD_MAX);
				strncpy(stage->in_file, progv[i+1], strlen(progv[i+1]));
				in += 1;
				i++;
			/*Case 2.2 - at a >  */
			}else{
				if (!progv[i+1]|| !*progv[i+1])
				{
					bad_output(stage->cmd_line[0]);
					return -1;
					/* if > is the last arg - ERROR*/
				}	
				/*if two redirect signs stack together* - ERROR*/
				if (*progv[i+1] == '>' || *progv[i+1] == '<')
				{
					bad_output(stage->cmd_line[0]);
					return -1;
				}
				/*----- update Stage's outfile -------*/
				
				o += 1;
							
				init_word_buff(&stage->out_file, WORD_MAX);
				strncpy(stage->out_file, progv[i+1], strlen(progv[i+1]));
				i++;
			}			
		}
	}
	stage->cmd_line[cmd_line_ptr] = NULL;
	if (in > 1)
	{
		bad_input(stage->cmd_line[0]);
		return -1;
	}
	if (o > 1)
	{
		bad_output(stage->cmd_line[0]);
		return -1;
	}
	if (stage ->out_file){
		/*if there is outfile and also pipe after --> error*/
		if(stage ->pipe_flag){
			ambiguous_output(stage->cmd_line[0]);
			return -1;
		}
	}
	if (stage -> in_file){
		if(i>0){
			ambiguous_input(stage->cmd_line[0]);
			return -1;
		}
	}

	return 0; 
}

/*Takes in a progs and creates a size num of stage */
stage_t *new_stages(char ***progs, int size)
{
	int i, k;
	stage_t *stages;

	if ((stages = (stage_t *)malloc(sizeof(stage_t) * size)) == NULL)
	{
		perror("malloc err");
		exit(EXIT_FAILURE);
	}
	/*======EMPTY ARGUMENTS=====*/

	if(!strcmp(progs[0][0],"\0")){
		empty_stage();
		exit(1);
	}

	/*Step 1 - (mallocing)setting up all members of stages */
	for (i = 0; i < size; i++)
	{
		if (progs[i] != NULL)
		{
			/*=================Setting up ============================  */
			init_progv_buff(&stages[i].cmd_line, PROGV_MAX, WORD_MAX);

			stages[i].num_args = 0;
			if(i < size -1){
				stages[i].pipe_flag = 1;
			}
			else{			
				stages[i].pipe_flag = 0;
			}
			/*printf("prog - %s %s \n", progs[i][0], progs[i][1]);*/
			stages[i].in_file = NULL;
			stages[i].out_file = NULL;
			/*========================================================= */
			/*=============Set Up cmd_line - End with NULL ptr=================*/
			/*only when i = size -1 when the stage will have pipe_flag == FALSE*/

			if(parse_progv(progs[i], &stages[i])==-1){
				/*=======================FREESTAGE=============== */
				return NULL;
			}


			/*============CHECK REDIRECTION < >  EXIT if error=================*/
			
			/*============update in, out, num_args================== */
			/*if (!redirect_is_valid(&stages[i]))
			{
				exit(1);
			}
 			*/
		}
	}
	return stages;
}

void print_stage(stage_t *stages, int size){
	int i;
	if(stages == NULL){
		exit(EXIT_FAILURE);
	}
	for(i = 0; i< size; i++){
	
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



int is_long_args(int counter, int max)
{
	if(counter >= max){
		return 1;
	}
	return 0;
}
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
			if (is_long_args(progv_ptr, PROGV_MAX)){
				/*free_word_buff(word_buff);
				free_progv_buff(progv_buff, PROGV_MAX);
				*/
				/*free progs too */
				many_arg();
				return NULL;
			}
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
				progs_argc += progv_ptr + 1;
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
					}
				}else if(line[i] == ' '){
					/* dont add anything in the buffer */
				}else{
					word_buff[word_ptr] = line[i];
					word_ptr++;
				}
			}
	}/* for loop */
	/* store the last progv in to progs */
	if(word_buff[0] != '\0'){
		strcpy(progv_buff[progv_ptr], word_buff);
		/*memset_progs(&progv_buff[progs_ptr], progv_buff, PROGV_MAX);*/
		int f;
		for(f = 0; f< PROGV_MAX; f++){
			strcpy(progs_buff[progs_ptr][f], progv_buff[f]);
		}
		progs_buff[progs_ptr][progv_ptr+1] = NULL;
		progs_argc += progv_ptr+1;
		progs_ptr++;
	}

	/*free_word_buff(word_buff);
	free_progv_buff(progv_buff, PROGV_MAX);
	*/

	return progs_buff;
}
/*======================================================================== */
