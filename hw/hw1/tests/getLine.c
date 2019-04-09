/* getline: reads a line then stores into line 
return 0: if char line is greater than MAX_CHAR
return 1: if sucessful
*/
#include <stdio.h>

#define MAXCHAR 1000 
char line[MAXCHAR];

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

int main()
{
	int sucess = getLine(line, MAXCHAR);
	printf("input is : %s ", line);
}
