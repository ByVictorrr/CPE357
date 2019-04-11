#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ASCII 256
#define DELETED -1
typedef enum { false, true } bool;

struct node
{
	int value;
	struct node *next;
};


struct node hashTable[ASCII]; 


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
	int i=0,j=0;
	char c;

	while ( (c = getchar()) != EOF )
	{	
		if(table[c].value != DELETED &&  table[c].next == NULL)
			putchar(table[c].value);

	}
	return 0; /*for overflow error or EOF*/
}
/* getFormat: 
return  0: if there is an error end program
returns 1: in -d mode
return  2: in tranlate mode
*/

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
		if (*set == '\\') /* if set1 has a escape character*/
		{
			c = getEscChar(*(set+1));
			set++;
		}else
			c = *set;
	table[c].value = DELETED; /*this indicates that in our hash table if you give it a key of c->-1 if used alread*/
	set++;
	}
}

int count(struct node *head)
{
	struct node*cursor = head;
	int i =0;
	while(cursor !=NULL)
	{
		i++;
		cursor = cursor->next;
	}
	return i;
}


void fillTranslateTable(struct node *table, char *set1, char *set2)
{
	char c, b, prev_c;
	int i, j, size1 = strl(set1), size2 = strl(set2);
	for(i=0,j=0; i< size1; i++) /*go till set1 == '\0'*/
	{ 
		if(set1[i] == '\\'){
			c=getEscChar(set1[i+1]);
			if(c == '\t' || c=='\\' || c== '\n')
				i++;
		}
		else
			c=set1[i];	
/*check set 2*/
		if(set2[j] == '\\' && j < size2-1)
		{	b=getEscChar(set2[j+1]);
			if(b == '\t' || b=='\\' || b== '\n')
				j++;
		}
		else
			b=set2[j];	

		table[c].value = b;	
		/*will get here if set1 > set2*/	
		if (j< size2 )
			j++;
		else if ( j >= size2 -1 && size1>size2)
		{
			table[prev_c].next = &table[c]; /*linking on */	
		}
		prev_c = c;
		}
		
	/*if reached last char of set2 i is index at which that ends*/
}
int main(int argc, char *argv[])
{

			
			initTable(hashTable); /* hashTable[i] = i; if not used*/

			fillTranslateTable(hashTable, argv[1], argv[2]);
			
		getLine(hashTable);

		return 0;
}


