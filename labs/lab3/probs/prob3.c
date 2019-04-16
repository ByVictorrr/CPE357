#include <stdio.h>

int main()
{
	char s[] = "Hello, World!\n";
	char *p;
	for(p=s; *p !='\0'; p++)
		putchar(*p);
}
