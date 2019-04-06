/*
 * mytr.c
 * Copyright (C) 2019 vdelaplainess <vdelaplainess@arch>
 *
 * Distributed under terms of the MIT license.
 */

#include "mytr.h"
#include <stdio.h>
#define 10000 /*safety of space */

char [MAX] output;
int getline(char *input, int size);

//compare argv[0](SET ONE) and argv[1] (SET TWO)
//have user keep enetering values
// if (int size1 = sizeof(set1)/(sizeof(int)
int main(int argc, char** argv)
{
main_loop:

	switch (checkParms(arc,argv)) //switch flag maybe?
	{
		case 1:
			if (deleteChars(argv[2], sizeof(argv[2])/sizeof(char) == 1)
				goto main_loop; /* if every thing is fine*/
			/* use stdin(getchar)*/
		   /* -delete option */

			break;
		case 2:
			/* 'set1' 'set2'*/
			/* use stdin(getchar)*/
			break;
		case -1: /*wrong parms*/
			fprintf(stderr, "usage: %s <filename>\n", argv[0]);
			break;
	}		

		return 0;
}
//options: mytr -d 'char' or 'char' -d 
//options: mytr 'char' 'char'


//returns 1: if -d option is valid
//return  2: if 'char' 'char is good
//return  -1: if error 
int checkParms(int argc, const char **argv)
{
	if ( argc != 3)
		return -1;
	if ( *(argv[1]) == '-' && *(argv[1]+1) == 'd')
		return 1;
	else
		return 2; /*translation set1 -> set 2*/
}

//indicates delete operation is good by 1
//indicates delete operation is bad by -1
int deleteChars(const char *delete, int size_delete)
{
	char c,i;
	i=0;
	while ((c=getchar())!= EOF ){
		for ( i=0; i< size_delete; i++)
			if ( delete[i] != c)
				output[i] = c;
	return 1;
	}
	return -1; /*EOF*/
}
/*compareSETS: to see if */
int compareSETS(const char *set1, const char *set2)
{
	if (
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
