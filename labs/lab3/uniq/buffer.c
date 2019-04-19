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

#define MAXCHAR 4

char buff[MAXCHAR];
char *bp; /*pointer actual buffer*/
int num_overflows = 0;

/*overflow: a data struct to help organize pointer to overflow and the new size*/
struct overflow{
	char *b_overflow;
	int size;
}over;


/*overflow_buffer: if overflow of the buffer happends move current data in 
 *					buffer to heap and clear current buffer and keep reading.

returns: (1) returns a NULL if didnt allocate heap space - that is if it didnt overflow
         (2) The address of space in heap.
 */
char *overflow_buffer(char *buffer, int max)
{
	char *p_over;
	if( bp >= buffer + max - 1) /*if the buffer is greater than static size*/
	{
		if (num_overflows == 0)/*if first overflow*/
			p_over = malloc(max);
		else
			p_over = realloc(over.b_overflow, over.size+MAXCHAR);
			
		return p_over;
	}
	else 
		return NULL;
}


int main(int argc, char *argv[])
{

	FILE *fopen(const char *, const char *);

	FILE *fp = fopen("inputs/test.txt", "r");
	char c;
	
	bp = buff; /*base pointer*/

	while((c=getc(fp)) != EOF) /*read while not end of line*/
	{
		*bp++ = c;
		if(( over.b_overflow = overflow_buffer(buff, MAXCHAR))) /*if overflow_buffer returns NULL means we dont have overflow*/
			/*restet the buffer pointer to start of buffer*/
			bp = buff;
	}
	if(over.b_overflow)
		free(over.b_overflow);

	fclose(fp);

	return 0;
}
