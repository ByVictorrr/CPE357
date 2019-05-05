#include "huffmanTree.h"

numUniqueChar = 0;


Node *buildHuffTree(int *freqTable)
{
    listNode *priorityQ = NULL;

    int i;

    for (i = 1; i<ALPHABET_SIZE; i++)
        if(freqTable[i] > 0)
        {
            if (i == (int)'\n')
            {
                printf("hi im new line");
            }
            else {
                numUniqueChar++;
                /*creat a new head to pqueue*/
                pushNewNode(&priorityQ, i, freqTable[i]);
            }

        }
		transverse(priorityQ);
        /*if there is only one character in the table*/
        if (size(priorityQ) == 1)
        {
            pushNewNode(&priorityQ, '\0', 1);

        }
        int j;
        j = 0;
        /*while there is more than one character in the pque*/
        while(size(priorityQ) > 1)
        {
           Node * left = poll(&priorityQ);
           Node * right = poll(&priorityQ);
           /*wrap parent in a listNode*/
           listNode *parent = newListNode('@', right->freq + left->freq, left, right);

            printf("ith insertion %d \n",  j++);
           inorder(parent->curr);


           pushNode(&priorityQ, parent);

        }

        Node *root = poll(&priorityQ);


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
