#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "fw.h"


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



