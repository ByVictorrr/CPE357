#include <stdio.h>
#include <ctype.h>
/* strLower - pass by reference change original to lower case */

void strLower(char *orginal, char *lower)
{
	/* function tolower */
	while ((*lower++ = tolower(*orginal++)) != '\0')
		;
}


