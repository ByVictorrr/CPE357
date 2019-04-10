#include <stdio.h>
#include <string.h>
#define MAXCHAR 1000

char line[MAXCHAR]; /*deleteChar: for -d flag, deletes each char in set, that is found in line*/
char *dupPtr = NULL;

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

int deleteChar(char *line, char c)
{                                                                                                                                                               
	int i, j;

	for ( i=0, j=0; i< strlen(line)+1; i++)                                                                                                                            
				if (line[i] != c){
					line[j] = line[i];
					j++;
				}
	if(i-j == 0)
		return 0; /*c isnt in line*/
	
	return 1; /*c is in line*/
}                    

/*mapChar: maps c1 -> c2 in line
 return 0 - if no char c1 is found in line
 return 1 - if at leaste one char c1 is found in line
 * */
int mapChar(char *line, char c1, char c2)
{                                                                                                                                                               
	int i,j;

	for ( i=0, j=0; i< strl(line) && c1 != '\0'; i++) /*plus one because of null char not recognized by strl*/
				if (line[i] == c1){
					line[i] = c2;
					j++;
				}
	if(j == 0)
		return 0; /*c1 isnt in line*/
	
	return 1; /*c1 is in line*/
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

/*mapStringToChar - loops for string of lastChars in line and replaces it with c2 if foud
 * return 1 - if lastChars string is found in line
 * return 0 - if lastChars string isnt found in line*/
int mapStringToChar(char *line, char *lastChars, char c2 )
{
	int i, j;
	int startIndex = 0;	

	for ( i=0, j=0; i< strl(line)+1; i++) /*plus one because of null char not recognized by strl*/
	{
		if(j > 1 && *lastChars == '\0'){ /* if the we found lastchars[] in line replace it in fist index that was fou*/
			line[startIndex] = c2; /* finally map c2 to string*/
			line[startIndex+1] = '\0';
		}
		else if (line[i] == *lastChars){
			lastChars++;
			if( j==0){
				startIndex = i; /*get index of starting index */
				j++;
			}else
				j++;
			
		}
		else
			j=0; /*indicating need to start over searching string*/
	}
	if(j == 0)
		return 0; 
	
	return 1;
}

/* getDup: returns a pointer to space allocated in heap, if there are duplicates*/
char *getDup(char *set1)
{
	int size_heap = strl(set1)+1 ; /*plus one to include \0*/
	char *dupPtr = (char*)calloc(size_heap, sizeof(char)); /* allocates MAXCHAR/2 elements in heap contingously) */
	printf("\n max allocated: size of :  %d", size_heap);
	return dupPtr;
}

/*charDup: checks if there is a duplicate of a character in set1
 * returns 1 - if there is a duplicate of a char in set1
 * return 0 - if there is no duplicate of a char in set1
 * Alters ptrDup - if duplicate found, if multiple of the same char
 *				 - changes ptrDup to have n-1 of multiple chars found in line
*/
int charDup(char *set1)
{
	int i, j;
	int k=0; /*indicate how many duplicates, alse used to incrment char array*/

	for(i = 0; i< strl(set1); i++)
		for (j = i+1;  j < strl(set1); j++)
			if ( set1[i] == set1[j]){
				if (++k==1 && dupPtr == NULL) /* if at least one duplicate create memory*/	
				{
					dupPtr = getDup(set1);
					dupPtr[k-1] = set1[j]; 
				}
				else if (dupPtr != NULL)
					dupPtr[k-1] = set1[j]; /* duplicate*/
			}
	dupPtr[k+1] = '\0'; /* to tell in the heap when the last value is*/
	if (k>0)
		return 1; /* if at least one dup*/
	return 0;
}
 
/*numOfChars: counts the number number of duplicated characters in dupPtr
 * returns 0: if no chars foundj
 */
int numOfDupChars(char c, char *dupPtr)
{
	int i,j;
	for (i = 0,j=0; i< strl(dupPtr); i++)
		if ( *dupPtr == c)
		{
			dupPtr++;
			j++;
		}
	return j;
}

/* getLastRepeating - this function return the index of the last orccuring character in a str
 * can pass in for set an incrmenting address to check duplicates for every char
 * /
*/
int lastNonRepeating(char *set1, char *dupPtr)
{
	int index = 0, i;
	int count = 0;
	int j= numOfDupChars(*set1, dupPtr)+1;
	int k;
	char c = *set1;

		for (i=0; set1[i] != '\0' || j==0 ; i++){
		/*j tells us how many duplicates there are for a given char*/
			if (c == set1[i])
			{
				j--; /*j-1 more differnt characters in set1*/
				count++;
			}
			else if (j == 0)
			{
				index = i; /*i maybe?*/
				break;
			}

			else
				count++; 
		}	
	return index-1;
}



int main(int argc, char *argv[])
{
main_loop:

	switch(getFormat(argc,argv[1]))
	{
		case 0: /* usage error*/
			printf("usage:\n mytr [-d] 'set1' 'set2'\n");
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
				i += deleteChar(line, *argv[2]++);
			if( i == 0 ) /* set doesnt have any characters that are in line*/
				printf("%s\n", line);
			else /*found at least one char from set in line*/
				printf("%s\n", line);
			goto main_loop;

		}
		case 2: /* mytr 'argv[1]' 'argv[2]'*/
			/*gett line*/
			if(getLine(line, MAXCHAR) == 0)
				return; /*hit the EOF*/
				int size_argv1 = strl(argv[1]);
				int size_argv2 = strl(argv[2]);
				int i = 0;
				int size = strl(line);
				/*j
				printf("should be 1 for duplicates: %d \n", charDup(argv[1]));
				printf("should be 2 for no duplicates: %d \n", charDup(argv[2]));
			*/	
				if (cmpStr(argv[1], argv[2]))  /* if argv[1] is longer than argv[2] than map the last char in set 2 to the same index +i ... index size of argv[1]*/
				{
					/* maps char to char until last char of argv[2]
					 * then it maps {argv[1][strl(argv[2])-1], ...,argv[1][strl(argv[1])-1]} -> argv[2][strl(argv[2])-1];
					 */
					
					printf("line before mapChar: %s ",line);
					while (--size_argv2 > 0 ) /*not at last value of argv[2]*/
							i+=mapChar(line, *argv[1]++, *argv[2]++);
					/*when last value in argv[2]*/
					/*mapStringToChar(line, char *set(pointing to address of last index of argv[2]), c2)*/
					
					printf("\nline before StringToChar: %s ",line);
					i+=mapStringToChar(line, argv[1], *argv[2]);
					printf("\nline changed: %s ",line);
				}
			
				else{ /* if argv[1] is less than or equal to argv[2] lenght*/
					while (size-- > 0)
						i+=mapChar(line, *argv[1]++, *argv[2]++);
					if( i = 0)
						printf("no duplicates from argv[1] found in line");		
					}
			/* else translate line from argv[1] -> argv[2]*/

			break;
	}
}



