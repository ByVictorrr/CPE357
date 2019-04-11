#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ASCII 255
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
			putchar(c);
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




/* getDup: returns a pointer to space allocated in heap, if there are duplicates*/
char *getDup(char *set1)
{
	int size_heap = strl(set1)+1 ; /*plus one to include \0*/
	char *dupPtr = (char*)calloc(size_heap, sizeof(char)); /* allocates MAXCHAR/2 elements in heap contingously) */
	printf("\n max allocated: size of :  %d", size_heap);
	return dupPtr;
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
void fillDeleteTable(int *table, char *argv2)
{
	int i=0;
	char c;
	while (*argv2){
		if (*argv2 == '\\') /* if set1 has a escape character*/
			c = getEscChar(*argv2++);
		else
			c = *argv2++;
	table[c] = DELETED; /*this indicates that in our hash table if you give it a key of c->-1 if used alread*/
	}
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

		initTable(hashTable); /* hashTable[i] = i; if not used*/
		case 1: /* mytr -d 'set' option*/
		{
			fillDeleteTable(hashTable, argv[2]);
			getLine(hashTable);
			goto main_loop;
		}
		case 2: /* mytr 'argv[1]' 'argv[2]'*'*/
		{
			
		}
	}
		return 0;
}


