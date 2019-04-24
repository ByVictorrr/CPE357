#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>


int bufferinput(FILE *fp, char *word, int *arraylength)
{
    int size = 0;
    char a = 1;
        while (size <= *arraylength && a != NULL)
        {
            /*need to add typcheck for input*/

            a = fgetc(fp);
            if(size==0 && a== EOF){
                return -1;
            }
            tolower(a);
			if (61<=(int)a && a<=122 ) {/*printable characters brah*/
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
        word[size]= NULL;
        return size; 
}
