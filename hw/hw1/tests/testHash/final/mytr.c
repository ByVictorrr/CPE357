#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mytr.h"

void initTable(struct node *table)
{
	int i;
	for(i=0; i<ASCII; i++)
	{
		table[i].value = i;
		table[i].next = NULL;
	}
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
int getLine( struct node *table)
{
	char c;
	while ( (c = getchar()) != EOF )
	{	
		if(table[(int)c].value != DELETED && !(table[(int)c].next != NULL && table[(int)c].value == table[(int)c].next -> value))
			putchar(table[(int)c].value);
	}
	return 0; /*for overflow error or EOF*/
}
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
void fillDeleteTable(struct node *table, char *set)
{
	char c;
	while (*set){
		if (*set == '\\' && *(set+1) != '\0') /* if set1 has a escape character*/
		{
			if(*(set+1) == 't' || *(set+1) =='\\' || *(set+1) == 'n')
			{
			c = getEscChar(*(set+1));
			set++;
			}
		}else
			c = *set;
	table[(int)c].value = DELETED; /*this indicates that in our hash table if you give it a key of c->-1 if used alread*/
	set++;
	}
}

void fillTranslateTable(struct node *table, char *set1, char *set2)
{
	char c, b, prev_c;
	int i, j, size1 = strl(set1), size2 = strl(set2);
	for(i=0,j=0; i< size1; i++) /*go till set1 == '\0'*/
	{ 
		if(set1[i] == '\\' && i < size1-1){
			c=getEscChar(set1[i+1]);
			if(c == '\t' || c=='\\' || c== '\n')
				i++;
		}
		else
			c=set1[i];	
/*check set 2*/
		if(set2[j] == '\\' && j < size2-1)
		{	b=getEscChar(set2[j+1]);
			if(b == 't' || b=='\\' || b== 'n')
				j++;
		}
		else
			b=set2[j];	

		table[(int)c].value = b;	
		/*will get here if set1 > set2*/	
		if (j< size2-1 )
			j++;
		else if ( i == size2  && size1>size2) /*if we gone past last character in set2*/
		{
			table[(int)prev_c].next = &table[(int)c]; /*linking on */	
		}
		prev_c = c;
		}
		
	/*if reached last char of set2 i is index at which that ends*/
}
int main(int argc, char *argv[])
{
main_loop:
/* getFormat: 
return  0: if there is an error end program
returns 1: in -d mode
return  2: in tranlate mode
*/

	switch(getFormat(argc,argv[1]))
	{
		case 0: /* usage error*/
			return 0;

		case 1: /* mytr -d 'set' option*/
		{
			initTable(hashTable); /* hashTable[i] = i; if not used*/
			fillDeleteTable(hashTable, argv[2]);
			getLine(hashTable);
			goto main_loop;
		}
		case 2: /* mytr 'argv[1]' 'argv[2]'*'*/
		{
			initTable(hashTable); /* hashTable[i] = i; if not used*/
			fillTranslateTable(hashTable, argv[1], argv[2]);
			getLine(hashTable);
			goto main_loop;

		}
	}
		return 0;
}


