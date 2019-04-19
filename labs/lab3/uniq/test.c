/*
 * Description:
 * This program will act as a filter, removing
 * adjacent duplicate lines as it copies its stdin to its stdout. That is, any line that is identical
 * to the previous line will be discarded rather than copied to stdout.
 * Your program may not impose any limits on file size or line length.
 * To get started, I highly recommend writing a function char *read long line(FILE *file)
 * that will read an arbitrarily long line from the given file into newly-allocated space. Once you
 * have that, the program is easy.
 * Be careful to free memory once you are done with it. A memory leak could be a real problem
 * for a program like this.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 1000
char buffer[MAXCHAR];
/*usage: ./unique filename filemod[-r, -w, -a]*/

/*swap_addr the address of two pointers*/
void swap_addr(char **p1, char **p2)
{
	char *temp = *p1; /*temp = p1->&p */
	*p1=*p2;
	*p2=temp;
}
void swap_vals(char *p1, char *p2)
{
	char temp = *p1;
	*p1=*p2;
	*p2=temp;

}
char *init_buffer(char *buffer, int max)
{
	int i;
	char *ptr_buffer = calloc(max); /*initalize buffer in memory*/
	for(i=0; i<max; i++)
		buffer[i] = '\0';
	strcpy(ptr_buffer, );	
}

/*hold a pointer to the whole file line delimited by\0";*/
char *read_long_line(FILE *file)
{

	int getc(FILE *), prev_size = 0;
	char c, *lines, *startPtr, *prev, *current, *temp;

	int numLines = 0, numChars=0;

	if (!file) return NULL;  /*if error in the file*/

	/*initally get something in heap*/

	startPtr = current = (char*)malloc(MAXCHAR); /*get base*/

	while((c=getc(file)) != EOF) /*read while not end of line*/
	{
		/*if at the end of a line*/
		if ((*current++ = c) =='\n'){
			*current = '\0';
			numChars = 0;
			current = startPtr;
					/*if the first line is read in*/
			if(numLines == 0){
				prev_size = strlen(current)+1;
				lines = (char *)malloc(prev_size); /*plus one for /0*/
				strcpy(lines,current); /*put original contents in heap*/
				prev =startPtr= lines; /* no previous to this numLines =0*/
				free(current); /*free old buffer*/
				current = (char*)malloc(MAXCHAR); 	/*get new buffer*/
				temp = current; /*hold base address of buffer*/
			}
			else{ /*check if the prev line is the same as current*/
				if (strcmp(startPtr,temp) == 0) /*if they are the same line*/
					printf("same so dont store\n");
					/*dont change prev*/
				else{ /*if adjacent lines are not the same*/
					int new_size = prev_size + strlen(temp)+1;
					lines = (char *)realloc(lines, new_size); /*plus one for /0*/
					
					startPtr = lines + prev_size; /*starting addres in the heap for next line*/
					
					/*find end of line then copy that pointer*/
					swap_vals(startPtr,temp);
					
					/*if it isnt then realloc pointer line*/
					prev_size = new_size; 
						
					free(temp); /*free old buffer*/

					current = (char*)malloc(MAXCHAR); 	/*get new buffer*/
					temp = current;
			}
		}
		numLines++; /*next line*/
	}
		numChars++; /*next char in the line*/
		if (numChars >= MAXCHAR - 1)
			current = (char*)realloc(current, numChars+MAXCHAR); /*add more space if ran out*/
	
} 
	return lines;
}





int main(int argc, char *argv[])
{

	FILE *fopen(const char *, const char *);

	FILE *fp = fopen(argv[1], "r");
	char *lines = read_long_line(fp);
	printf("lines:  %s",lines);	
	printf("lines: %s",lines+19);
	free(lines);
	fclose(fp);

	return 0;
}
