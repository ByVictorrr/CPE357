#include <stdio.h>
#include <stdlib.h>

#define ALPHABET_SIZE 256

enum boolean{FALSE,TRUE};

typedef struct huffmanEncoder{
	


}HuffmanEncoder;



Node *buildHuffTree(int *freq)
{
	pQueue *q = (pQueue)malloc(sizeof(qQueue));

	int i;
	/* If that characater has freqency greater than 0 add to pqueeu*/
	for (i = 0; i<ALPHABET_SIZE; i++)
		if(freq[i] > 0)
			q.add();
}


/*buildFrequencyTable: takes in a string and relates
 *
 */
int *buildFreqeuncyTable(char *data)
{
	/*make a freq table for each character that we are encoding*/
	int *freq = (int *)calloc(ALPHABET_SIZE,sizeof(int));
	int i;
	/*go until EOF*/
	for (;*data != EOF; data++)
	{
		/*every time come across that character incrment freq*/
		freq[*data]++;
	}
	return freq;
}


typedef struct node{
	char character;
	int frequency;
	Node *left_child;
	Node *right_child;
}Node;


/*isLeaf: inputs a node and tells you if a node is a leaf*/
int isLeaf(Node *n)
{
	if (n->left_child == NULL && n->right_child == NULL)
		return TRUE;
	return FALSE;
}




int main()
{

}
