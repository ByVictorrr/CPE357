#include <stdio.h>
#include <ctype.h>
/* strLower - pass by reference change original to lower case */

void strLower(char orginal[], char lower[])
{
	/* function tolower */
	int i = 0;
	while ((lower[i] = tolower(orginal[i])) != '\0')
		++i;
}

