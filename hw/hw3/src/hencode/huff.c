#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "pQueue.c"
#include "lookUpTable.c"
#include <string.h>
#define BUFSIZE 210
#define ALPHABET_SIZE 256

enum boolean{FALSE,TRUE};

typedef struct huffmanEncoder{


}HuffmanEncoder;

const char * one = "1";
const char *zero = "0";




char *generateEncodedData(char *data, struct lookUpTable * table )
{
   char *encoded = (char *)malloc(sizeof(char)*ALPHABET_SIZE);
   int i;
    for (i=0; *data; data++, encoded++) {
        encoded = table[*data].code;

    }
    return encoded;
}
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

   inorder(root->left_child);
   printf("binary tree node with value char %c and data %d\n", root->c, root->freq);
   inorder(root->right_child);
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

void initLookUpTable(Node *node, char *s, struct lookUpTable **table)
 {
    if(!isLeaf(node))
    {
        initLookUpTable(node->left_child, strcat(s,"0"), table);
        initLookUpTable(node->right_child, strcat(s,"1"), table);
    }else{
        printf("fuck %c \n,", node->c);
            (*table)[node->c].code = (char*)malloc(sizeof(char)*ALPHABET_SIZE);
            strcpy((*table)[node->c].code,s);
            free(s);
            s=(char*)malloc(sizeof(char)*ALPHABET_SIZE);
     }

 }
struct lookUpTable *buildLookUpTable(Node *root)
{
    struct lookUpTable *table = (struct lookUpTable*)malloc(sizeof(struct lookUpTable)*ALPHABET_SIZE);
    char *s = (char*)malloc(sizeof(char)*ALPHABET_SIZE);
    *s='\0';
    initLookUpTable(root,s, &table);
    return table;
}


int main(int argc, char *argv[])
{

    int fd, n;
    char buf[BUFSIZE], c;
    int *ft;
    int i = 0;


    /*===========Test 1- test read=====================*/
    /*n=read(0,buf,sizeof(buf));*/

char string[] = "aaaaaaaabcccccmmmtttttt";
    ft = buildFreqeuncyTable(string);

    printFreqTable(ft);

   /*==============Test 2- build huffman tree============*/

   Node *head = buildHuffTree(ft);
  inorder(head);

/*=====================test 3 - Build look up character -> codes table===========*/

struct lookUpTable *table = buildLookUpTable(head);

printf("table %s\n", (table+'z')->code);

    for (int j = 0; j < ALPHABET_SIZE; ++j) {
        if(table[j].code != NULL)
       printf("table[ %c ] = %s\n",(char)j ,table[j].code);
    }



  free(head);
    free(ft);


    return 0;
 }
