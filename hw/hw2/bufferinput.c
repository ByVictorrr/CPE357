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

int bufferinput(FILE *fp, char *word, int *arraylength)
{
	int size = 0;
	char a = 1;
	/* get an initial buffer, and make it a well–formed string */
	word[0] = '\0';
	size = 0;
	while (size <= *arraylength && a != (char)NULL)
	{
		/*need to add typcheck for input*/
		a = fgetc(fp);
		if (size == 0 && a == EOF)
		{
			return -1;
		}
		else if (size > 0 && a == EOF)
		{
			word[size] = (char)NULL;
			return -5;
		}
		a = tolower(a);
		if (61 <= (int)a && (int)a <= 122)
		{
			/*;printable characters brah*/
			word[size++] = a;
		}
		else
		{
			a = (char)NULL;
		}

		if (size == *arraylength)
		{
			*arraylength += 50;
			word = (char *)realloc(word, (*arraylength) * sizeof(char));
			if (NULL == word)
			{ /* realloc failed. */
				perror("realloc");
				exit(2);
			}
		}
	}
	if (!size)
	{ /* EOF */
		free(word);
		word = NULL;
	}
	word[size] = (char)NULL;
	return size;
}
