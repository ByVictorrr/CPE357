#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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


/*mapStringToChar - find string*/

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
		return 0; /*c1 isnt in line*/
	
	return 1; /*c1 is in line*/
}

int main()
{	line[0] = 'a';
	line[1] = 'h';
	line[2] = 'i';
	line[3] = 'c';
	line[4] = 't';
	line[5] = 'o';
	line[6] = 'r';
	line[7] = '\0';
	
	char *set1 = "victor";
	char *set2 = "kay\\";
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
		
		printf("line before mapChar: %s ",line);
		while (--size_set2 > 0 ) /*not at last value of set2*/
				i+=mapChar(line, *set1++, *set2++);
		/*when last value in set2*/
		/*mapStringToChar(line, char *set(pointing to address of last index of set2), c2)*/
		
		printf("\nline before StringToChar: %s ",line);
		i+=mapStringToChar(line, set1, *set2);
		printf("\nline changed: %s ",line);
	}

	else{ /* if set1 is less than or equal to set2 lenght*/
		while (size-- > 0)
			i+=mapChar(line, *set1++, *set2++);
		if( i = 0)
			printf("no duplicates from set1 found in line");		
		}




	return 0;
}



