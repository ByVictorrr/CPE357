
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int bufferinput(FILE *fp, char *word, int *arraylength)
{
    int size = 0;
    char a = 1;
    if (fp == NULL)
    {
        while (size <= arraylength && a != NULL)
        {
            /*need to add typcheck for input*/

            a = getchar();
			tolowercase(a);
			if (a == a) {/*need to put valid check*/
				word[size++] = a;
			}
			if (size == arraylength) {
				arraylength += 256;
				word = (char*)realloc(word, arraylength *sizeof(char));
			}
        }
    }
    else
    {
        while (size < arraylength && a != NULL)
        {
            a=fgetc(fp);
            tolowercase(a);
            if(a==a){/*need to put valid check*/
                word[size] =a;
            }
        }
    }
}