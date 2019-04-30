#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "pQueue.c"
#include "lookUpTable.c"

#define BUFSIZE 210
#define ALPHABET_SIZE 256

enum boolean{FALSE,TRUE};

typedef struct huffmanEncoder{


}HuffmanEncoder;




/*buildFrequencyTable: takes in a string and relates
 *
 */
int *buildFreqeuncyTable(char *data)
{
	/*make a freq table for each character that we are encoding*/
	int *freq = (int *)calloc(ALPHABET_SIZE,sizeof(int));
	int i;

	for(i = 0; i<ALPHABET_SIZE; i++)
    {
	    freq[i] = 0;
    }
	/*go until EOF*/
	for (;*data != EOF; data++)
	{
		/*every time come across that character incrment freq*/
		freq[*data]++;
	}
	return freq;
}



Node *buildHuffTree(int *freqTable)
{
    listNode *priorityQ = NULL;

    int i;

    for (i = 1; i<ALPHABET_SIZE; i++)
        if(freqTable[i] > 0)
        {
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
           Node * right = poll(&priorityQ);
           Node * left = poll(&priorityQ);
           /*wrap parent in a listNode*/
           listNode *parent = newListNode('\0', right->freq+left->freq,left,right);

           pushNode(&priorityQ, parent);

        }


        return poll(&priorityQ);
}


void inorder(Node *root)
{

   if(root == NULL)
       return;

   inorder(root->right_child);
   printf("binary tree node with value char %c and data %d\n", root->c, root->freq);
   inorder(root->left_child);
}


void printFreqTable(int *freqTable)
{
    for (int i = 1; i < ALPHABET_SIZE; i++)
    {
        if (freqTable[i] >0)
            printf("freqTable[ %c ] = %d\n", (char)i, freqTable[i]);
    }
}


int isLeaf(Node *n)
{
	if (n->left_child == NULL && n->right_child == NULL)
		return TRUE;
	return FALSE;
}


struct lookUpTable *buildLookUpTable(Node *root)
{
    struct lookUpTable *table =
            (struct lookUpTable*)malloc(sizeof(struct lookUpTable));

    initLookUpTable(root, "", table);

    return table;
}

void initLookUpTable(Node *root, char *s, struct lookUpTable **table)
 {

    if(!isLeaf(root))
    {
        buildHuffTree(root->left_child, s+'0', table)
        buildHuffTree(root->left_child, s+'1', table);
    }
 }

int main(int argc, char *argv[])
{

    int fd, n;
    char buf[BUFSIZE], c;
    int *ft;
    int i = 0;


    /*===========Test 1- test read=====================*/
    /*n=read(0,buf,sizeof(buf));*/

    char string[] = "fuckmezzfluukad";
    ft = buildFreqeuncyTable(string);

    printFreqTable(ft);

   /*==============Test 2- build huffman tree============*/

   Node *head = buildHuffTree(ft);
  inorder(head);




  free(head);
    free(ft);


    return 0;
}
