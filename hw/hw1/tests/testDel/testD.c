#include <stdio.h>
#include <string.h>
#define MAXCHAR 1000

char line[MAXCHAR]; /*deleteChar: for -d flag, deletes each char in set, that is found in line*/

/* getline: reads a line then stores into line 
return 0: if char line is greater than MAX_CHAR
return 1: if sucessful
*/
int getLine(char *line, int max_char)
{
	int i;
	char c;
	i = 0;
	while ( (c = getchar()) != EOF && c != '\n' && --max_char > 0 )
	{
			line[i] = c;
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


int strl(char * s)
{
		char * base = s;

		while (*(++s) != '\0')
			;
			return s - base;
}


/* getFormat: 
return  0: if argc != 3 - more argument than needed
returns 1: if -d option is valid
return  2: argv[1] = SET1 and arv[2] = SET2
*/
int getFormat(int argc, const char *argv)
{

	if ( argc != 3)
		return 0;
	if ( *(argv) == '-' && *(argv+1) == 'd')
		return 1;
	else
		return 2; /*translation set1 -> set 2*/
}

int deleteChar(char *input, char c)
{                                                                                                                                                               
	int i, j;

	for ( i=0, j=0; i< strlen(line); i++)                                                                                                                            
				if (line[i] != c){
					line[j] = line[i];
					j++;
				}
	if(i-j == 0)
		return 0; /*c isnt in line*/
	
	return 1; /*c is in line*/
}                    

int main(int argc, char *argv[])
{

main_loop:

	switch(getFormat(argc,argv[1]))
	{
		case 0: /* usage error*/
			printf("usage:\n mytr [-d] 'set1' 'set2'");
			break;

		case 1: /* mytr -d 'set' option*/
		{
			/*get line*/
			if (getLine(line,MAXCHAR) == 0)
				return; /*hit the EOF and return to tty*/
			/*else delete set in input line*/
			int size = strl(argv[2]);
			int i=0;
			while ( size-- != 0 )
				i += deleteChar(line, *(argv[2]));
				argv[2]++;
			if( i == 0 ) /* set doesnt have any characters that are in line*/
				printf("%s\n", line);
			else /*found at least one char from set in line*/
				printf("%s\n", line);
			goto main_loop;

		}
		case 2: /* mytr 'set1' 'set2'*/
			break;
	}
}



