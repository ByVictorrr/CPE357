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
#define INITAL 1000
/*usage: ./unique filename filemod[-r, -w, -a]*/

/*swap the address of two pointers*/
void swap(char **p1, char **p2)
{
	char *temp = *p1; /*temp = p1->&p */
	*p1=*p2;
	*p2=temp;
}


/*hold a pointer to the whole file line delimited by\0";*/
char *read_long_line(FILE *file)
{

	int getc(FILE *), prev_size = 0;
	char c, *lines, *startPtr, *prev, *current;

	int numLines = 0, numChars=0;

	if (!file) return NULL;  /*if error in the file*/

	/*initally get something in heap*/

	startPtr = current = (char*)malloc(INITAL); /*get base*/

	while((c=getc(file)) != EOF) /*read while not end of line*/
	{
		/*if at the end of a line*/
		if ((*current++ = c) =='\n'){
			*current = '\0';
			numChars = 0;
			swap(&current, &startPtr); /*startPtr is now the end of the line*/

					/*if the first line is read in*/
			if(numLines == 0){
				prev_size = strlen(current)+1;
				lines = (char *)malloc(prev_size); /*plus one for /0*/
				strcpy(lines,current); /*put original contents in heap*/
				prev = lines; /*get previous line*/

				free(current); /*free old buffer*/
				current = (char*)malloc(INITAL); 	/*get new buffer*/
			}
			else{ /*check if the prev line is the same as current*/
				if (strcmp(prev,current) == 0) /*if they are the same line*/
					;
					/*dont change prev*/
				else{ /*if adjacent lines are not the same*/
					int new_size = prev_size + strlen(current)+ 1;

					lines = (char *)realloc(lines, new_size); /*plus one for /0*/

					startPtr = prev + strlen(prev); /*starting addres in the heap for next line*/
					
					/*find end of line then copy that pointer*/
					strcpy(startPtr,current);
					/*if it isnt then realloc pointer line*/
					prev_size = new_size; 

					free(current); /*free old buffer*/
					current = (char*)malloc(INITAL); 	/*get new buffer*/
			}
		numLines++; /*next line*/
		}

	}
		numChars++; /*next char in the line*/
		if (numChars >= INITAL - 1)
			current = (char*)realloc(current, numChars+INITAL); /*add more space if ran out*/
	
} 
	return lines;
}





int main(int argc, char *argv[])
{

	FILE *fopen(const char *, const char *);

	FILE *fp = fopen(argv[1], "r");
	char *lines = read_long_line(fp);
	int i;
	printf("line num string: %s",lines);	
	free(lines);
	fclose(fp);

	return 0;
}
