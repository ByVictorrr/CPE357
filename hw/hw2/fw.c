#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "bst.h"
#include "fw.h"
#define SIZE 100
extern numOfNodes;

int main(int argc, char *argv[])
{
	int TopWords = 10;
	FILE *fp;
	int arraysize = 40;
	char *word = (char *)malloc(arraysize * sizeof(char));
	int wordsize = 0;
	struct node *root = NULL;

	if (fp == NULL)
		switch (argc)
		{
		case 1: /*case 1: only input executable*/
			/*this case we want to get input from std in*/
			while (wordsize != -1)
			{
				wordsize = bufferinput(stdin, word, &arraysize);
			}

			break;
			/*==============================================================================*/
		case 2: /*could use option */
			/*case 2.1: if the argv[1] != -n treat is a file input*/
			if (!strcmp(argv[1], "-n"))
				fprintf(stderr, "usage: fw [-n num] [ file1 [ file2 [..]]]\n");
			/*case 2.2: if the argv[1] is anything other than -n treat it as a file**/
			else
			{

				if (fp = fopen(argv[1], 'r'))
				{
					while (wordsize != -1)
					{
						wordsize = bufferinput(fp, word, &arraysize);
						root = insertNode(root, word);
					}
				}
				//read in single file
				else /*else file ptr null - something wrong with the file*/
					fprintf(stderr, "usage No such file or directory\n The top 10 words (out of 0 are:\n");
				break;
			}
			/*==============================================================================*/
		case 3: /*case 3: could be -n option and number, or just files or combination*/
			/*case 3.1: fw -n number*/
			if (!strcmp(argv[1], "-n") && isdigit(argv[2]))
			{
				TopWords = argv[2];
				while (wordsize != -1)
				{
					wordsize = bufferinput(stdin, word, &arraysize);
					root = insertNode(root, word);
				} /*stuff read in now need to do stuff*/
			}
			else
			{
				fprintf(stderr, "usage No such file or directory\n The top 10 words (out of 0 are:\n");
			}

		default:

			if (!strcmp(argv[1], "-n") && isdigit(argv[2]))
			{
				TopWords = argv[2];
				while (wordsize != -1)
				{
					wordsize = bufferinput(fp, word, &arraysize);
					root = insertNode(root, word);
				}
			}
			else
			{
				int i = 1;
				while (i < argc)
				{
					if (fp = fopen(argv[i], 'r'))
					{
						while (wordsize != -1)
						{
							wordsize = bufferinput(fp, word, &arraysize);
							root = insertNode(root, word);
						}
					}else{
						fprintf(stderr, "usage No such file or directory\n The top 10 words (out of 0 are:\n");
					}
				}
			}
		}

	return 0;
}
