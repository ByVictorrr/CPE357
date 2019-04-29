#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "pQueue.c"

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
    listNode *priorityQ = (pQueue)malloc(sizeof(qQueue));

    int i;

    for (i = 0; i<ALPHABET_SIZE; i++)
        if(freq[i] > 0)
        {
            /*creat a new head to pqueue*/
            pushNew(&priorityQ,c,freqTable[i]);
        }

        if (priorityQ.size() == 1)
        {


        }
        while(priority->size() > 1)
        {
           Node * right = poll(&priorityQ);
           Node * left = poll(&priorityQ);
           /*wrap parent in a listNode*/
           listNode parent = newListNode('\0', right->freq+left->freq,left,right);

           pushNode(&priorityQ, parent);

        }
}

 /*
int isLeaf(Node *n)
{
	if (n->left_child == NULL && n->right_child == NULL)
		return TRUE;
	return FALSE;
}
*/
int main(int argc, char *argv[])
{

    int fd, n;
    char buf[BUFSIZE];
    int *ft;

   if((fd = open(argv[1], O_RDONLY | O_WRONLY, 0777)) == -1)
   {
       exit(-1);
   }
    /*read from ft*/
   while((n=read(fd, buf, BUFSIZE)) > 0) {

       ft = buildFreqeuncyTable(buf);
       printf("%s",buf);

   }
    printf(" size of f['a'] is %d\n",ft['a']);

    printf(" size of ft['d'] is %d\n",ft['d']);

    printf(" size of ft['f'] is %d\n",ft['f']);
    free(ft);

    return 0;
}
