#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ASCII 256
#define DELETED -1

int hashTable[ASCII]; 

void initTable(int *table)
{
	int i;
	for(i=0; i<ASCII; i++)
		table[i] = i;
}
int strl(char * s)
{
		char * base = s;

		while (*(++s) != '\0')
			;
			return s - base;
}

/*cmpStr: compares length of set1 and set2
 * return -1 - if set1 < set2
 * return 0 - if set1==set2
 * return 1 - if set 1 > set2
 */
int cmpStr(char *set1, char *set2)
{
	if(strl(set1) > strl(set2))
			return 1;
	else if (strl(set1) == strl(set2))
			return 0;
	return -1;
}

/* getline: reads a line then stores into line 
return 0: returned normall;
*/
int getLine(int *table)
{
	int i;
	char c;
	while ( (c = getchar()) != EOF )
	{
		if(table[c] != DELETED)
			putchar(table[c]);
	}
	return 0; /*for overflow error or EOF*/
}
/* getFormat: 
return  0: if there is an error end program
returns 1: in -d mode
return  2: in tranlate mode
*/
int getFormat(int argc, char *set1)
{ 
	switch(argc)
	{
		case 1: 
			fprintf(stderr, "mytr:\n usage: mytr [-d] 'set1' ['set2'] \n");
			return 0;
			break;
		case 2:
			if ( cmpStr(set1,"-d") != 0)
				fprintf(stderr, "mytr: missing operand after '%s'\nTwo strings must be given when translating\nTry 'tr --help' for more information.\n",set1);
			else
				fprintf(stderr, "mytr: missing operand after -d \nTry 'tr --help' for more information.\n");
			return 0;
			break;
		case 3: /*should be three if no error*/
			if ( cmpStr(set1,"-d") == 0) /* if set1 is -d - delete mode*/
				return 1;
			else
				return 2; /*translation set1 -> set 2*/
		default:
			fprintf(stderr, "mytr: extra operand\nTry 'tr --help' for more information.\n");
			return 0;
	}
}

/*getEscChar: return the value value of espace character given that \ is the character before c in the string*/
char getEscChar(char c)
{
	switch(c)
	{
	case '\\': /* have to check this way because computer reads in \\ but in characters \\ is \*/
		return '\\';
	case 'n':
		return '\n';
	case 't':
		return '\t';
	}
	return c;
}

/*fills table for delete option:
 *table[deleteC] = -1; if used
 *table[i] = i; if not used
 */
void fillDeleteTable(int *table, char *set)
{
	char c;
	while (*set){
		if (*set == '\\') /* if set1 has a escape character*/
		{
			c = getEscChar(*(set+1));
			set++;
		}else
			c = *set;
	table[c] = DELETED; /*this indicates that in our hash table if you give it a key of c->-1 if used alread*/
	set++;
	}
}

void fillTranslateTable(int *table, char *set1, char *set2)
{
	char c, b;
	int i, j, size1 = strl(set1), size2 = strl(set2);
	for(i=0,j=0; i< size1; i++, j++) /*go till set1 == '\0'*/
	{ 
		if(set1[i] == '\\')
			c=getEscChar(set1[i+1]);
		else
			c=set1[i];	
/*check set 2*/
		if(set2[j] == '\\')
			b=getEscChar(set2[j+1]);
		else
			b=set2[j];	
		
		table[c] = b;

	}
		
	/*if reached last char of set2 i is index at which that ends*/
}
int main(int argc, char *argv[])
{
			printf("argv[2]=%s: ", argv[2]);
		
			initTable(hashTable); /* hashTable[i] = i; if not used*/
			fillDeleteTable(hashTable, argv[2]);

		return 0;
}


