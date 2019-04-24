#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int bufferinput(FILE *fp, char *word, int arraylength)
{
    int size = 0;
    char a = 1;
        while (size <= *arraylength && a != NULL)
        {
            /*need to add typcheck for input*/
<<<<<<< Updated upstream

            a = fgetc(fp);
            if(size==0 && a== EOF){
                return -1;
            }
            tolowercase(a);
			if (61<=(int)a && a<=122 ) {/*printable characters brah*/
||||||| merged common ancestors

            a = getchar();
			tolowercase(a);
			if (32<=a<=122 ) {/*printable characters brah*/
=======
            a = getchar();
			a = tolowercase(a);
			if (32<=a<=122 ) {/*printable characters brah*/
>>>>>>> Stashed changes
				word[size++] = a;
			}else
            {
                a=NULL;
            }
            
<<<<<<< Updated upstream
			if (size == *arraylength) {
				*arraylength += 256;
				word = (char*)realloc(word, *arraylength *sizeof(char));
||||||| merged common ancestors
			if (size == arraylength) {
				arraylength += 256;
				word = (char*)realloc(word, arraylength *sizeof(char));
=======
			if (size == arraylength) {
				arraylength += 256;
				word = (char*)realloc(word, arraylength * sizeof(char));
>>>>>>> Stashed changes
			}
        }
        word[size]= '/0';
        return size; 
<<<<<<< Updated upstream
}
||||||| merged common ancestors
    }
    else
    {
        /*got belly ache will copy above down her soon*/
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
=======
    }
    else
    {
        /*got belly ache will copy above down her soon*/
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
>>>>>>> Stashed changes
