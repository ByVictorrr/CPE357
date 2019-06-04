#ifndef PARSELINE_H
#define PARSELINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <regex.h>
#include <signal.h>
#include <unistd.h>
#define WORD_MAX 10
#define PROGV_MAX 10
#define PROGS_MAX 10
#define CMD_LINE_MAX 10
enum boolean{FALSE,TRUE};


typedef struct stage{
	/*command options files */
	char **cmd_line;
	char *in_file;
	char *out_file;
	int num_args; /*counts the number of string in cmd_line  */
	int pipe_flag; /*set if there is a pipe to the right*/
}stage_t;



/*====================GLOBAL VARS===============================*/
/* ==================================================== */
/*================Debuggin fucntions=============== */
void print_progv(char **progv, int size);

/* ================================================ */

/*==============Utility Functions====================*/
void init_word_buff(char **p, int word_size);
void init_progv_buff(char ***p, int progv_size, int word_size);
void init_progs_buff(char ****p, int progs_size, int progv_size, int word_size);
void free_word_buff(char *ptr_word);
void free_progv_buff(char **ptr_progv, int size);
void free_prog_buff(char ***prog, int progv_size, int progs_size);
void clear_progv(char *** progv, int size);
void memset_progs(char ***progs_nth, char **progv, int size);
/*===================================================*/

/*==============Parsing functions=================== */
void parse_progv(char **progv, stage_t *stage);
/*Takes in a progs and creates a size num of stage */
stage_t *new_stages(char ***progs, int size);
void print_stage(stage_t *stages, int size);
/*=========================================================*/
int count_pipes(char *line);
char ***get_progs_with_options(char *line);
/*======================================================================== */

#endif

