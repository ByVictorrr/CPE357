#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>




/*========================Node=======================================*/
typedef struct node{
    char c;
    int freq;
    struct node *left_child;
    struct node *right_child;
}Node;


Node *newNode(char c, int freq, Node *left, Node *right)
{
	 Node *new;
	 if ((new = (Node*)malloc(sizeof(Node))) == NULL)
	     return NULL;

	 new->freq = freq;
	 new->c = c;

	new->left_child = left;
	new->right_child = right;

	return new;
}
