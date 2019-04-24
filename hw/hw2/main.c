#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "fw.h"
#define SIZE 100


int main(int argc, char *argv[])
{
	struct node *addToAddrNodeArr(struct node *root, int numOfNodes);
	int TopWords = 10;
	FILE *fp;
	int arraysize = 40;
	char *word = (char *)malloc(arraysize * sizeof(char));
	int wordsize = 0;
	struct node *root = NULL;
	struct node *ptrArry;

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

				if ((fp = fopen(argv[1], 'r')))
				{
					while (wordsize != -1)
					{
						wordsize = bufferinput(fp, word, &arraysize);
						root = insertNode(root, word);
					}

				}
				else /*else file ptr null - something wrong with the file*/
					fprintf(stderr, "usage No such file or directory\n The top 10 words (out of 0 are:\n");
				
				
				ptrArry = addToAddrNodeArr(root,numOfNodes);
				mergeSort(ptrArry,0,numOfNodes-1);
				
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
				ptrArry = addToAddrNodeArr(root,numOfNodes);
				mergeSort(ptrArry,0,numOfNodes-1);
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
				ptrArry = addToAddrNodeArr(root,numOfNodes);
				mergeSort(ptrArry,0,numOfNodes-1);
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
				ptrArry = addToAddrNodeArr(root,numOfNodes);
				mergeSort(ptrArry,0,numOfNodes-1);
			}
		}

	return 0;
}


void readOutWords(int amount, struct node *arr[])
{
    int n = 0;
    printf("these are the %d top words", amount);
    for (n = 0; n < amount; n++)
    {
        printf("%s: count: %d\n", arr[n]->word, arr[n]->wCount);
    }
}

void merge(struct node *arr[], int left, int middle, int right)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    /* create temp arrays */
    struct node *L[n1], *R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;    // Initial index of first subarray
    j = 0;    // Initial index of second subarray
    k = left; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if(L[i]->wCount > R[j]->wCount){
            arr[k]=L[i];
            i++;
        }
        else if(L[i]->wCount < R[j]->wCount){
            arr[k]=R[j];
            j++;
        }
        else if (L[i]->wCount == R[j]->wCount)
        {
            if (strcmp((L[i]->word), (R[j]->word)) == -1)
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
    }
}

    /* Copy the remaining elements of L[], if there */

int bufferinput(FILE *fp, char *word, int *arraylength)
{
    int size = 0;
    char a = 1;
        while (size <= *arraylength && a != NULL)
        {
            /*need to add typcheck for input*/

            a = fgetc(fp);
            if(size==0 && a== EOF){
                return -1;
            }
            tolower(a);
			if (61<=(int)a && a<=122 ) {/*printable characters brah*/
				word[size++] = a;
			}else
            {
                a=NULL;
            }
            
			if (size == *arraylength) {
				*arraylength += 256;
				word = (char*)realloc(word, *arraylength *sizeof(char));
			}
        }
        word[size]= NULL;
        return size; 
}
struct node *addToAddrNodeArr(struct node *root, int numNodes)
{
	struct node **stack = (struct node**)malloc(sizeof(struct node)*numNodes);
	struct node *current=root;
	struct node *nodeArry = (struct node*)malloc(sizeof(struct node)*numNodes);
	struct node *baseAddrArr = nodeArry;

	int j; //count num of nodes
	
	//Step 2 - check if root isnt null
	if(!root) return NULL;
	j=-1;
	/*Step 3 - while numnodes not equal to i */
	while(1)
	{
		/*INORDER*/

		//Step 4.1  - is current null? if it isnt add it to the stack
		if (current !=NULL)
		{
			stack[++j] = current;  //push into stack
			current = current->left_child;
		}
		//step 4.2 - go right if current == NULL
		else
		{
			if (j==-1)
				break;
			current = stack[j--];
			*nodeArry++ = *current;
			current = current->right_child;
		}

	}
	return baseAddrArr;
}
void inOrder(struct node *root)
{
	//Base case when reached a leaf
	if(root == NULL)
		return;
	//General case
	else
		inOrder(root->left_child);
		printf("word: %s, wordCount: %d\n", root->word, root->wCount);
		inOrder(root->right_child);
}
void freeTree(struct node *root)
{
	if(!root) return;
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
	 new = (struct node*)malloc(sizeof(struct node));
	 new->word=(char*)malloc(sizeof(strlen(word)+1));

	
	 //case 1: if either allocation of node or word NULL  - return NULL
	if(!new || !new -> word) 
		return NULL;

	new->wCount = 1;
	strcpy(new->word,word);
	new->left_child = NULL;
	new->right_child = NULL;
	numOfNodes++;

	return new;
}
/* insertNode: if (word is lexicographically less than root-> word stored in left child*/
struct node *insertNode(struct node *root, char*word)
{
	//Case 1: if tree is empty
	if(!root) 
		return newNode(word);
	//Case 2: if the word in current node is word inserted 
	else if (strcmp(root->word,word) == 0)
	{
		root->wCount++;
		return root;
	}
	//Case 3: if current word is less than current node then go to left node
	else if( strcmp(word, root->word) ) //if condition is negative word is lexicograpically less than root->word
		root->left_child = insertNode(root->left_child, word);
	else	
		//Case 4: if current greater than current node then go to left node
		root->right_child = insertNode(root->right_child, word);

	return root;
}
/*returns Null if not found*/
struct node *searchNode(struct node *root, char *word )
{
	//case 1: base case if node isnt foud
	if (root = NULL)
		return NULL;
	//case 2: if word is found return address
	else if (root->word == word)
		return root;
	else if(strcmp(word,root->word)) 
		return searchNode(root->left_child, word);
	else 
		return searchNode(root->right_child,word);
}



