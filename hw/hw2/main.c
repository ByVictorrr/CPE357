#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "fw.h"
#define SIZE 100

void readOutWords(int amount, int numnodes, struct node arr[])
{
	int n = 0;
	printf("The top %d words (out of %d)are:\n", amount, numnodes);
	for (n = 0; n < amount; n++)
	{
		printf("%s: count: %d\n", arr->word, arr->wCount);
		arr++;
	}
}

int bufferinput(FILE *fp, char *word, int *arraylength)
{
	int size = 0;
	char a = 1;
	while (size <= *arraylength && a != NULL)
	{
		/*need to add typcheck for input*/

		a = fgetc(fp);
		if (size == 0 && a == EOF)
		{
			return -1;
		}
		tolower(a);
		if (61 <= (int)a && (int)a <= 122)
		{
			/*;printable characters brah*/
			word[size++] = a;
		}
		else
		{
			a = NULL;
		}

		if (size == *arraylength)
		{
			*arraylength += 256;
			word = (char *)realloc(word, *arraylength * sizeof(char));
		}
	}
	word[size] = NULL;
	return size;
}
struct node *addToAddrNodeArr(struct node *root, int numNodes)
{
	struct node **stack = (struct node **)malloc(sizeof(struct node) * numNodes);
	struct node *current = root;
	struct node *nodeArry = (struct node *)malloc(sizeof(struct node) * numNodes);
	struct node *baseAddrArr = nodeArry;

	int j; //count num of nodes

	//Step 2 - check if root isnt null
	if (!root)
		return NULL;
	j = -1;
	/*Step 3 - while numnodes not equal to i */
	while (1)
	{
		/*INORDER*/

		//Step 4.1  - is current null? if it isnt add it to the stack
		if (current != NULL)
		{
			stack[++j] = current; //push into stack
			current = current->left_child;
		}
		//step 4.2 - go right if current == NULL
		else
		{
			if (j == -1)
				break;
			current = stack[j--];
			*nodeArry++ = *current;
			printf("word: %s and wcount: %d\n", (nodeArry - 1)->word, (nodeArry - 1)->wCount);
			current = current->right_child;
		}
	}
	return baseAddrArr;
}
void inOrder(struct node *root)
{
	//Base case when reached a leaf
	if (root == NULL)
		return;
	//General case
	else
		inOrder(root->left_child);
	printf("word: %s, wordCount: %d\n", root->word, root->wCount);
	inOrder(root->right_child);
}
void freeTree(struct node *root)
{
	if (!root)
		return;
	else
	{
		freeTree(root->left_child);
		freeTree(root->right_child);
		free(root->word);
		free(root);
	}
}
struct node *newNode(char *word)
{
	struct node *new;
	new = (struct node *)malloc(sizeof(struct node));
	new->word = (char *)malloc(sizeof(strlen(word) + 1));

	//case 1: if either allocation of node or word NULL  - return NULL
	if (!new || !new->word)
		return NULL;

	new->wCount = 1;
	strcpy(new->word, word);
	new->left_child = NULL;
	new->right_child = NULL;
	numOfNodes++;

	return new;
}
/* insertNode: if (word is lexicographically less than root-> word stored in left child*/
struct node *insertNode(struct node *root, char *word)
{
	//Case 1: if tree is empty
	if (!root)
		return newNode(word);
	//Case 2: if the word in current node is word inserted
	else if (strcmp(root->word, word) == 0)
	{
		root->wCount++;
		return root;
	}
	//Case 3: if current word is less than current node then go to left node
	else if (strcmp(word, root->word) < 0) //if condition is negative word is lexicograpically less than root->word
		root->left_child = insertNode(root->left_child, word);
	else
		//Case 4: if current greater than current node then go to left node
		root->right_child = insertNode(root->right_child, word);

	return root;
}
/*returns Null if not found*/
struct node *searchNode(struct node *root, char *word)
{
	//case 1: base case if node isnt foud
	if (root = NULL)
		return NULL;
	//case 2: if word is found return address
	else if (root->word == word)
		return root;
	else if (strcmp(word, root->word))
		return searchNode(root->left_child, word);
	else
		return searchNode(root->right_child, word);
}

int comparator(const void *p, const void *q)
{
	int l = ((struct node *)p)->wCount;
	int r = ((struct node *)q)->wCount;
	return (r - l);
}

int main(int argc, char *argv[])
{
	struct node *addToAddrNodeArr(struct node * root, int numOfNodes);
	int TopWords = 10;
	FILE *fp;
	int arraysize = 40;
	char *word = (char *)malloc(arraysize * sizeof(char));
	int wordsize = 0;
	struct node *root = NULL;
	struct node *ptrArry;
	int i;

	switch (argc)
	{
	case 1: /*case 1: only input executable*/
		/*this case we want to get input from std in*/
		while (wordsize != -1)
		{
			wordsize = bufferinput(stdin, word, &arraysize);
			if (wordsize != EOF && wordsize != NULL)
			{
				root = insertNode(root, word);
			}
			/*printf("word: %s \n", word);*/
		}
		ptrArry = addToAddrNodeArr(root, numOfNodes);
		int j = 0;

		int sizeoarray = sizeof(ptrArry) / sizeof(ptrArry[0]);

		qsort(ptrArry, numOfNodes, sizeof(ptrArry[0]), comparator);
		if (TopWords > numOfNodes)
		{
			TopWords = numOfNodes;
		}
		readOutWords(TopWords, numOfNodes, ptrArry);

		break;
		/*==============================================================================*/
	case 2: /*could use option */
		/*case 2.1: if the argv[1] != -n treat is a file input*/
		if (!strcmp(argv[1], "-n"))
			fprintf(stderr, "usage: fw [-n num] [ file1 [ file2 [..]]]\n");
		/*case 2.2: if the argv[1] is anything other than -n treat it as a file**/
		else
		{

			if ((fp = fopen(argv[1], 'r')))
			{
				while (wordsize != -1)
				{
					wordsize = bufferinput(fp, word, &arraysize);
					if (wordsize != EOF && wordsize != NULL)
					{
						root = insertNode(root, word);
					}
				}
			}
			else
			{ /*else file ptr null - something wrong with the file*/
				int m = 1;
				while (m < argc)
				{
					fp = fopen(argv[m], 'r') while (wordsize != -1) if (fp = NULL)
					{
						fprintf(stderr, "usage unable to open file error");
					}
					{
						wordsize = bufferinput(fp, word, &arraysize);
						if (wordsize != EOF && wordsize != NULL)
						{
							root = insertNode(root, word);
						}
					}
					m++
				}
				ptrArry = addToAddrNodeArr(root, numOfNodes);
				qsort(ptrArry, numOfNodes, sizeof(ptrArry[0]), comparator);
				if (TopWords > numOfNodes)
				{
					TopWords = numOfNodes;
				}
				readOutWords(TopWords, numOfNodes, ptrArry);
				break;
			}
		}
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
			if (wordsize != EOF && wordsize != NULL)
			{
				root = insertNode(root, word);
			}
		} /*stuff read in now need to do stuff*/
		ptrArry = addToAddrNodeArr(root, numOfNodes);
		qsort(ptrArry, numOfNodes, sizeof(ptrArry[0]), comparator);
		if (TopWords > numOfNodes)
		{
			TopWords = numOfNodes;
		}
		readOutWords(TopWords, numOfNodes, ptrArry);
		break;
	}
	else
	{
		int m = 1;
		while (m < argc)
		{
			fp = fopen(argv[m], 'r') while (wordsize != -1) if (fp = NULL)
			{
				fprintf(stderr, "usage unable to open file error");
			}
			{
				wordsize = bufferinput(fp, word, &arraysize);
				if (wordsize != EOF && wordsize != NULL)
				{
					root = insertNode(root, word);
				}
			}
			m++
		}
		ptrArry = addToAddrNodeArr(root, numOfNodes);
		qsort(ptrArry, numOfNodes, sizeof(ptrArry[0]), comparator);
		if (TopWords > numOfNodes)
		{
			TopWords = numOfNodes;
		}
		readOutWords(TopWords, numOfNodes, ptrArry);
		break;
	}

default:

	if (!strcmp(argv[1], "-n") && isdigit(argv[2]))
	{
		int m = 3;
		TopWords = (int)argv[2];
		while (m < argc)
		{
			fp = fopen(argv[m], 'r') while (wordsize != -1) if (fp = NULL)
			{
				fprintf(stderr, "usage unable to open file error");
			}
			{
				wordsize = bufferinput(fp, word, &arraysize);
				if (wordsize != EOF && wordsize != NULL)
				{
					root = insertNode(root, word);
				}
			}
			m++
		}
		ptrArry = addToAddrNodeArr(root, numOfNodes);
		qsort(ptrArry, numOfNodes, sizeof(ptrArry[0]), comparator);
		if (TopWords > numOfNodes)
		{
			TopWords = numOfNodes;
		}
		readOutWords(TopWords, numOfNodes, ptrArry);
		break;
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
					if (wordsize != EOF && wordsize != NULL)
					{
						root = insertNode(root, word);
					}
				}
			}
			else
			{
				fprintf(stderr, "usage No such file or directory\n The top 10 words (out of 0 are:\n");
			}
		}
		ptrArry = addToAddrNodeArr(root, numOfNodes);
		qsort(ptrArry, numOfNodes, sizeof(ptrArry[0]), comparator);
		if (TopWords > numOfNodes)
		{
			TopWords = numOfNodes;
		}
		readOutWords(TopWords, numOfNodes, ptrArry);
		break;
	}return 0;
}
