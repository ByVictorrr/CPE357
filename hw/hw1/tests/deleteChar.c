#include <stdio.h>
#include <string.h>
#define MAXCHAR 1000

char line[MAXCHAR]; /*deleteChar: for -d flag, deletes each char in set, that is found in line
 */

int strl(char * s)
{
		char * base = s;

		while (*(++s) != '\0')
			;
			return s - base;
}


int deleteChar(char *line, char c)
{                                                                                                                                                               
	int i, j;

	for ( i=0, j=0; i< strl(line)+ 1; i++) /*plus one because of null char not recognized by strl*/
				if (line[i] != c){
					line[j] = line[i];
					j++;
				}
	if(i-j == 0)
		return 0; /*c isnt in line*/
	
	return 1; /*c is in line*/
}                    

int main()
{
	char *arg_i_2 = "hi";
	line[0] = 'a';
	line[1] = 'h';
	line[2] = 'i';
	line[3] = 'h';
	line[4] = '\0';
	int size = strl(arg_i_2);
	int i=0;
	while ( size-- > 0 )
		i += deleteChar(line, *arg_i_2++);
	if( i == 0 )
		printf("Not chars from h i are found in: %s", line);
		/* not found */
	else /* found at least one char in line */
			printf("new string:  %s", line);
	return 0;
}


