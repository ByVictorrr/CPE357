#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "bst.h"
#include "bufferinput.h"

#define SIZE 5

int numOfNodes=0;


int main(int argc, char*argv[])
{
	FILE *fp = fopen(argv[1]);
	
	struct node *root = NULL;
	char *words[SIZE] = {"victor","marilyn","victor","zebra","high"};
	int i = 0;

	while ( (c = getc(fp)) != EOF)
	{
		root = insertNode(root, words[i]);
	}	
	inOrder(root);
	
	freeTree(root);
	return 0;

}

struct node ** arrOfAddress(struct node *root, int numOfNodes , struct node **arr)
{
	w
	//Base case when reached a leaf
	if(root == NULL)
		return root;
	//General case
	else
		inOrder(root->left_child);
		printf("word: %s, wordCount: %d\n", root->word, root->wCount);
		inOrder(root->right_child);

}

}
void freeNode(struct node *root)
{
	if(!root)
		return;
	free(root->word);
	free(root);
}
void freeTree(struct node *root)
{
	//Base case until root == NULL
	if(root == NULL)
		return;
	else{
		freeTree(root->left_child);
		printf("freed : %s\n", root->word);
		freeNode(root);
		freeTree(root->right_child);
		}
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



