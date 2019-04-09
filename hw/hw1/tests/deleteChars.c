#include <stdio.h>
#include <string.h>
#define MAXCHAR 1000

char line[MAXCHAR] = "hi2sddf"; /*deleteChar: for -d flag, deletes each char in set, that is found in line
 */

int deleteChars(const char *set, int size)                                                                                                                                                                         
{                                                                                                                                                                                                                            
+···int i, j;

	for ( i=0; i< strlen(line); i++)                                                                                                                                                                                      
			for ( j=0; j< size; j++)
				if ( set[j] == line[i])
					swap(
+···return 1;                                                                                                                                                                                                                
+···}                                                                                                                                                                                                                        
+···return -1; /*EOF*/                                                                                                                                                                                                       
}                    
int main()
{
	char *arg_i_2 = "hi"; 
	int deleted = deleteChar(arg_i_2, sizeof(arg_i_2));
	p
	return 0;
}


