#include "huffmanTree.h"



Node *buildHuffTree(int *freqTable)
{
    listNode *priorityQ = NULL;
    Node *root = NULL;
    int i;

    for (i = 0; i<ALPHABET_SIZE; i++) {
        if (freqTable[i] > 0) {
            /*creat a new head to pqueue*/

            pushNewNode(&priorityQ, (unsigned char)i, freqTable[i]);
        }
    }
        
/*====================Special cases ===============================*/
        /*case 1 - if numUniqueChar == 0*/
        if (priorityQ == NULL)
            return NULL;

		/*Case 2 - if numUniqueChar == 1*/
		if(size(priorityQ) == 1)
        {
			poll(&priorityQ);
			return NULL;
		}
/*=================================================================*/

        /*while there is more than one character in the pque*/
        while(size(priorityQ) > 1)
        {
           Node * left = poll(&priorityQ);
           Node * right = poll(&priorityQ);
           /*wrap parent in a listNode*/
           listNode *parent = newListNode('\0', (unsigned int)right->freq + (unsigned int)left->freq, left, right);
           pushNode(&priorityQ, parent);
        }

        root = poll(&priorityQ);
        numCodes = root->freq;

        return root;
}


void inorder(Node *root)
{

   if(root == NULL)
       return;

   inorder(root->left_child);
   printf("binary tree node with value char %c and freq %d\n", root->c, root->freq);
   inorder(root->right_child);
}


int isLeaf(Node *n)
{
	if (n->left_child == NULL && n->right_child == NULL)
		return TRUE;
	return FALSE;
}

void freeHuffmanTree(Node *tree)
{
    if(tree == NULL)
        return;
    else{
        freeHuffmanTree(tree->left_child);
        freeHuffmanTree(tree->right_child);
        free(tree);
    }
}
