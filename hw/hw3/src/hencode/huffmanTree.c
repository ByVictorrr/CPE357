#include "huffmanTree.h"

numUniqueChar = 0;


Node *buildHuffTree(int *freqTable)
{
    listNode *priorityQ = NULL;

    int i;

    for (i = 1; i<ALPHABET_SIZE; i++)
        if(freqTable[i] > 0)
        {
			numUniqueChar++;
            /*creat a new head to pqueue*/
            pushNewNode(&priorityQ, i ,freqTable[i]);

        }
        /*if there is only one character in the table*/
        if (size(priorityQ) == 1)
        {
            pushNewNode(&priorityQ, '\0',1);

        }
        /*while there is more than one character in the pque*/
        while(size(priorityQ) > 1)
        {
            printf("transversing\n");
           Node * right = poll(&priorityQ);
           Node * left = poll(&priorityQ);
           /*wrap parent in a listNode*/
           listNode *parent = newListNode('\0', right->freq + left->freq, left , right );
           pushNode(&priorityQ, parent);

        }

        Node *root = poll(&priorityQ);

        codeLength = root->freq;

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
