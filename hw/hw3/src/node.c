#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "node.h"

typedef struct node{
    char character;
    int freq;
    Node *left_child;
    Node *right_child;
}Node;



Node *newNode(char c, int freq);
Node *insertNode(Node *root, char c, int freq);

Node *searchNode(Node *root, char c);
void freeNode(Node *root);

Node *newNode(char c, int freq)
{
	 Node *new;
	 if ((new = (Node*)malloc(sizeof(Node))) == NULL)
	     return NULL;

	 new->freq = freq;
	 new->c = c;

	new->left_child = NULL;
	new->right_child = NULL;

	return new;
}



/* insertNode: if (word is lexicographically less than root-> word stored in left child*/
Node *insertNode(char c, int freq)
{

		return newNode(k);

	return root;
}

/*returns Null if not found*/
Node *searchNode(Node *root, char *word )
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



