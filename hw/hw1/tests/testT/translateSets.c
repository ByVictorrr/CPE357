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

/*mapChar: maps c1 -> c2 in line
 return 0 - if no char c1 is found in line
 return 1 - if at leaste one char c1 is found in line
 * */
int mapChar(char *line, char c1, char c2)
{                                                                                                                                                               
	int i,j;

	for ( i=0, j=0; i< strl(line); i++) /*plus one because of null char not recognized by strl*/
				if (line[i] == c1){
					line[i] = c2;
					j++;
				}
	if(j == 0)
		return 0; /*c1 isnt in line*/
	
	return 1; /*c1 is in line*/
}                    

int main()
{
	char *arg_i_2 = "hi";
	char *arg_i_3 = "by";
	char line_dup[MAXCHAR];
	int j;

	line[0] = 'a';
	line[1] = 'h';
	line[2] = 'i';
	line[3] = 'h';
	line[4] = '\0';
	
	for (j=0; j< strl(line)+1; j++)
		line_dup[j] = line[j];

	int size = strl(arg_i_2);
	int i=0;
	while ( size-- > 0 )
		i += mapChar(line, *arg_i_2++,*arg_i_3++);
	if( i == 0 )
		printf("Not chars from h i are found in: %s", line);
		/* not found */
	else /* found at least one char in line */
			printf("new string:  %s", line);
			printf("\noriginal string: %s", line_dup);
	return 0;
}


