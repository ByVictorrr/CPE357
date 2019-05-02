#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include "pQueue.c"
#include "lookUpTable.c"
#include <string.h>

#define BUFSIZE 210
#define ALPHABET_SIZE 256
#define MASK 1
int numUniqueChar = 0;

int codeLength;
enum boolean{FALSE,TRUE};

/*========================Encoded data===================================*/

/*Should be 5 bytes*/
typedef struct charEncodeFormat
{
	uint8_t character; 
	uint32_t frequency; /*number of chars in freq table*/
}fieldHeader;

typedef struct huffmanEncoder{
		fieldHeader *header;
		uint32_t header_size;  /*its fixed */
		uint8_t *body;
}HuffmanEncoder;

/*returning the body of the string encodded*/
uint8_t *generateBody(struct lookUpTable *table, int codeLength)
{

  uint8_t *encoded = (uint8_t*)malloc(codeLength*sizeof(uint8_t));
  /*mask 1's an 0's from char to int*/
  int i;
  uint8_t temp = 0;
  char *conv;
  for(i = 0; i<ALPHABET_SIZE; i++)
  {
      if((conv = table[i].code) != NULL) {
          for (int j = 0; j < strlen(table[i].code); ++j) {
                if(j==7)
                {
                   encoded++; /* go get more data*/
                }
                *encoded = *encoded << (conv[j] & MASK);
              printf("shift left for %c, %d\n", (char)i, *encoded );

          }

          printf("new char\n");

      }

        /*want to mask then shift each value to get conversion of char -> integer*/
  }


    return encoded;
}


/*This method gives the string wit the codes*/
fieldHeader *generateHeader(int *ft, int numUniqueChars)
{ 
	/*allocating for header*/
   fieldHeader *header = (fieldHeader*)malloc(sizeof(fieldHeader)*numUniqueChars);
	int i;
	int header_inc = 0;
   for ( i=1; i<ALPHABET_SIZE; i++)
   {
       if(ft[i] > 0) {
           /*insert into header*/
           header[header_inc].frequency = (uint32_t) ft[i];
           header[header_inc].character = (uint8_t) i;
           header_inc++;
       }

   }
   return header;
}



void printFieldHeader(fieldHeader *header, int numUniqueChars)
{
    for (int i = 0; i < numUniqueChars; ++i) {
       printf("| %c | %lu |", (char)header[i].character, header[i].frequency) ;
    }
}

/*=================================================================*/






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

void initLookUpTable(Node *node, char *s, int top ,struct lookUpTable **table)
 {
    if(isLeaf(node))
    {

		(*table)[node->c].code = (char*)malloc(sizeof(char)*ALPHABET_SIZE);

		strcpy((*table)[node->c].code,s);

	}else{
			printf("hi\n");
			
				s[top] = '0';
				initLookUpTable(node->left_child, s, top+1, table);
				s[top] = '1';
				initLookUpTable(node->right_child,s, top+1, table);
			}


 }

 int getCodeLen(struct lookUpTable *table)
 {
    int codeLen = 0;
    int j;
    for ( j = 0; j < ALPHABET_SIZE; ++j)
        if (table[j].code != NULL)
            codeLen += strlen(table[j].code);
        return codeLen;
 }

struct lookUpTable *buildLookUpTable(Node *root)
{
    struct lookUpTable *table = (struct lookUpTable*)malloc(sizeof(struct lookUpTable)*ALPHABET_SIZE);
    char *s=(char*)calloc(ALPHABET_SIZE,sizeof(char));
    *s = EOF;
    initLookUpTable(root,s, 0 ,&table);
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

	char string[] = "vvica";
    ft = buildFreqeuncyTable(string);

    printFreqTable(ft);

   /*==============Test 2- build huffman tree============*/

   Node *head = buildHuffTree(ft);
	structure(head,0);

/*=====================test 3 - Build look up character -> codes table===========*/

struct lookUpTable *table = buildLookUpTable(head);

printf("table %s\n", (table)->code);

    for (int j = 0; j < ALPHABET_SIZE; ++j) {
        if(table[j].code != NULL)
       printf(" code table[ %c ] = %s\n",(char)j ,table[j].code);
    }

/*=======================test 4 - print header=========*/

generateBody(table,getCodeLen(table));
    fieldHeader *header = generateHeader(ft, numUniqueChar);
	/*printFieldHeader(header,numUniqueChar);*/


	/*printf("get codes : %d\n", codeLength);*/

/*=================================================*/
  free(header);
  free(head);
    free(ft);


    return 0;
 }
