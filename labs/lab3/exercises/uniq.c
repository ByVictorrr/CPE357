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
/*usage: ./unique filename filemod[-r, -w, -a]*/

char *read_long_line(FILE *file)
{

	int getc(FILE *), start=0;
	char c, *line, *startPtr;

	if (!file) return NULL;  /*if error in the file*/
	
	while((c=getc(file)) != EOF && c != '\n') /*read while not end of line*/
	{
		*line++=c;
		if(start==0) startPtr = line-1;
		start++;
	}
	/*if found new line change to \0*/
	*line = '\0';
	line = startPtr; /*get start of addres*/
	/*char *pc = (char *)malloc(sizeof(strlen(startPtr))) + 1;*/

	return strcpy((char *)malloc(sizeof(strlen(startPtr))+1),startPtr);
} 





int main(int argc, char *argv[])
{

	FILE *fopen(const char *, const char *);

	FILE *fp = fopen(argv[1], argv[2]);

	char *line = read_long_line(fp);

	printf("printing line %s", line );

	fclose(fp);

	free(line);
	return 0;
}
