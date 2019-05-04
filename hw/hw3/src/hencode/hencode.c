#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>

#include "pQueue.h"
#include "lookUpTable.h"
#include "huffmanTree.h"
#include "freqTable.h"



#define BUFSIZE 210
#define ALPHABET_SIZE 256
#define MASK 1


extern int numUniqueChar;
extern enum boolean;

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

/*packing the body into a smaller */

uint8_t *generateBody(struct lookUpTable *table, int codeLength)
{

  uint8_t *encoded = (uint8_t*)malloc(codeLength*sizeof(uint8_t));
  /*mask 1's an 0's from char to int*/
  int i;
  uint8_t temp = 0;
  char *conv;
  /*iterate through whole table*/
  for(i = 0; i<ALPHABET_SIZE; i++)
  {

      /*conv = non null codes*/
      if((conv = table[i].code) != NULL) {

          /*go through that strings chars -> integer*/
          int j;
          for (j = 0; j < strlen(table[i].code); ++j) {

                /*if end of that string*/
                *encoded += (int)pow(2,j) * (conv[0] & MASK) ;
                *conv = *conv >> 1;

                /*if encoded reaches its maximum*/
                if(*encoded==255)
                {
                    encoded++;
                }

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
    int i;
    for (i = 0; i < numUniqueChars; ++i) {
       printf("| %c | %lu |", (char)header[i].character, header[i].frequency) ;
    }
}

/*=================================================================*/







 int getCodeLen(struct lookUpTable *table)
 {
    int codeLen = 0;
    int j;
    for ( j = 0; j < ALPHABET_SIZE; ++j)
        if (table[j].code != NULL)
            codeLen += strlen(table[j].code);
        return codeLen;
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
    ft = buildFreqTable(string);

    printFreqTable(ft);

   /*==============Test 2- build huffman tree============*/

   Node *head = buildHuffTree(ft);
	structure(head,0);

/*=====================test 3 - Build look up character -> codes table===========*/

struct lookUpTable *table = buildLookUpTable(head);

printf("table %s\n", (table)->code);

int j;
    for ( j = 0; j < ALPHABET_SIZE; ++j) {
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
