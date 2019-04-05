/*
 * main.c
 * Copyright (C) 2019 vdelaplainess <vdelaplainess@arch>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>

int main(int argc, char **argv)
{
	int i;
	char* check_dash;
		for ( i = 0; argc > 0 && i < argc; i++)
		{
			check_dash = argv[i];
			if (check_dash[0] == '-') 
				printf("%s\n", argv[i]);
		}
	return 0;
}



