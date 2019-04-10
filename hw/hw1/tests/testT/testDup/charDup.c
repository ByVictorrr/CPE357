#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXCHAR 1000

char line[MAXCHAR]; /*deleteChar: for -d flag, deletes each char in set, that is found in line*/
char *dupPtr = NULL;
int sp = -1;

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
	int j= numOfDupChars(*set1, dupPtr) ; 
	int k;
	char c = *set1;

		for (i=0; set1[i] != '\0' ; i++){
		/*j tells us how many duplicates there are for a given char*/
			if (j == 0)
			{
				index = count;
				break;
			}
			if (c == set1[i])
			{
				j--; /*j-1 more differnt characters in set1*/
				count++;
			}
			else
				count++; 
		}	
	return index;
}
int main()
{
	char *set1 = "freadfunny";
	char *set2 = "kay";	
	/*j
	printf("should be 1 for duplicates: %d \n", charDup(char1));
	printf("should be 2 for no duplicates: %d \n", charDup(char2));
*/	printf("%d",charDup(set1));
	printf("\nindex shoudl equal 5 where f: %d", lastNonRepeating(set1, dupPtr));

	return 0;
}

