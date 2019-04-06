/*
 * mytr.c
 * Copyright (C) 2019 vdelaplainess <vdelaplainess@arch>
 *
 * Distributed under terms of the MIT license.
 */

#include "mytr.h"
#include <stdio.h>
#define 10000 /*safety of space */

char [MAX] input;
int getline(char *input, int size);

//compare argv[0](SET ONE) and argv[1] (SET TWO)
//have user keep enetering values
// if (int size1 = sizeof(set1)/(sizeof(int)
int main(int argc, char** argv)
{
	switch () //switch flag maybe?
	return 0;
}

/* reading a string using stdin */
int getline(char *input)
{
	int c, i;
	i = 0;
	while ( (c=getchar()) != EOF){
		input[i] = c;
		i++;
	}
}
