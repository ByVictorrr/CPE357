
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int bufferinput(FILE *fp, char *word, int *arraylength)
{
    int size = 0;
    char a = 1;
        while (size <= arraylength && a != NULL)
        {
            /*need to add typcheck for input*/

            a = fgetc(fp);
			tolowercase(a);
			if (32<=a<=122 ) {/*printable characters brah*/
				word[size++] = a;
			}else
            {
                a=NULL;
            }
            
			if (size == *arraylength) {
				*arraylength += 256;
				word = (char*)realloc(word, *arraylength *sizeof(char));
			}
        }
        word[size]= '/0';
        return size; 
}