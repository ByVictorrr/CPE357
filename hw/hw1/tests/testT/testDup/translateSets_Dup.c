#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXCHAR 1000

char line[MAXCHAR]; /*deleteChar: for -d flag, deletes each char in set, that is found in line
 */
char *dupPtr = NULL;

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


/*cmpStr: compares length of set1 and set2
 * return -1 - if set1 < set2
 * return 0 - if set1==set2
 * return 1 - if set 1 > set2
 */
int cmpStr(char *set1, char *set2)
{
	if(strl(set1) > strl(set2)
			return 1;
	else if (strl(set1) == strl(set2))
			return 0;
	return -1;
}


/*mapStringToChar - find string*/

int mapStringToChar(char *line, char *lastChars, char c2 )
{
	int i,j;
	char temp;

	for ( i=0, j=0; i< strl(line); i++) /*plus one because of null char not recognized by strl*/
	{
		if (line[i] == *lastChars){
			temp = *lastChars++;
			j++;
		}
		if(j > 2) /* if the line has "lastchar[i] .... in it then
			
	}
	}
	if(j == 0)
		return 0; /*c1 isnt in line*/
	
	return 1; /*c1 is in line*/
}

int main()
{	line[0] = 'a';
	line[1] = 'h';
	line[2] = 'i';
	line[3] = 'h';
	line[4] = '\0';
	

	char *set1 = "hihhdfi";
	char *set2 = "kay";	
	int size_set1 = strl(set1);
	int size_set2 = strl(set2);
	int i = 0;
	int size = strl(line);

	/*j
	printf("should be 1 for duplicates: %d \n", charDup(set1));
	printf("should be 2 for no duplicates: %d \n", charDup(set2));
*/	
	if (cmpStr(set1, set2)==1)  /* if set1 is longer than set2 than map the last char in set 2 to the same index +i ... index size of set1*/
	{
		/* maps char to char until last char of set2
		 * then it maps {set1[strl(set2)-1], ...,set1[strl(set1)-1]} -> set2[strl(set2)-1];
		 */
		
		while (size_set2-- > 0 && size-- > 0 ) /*not at last value of set2*/
				i+=mapChar(line, *set1++, *set2++);
		/*when last value in set2*/
		/*mapStringToChar(line, char *set(pointing to address of last index of set2), c2)*/
		
	}

	else{ /* if set1 is less than or equal to set2 lenght*/
		while (size-- > 0)
			i+=mapChar(line, *set1++, *set2++);
		if( i = 0)
			printf("no duplicates from set1 found in line");		
		}




	if (charDup(set1) > 0)
	{
		printf("\nshould be 1 for duplicates: %d \n", 1);
		printf("\nptr = shoudl equal h: %s", dupPtr);
		free(dupPtr);
	}
	else
		printf("should be 0 for no duplicates: %d \n", 0);


	return 0;
}



