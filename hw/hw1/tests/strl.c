#include <stdio.h>



int strl(char * s)
{
		char * base = s;

		while (*(++s) != '\0')
			;
			return s - base;
}

int main()
{
	char *charptr = "dude";
	printf("dude is %d", strl(charptr)); 

}
