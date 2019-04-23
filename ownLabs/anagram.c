#include <stdio.h>
#include <stdlib.h>

char *anagram(char *s)
{
	char *temp = s;
	while(*temp)
		temp++;
	int size = temp - s;
	int i;
	temp = s;
	for(i=size; i>0; i--)
		*temp++ = s[i-rand()%size];

	return s;
}

int main()
{
	
	printf("%s",anagram("anagram"));
		
		
		
	return 0;
}
