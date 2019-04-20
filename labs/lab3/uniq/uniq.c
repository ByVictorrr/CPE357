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
#define MAXCHAR 1000 /*inital amt of lines in the buffer*/

/*======================lines memory=================================*/
char *line;
char *prev; /*prev is the pointing to the beginingin of the ith line*/
/*===================================================================*/

/*======================Current line buffer=========================*/
char *pbuff;
/*==================================================================*/

/*================count number of lines==================*/
unsigned numLines =0;
unsigned sizeLines = 0;
/*=======================================================*/
char *read_long_line(FILE *file)
{

	int getc(FILE *);
	char *strcat(char *dest, const char *src);
	char *temp, c; /*temp is for moving allong pbuff*/
	
	/*case 1: file error*/
	if (!file) return NULL; 
	/*case 2: reading the whole file */
	pbuff = temp = (char*)malloc(MAXCHAR);

	/*initalize current size of buffer*/	
	unsigned sizebuff = MAXCHAR;
	int oneline = 0;
	while((c=getc(file)) != EOF)
	{
		/*case 3: store value of c in buffer */
		*temp++ = c;
		/*case 4: check if an overflow occured in buffer same line
		 *		count number of overflows in buff */
		if ( temp >= (MAXCHAR-1)+ pbuff )
		{
			/*Size alloationa are alwaysgoing to be mutliples os MAXCHAr*/
			sizebuff = sizebuff + MAXCHAR;
			pbuff = (char*)realloc(pbuff,sizebuff);
			temp = pbuff + (sizebuff - MAXCHAR); /*tryin to get next spot in stack for word*/
		}
		/*case 5: we got a new line*/
		if ( c == '\n')
		{
		   	/*go back to last value of '\n'*/ 
			
			oneline = temp - pbuff;
			/*Case 5.1: check if the first line becaue numLines==0*/
			if (!numLines)
			{
				/*case 5.1.1: 1st time allocate space for line*/
				line = (char*)malloc(oneline); /*what if not overflowed*/
				strcpy(line,pbuff);
				prev = line; /*have prev point to first char*/
				sizeLines = oneline;
			}else{ /*Case 5.1.2: ith time allocating space for line, also need to only reallocate on condition*/
				/*If were in this scope its assume that there is at least two lines*/
				if (strcmp(pbuff, prev)) /* if they arent equal*/
				{
					line = (char*)realloc(line,oneline+sizeLines);
					/*copy contents from buffer to prev*/
					char *temp = prev;
					prev = line;
					strcpy((prev = prev + sizeLines), pbuff);
					sizeLines += oneline;
				}

			}
			/*case 6: reset buffer*/ free(pbuff);
			pbuff = (char*)calloc(MAXCHAR,sizeof(char));
			temp = pbuff;

	sizebuff = MAXCHAR;
	numLines++;
		}

	} 
	*(prev+oneline)='\0';

	return line;
}



int main(int argc, char *argv[])
{

	FILE *fopen(const char *, const char *);

	FILE *fp = fopen("inputs/test.txt", "r");

	char *line_ptr = read_long_line(fp);
	int i;
	for(i=0; *line_ptr != '\0'; line_ptr++)
		putchar(*line_ptr);

	fclose(fp);

	free(line);
	return 0;
}
