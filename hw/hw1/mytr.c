/* usage:
	1.) mytr 'set1' 'set2'
	2.) mytr '-d' 'set'
 */

#include <stdio.h>
#include "./tests/getFormat.c"

#define MAXCHAR 10000 /*maxium number of characters per line*/

char line[MAXCHAR];

int getline(char *line, int size); /*for reading line store into var line*/
int strl(const char * s); /*for getting the length of a string*/
int getFormat(int argc, const char *argv[]); /*type of format of commandline arguments*/
int foundInLine(char c); /* returns the index of set/set1 char that is found in line; returns 1 if that char is found, and return 0 if not found */
int deleteChar(char *line, char c); /* for usage 2; to delete char from set, in line*/ 


struct node
{
	char c;
	struct node *next;
};

int main(int argc, char* argv[])
{
main_loop:

	switch (getFormat(arc,argv[1])) //switch flag maybe?
	{
		case 1: /* if typed -d 'set'*/
			
			
			break;
		case 2:
			/* 'set1' 'set2'*/
			/* use stdin(getchar)*/
			break;
		case 0: /*wrong parms*/
			fprintf(stderr, "usage: %s <filename>\n", argv[0]);
			break;
	}		

		return 0;
}


int compareSETS(const char *set1, const char *set2)
{
	if (strl(set1) > strl(set2){
	
}

translate(const char *set1, const char *set2)
{
	if(strl(set1) > strl(set2))
		//if set1[i] is in line then change 
		//find set1[i].. up to set2[size2-1] change 
}



