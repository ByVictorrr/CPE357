/* usage:
	1.) mytr 'set1' 'set2'
	2.) mytr '-d' 'set'
 */

#include <stdio.h>
#define MAXCHAR 10000 /*maxium number of characters per line*/

char line[MAXCHAR];

int getline(char *line, int size); /*for reading line store into var line*/
int strl(const char * s); /*for getting the length of a string*/
int getFormat(int argc, const char *argv[]); /*type of format of commandline arguments*/
int foundInLine(char c); /* returns the index of set/set1 char that is found in line; returns 1 if that char is found, and return 0 if not found */
int deleteChar(char *line, char c); /* for usage 2; to delete char from set, in line*/




int main(int argc, char* argv[])
{
main_loop:

	switch (getFormat(arc,argv)) //switch flag maybe?
	{
		case 1:
			if (deleteChars(argv[2], sizeof(argv[2])/sizeof(char) == 1)
				goto main_loop; /* if every thing is fine*/
			/* use stdin(getchar)*/
		   /* -delete option */

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

/* getFormat: 
return  0: if argc != 3 - more argument than needed
returns 1: if -d option is valid
return  2: argv[1] = SET1 and arv[2] = SET2
*/
int getFormat(int argc, const char *argv[])
{

	if ( argc != 3)
		return 0;
	if ( *(argv[1]) == '-' && *(argv[1]+1) == 'd')
		return 1;
	else
		return 2; /*translation set1 -> set 2*/
}



//indicates delete operation is good by 1
//indicates delete operation is bad by -1
int deleteChars(const char *delete, int size_delete)
{
	char c,i;
	i=0;
	while ((c=getchar())!= EOF ){
		for ( i=0; i< size_delete; i++)
			if ( delete[i] != c)
				output[i] = c;
	return 1;
	}
	return -1; /*EOF*/
}
/*compareSETS: to see if */
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

/* getline: reads a line then stores into line 
return 0: if char line is greater than MAX_CHAR
return 1: if sucessful
*/
int getline(char *line, int max_char)
{
	int i, c;
	i = 0;
	while ( (c = getchar()) != EOF && c != '\n' && --max_char > 0 )
	{
			line[i] = s;
			i++;
	}
	if (c == '\n')
	{
		line[i] = '\0';
		line[++i] = c;
		return i;
	}
	return 0; /*for overflow error or EOF*/
}


