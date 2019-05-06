#include "huffmanTree.h"
#include "freqTable.h"
#include <stdint.h>
#include "readLongLine.h"
#include "hdecode.h"
#define MASK_MSB 0x80


int decodeHeader(int inFd, Node **huffmanTree, int **ft)
{
    int numUniqueOfChars;
    numUniqueOfChars = 0;

    uint32_t i;

    uint8_t c;

    *ft = buildFreqTable();

   /* Step 1 - read the number of unique characters*/
    if((read(inFd, &i, sizeof(int))) <= 0)
    {
        /*perror("error reading file\n"); /*1st argument permission denied*/
      /*  exit(-1);*/
    }

    numUniqueOfChars = (int)i;
   /*Step 2 - read in each character store in freqTable
    * if step 1 suceeded the file should be at the first char
    * */

   /*read in sets of 5 bytes*/
    for (i= 0; i < numUniqueOfChars; i++) {

        /*Step 3 -  read the character*/
        if((read(inFd, &c, sizeof(uint8_t))) <= 0)
        {
            perror("error reading file\n"); /*1st argument permission denied*/
            exit(-1);
        }

        uint32_t ft_adder=0;
        /* Step 4 - read the corresponding frequency of that character*/
        if((read(inFd, &ft_adder, sizeof(uint32_t))) <= 0)
        {
            perror("error reading file\n"); /*1st argument permission denied*/
            exit(-1);
        }

        printf("error for: %c think %d\n", c , ft_adder);
        ft[0][c] = ft_adder;

    }


    printFreqTable(*ft);

   /*step 5 - build huffmanTree from freqTable*/
   if(*ft != NULL) {
       *huffmanTree = buildHuffTree(*ft);
   }


   structure(*huffmanTree, 0);
   /*printFreqTable(*ft);*/

   return numUniqueOfChars;

}

/*decode left to right reading body 1000 0000 = 0x80*/

/*Call after header, so left off at the first part of the body*/
void decodeBody(int inFd, int outFd, int numTotalChars, Node *huffmanTree)
{

    /*Step 1 - read in the file from where left off
     *
     *         Decode while reading keep track of number of chars read
     * */
    /*initalize the buffer*/


    int indexBuff;

    Node *root = huffmanTree;


    buff = read_long_line(inFd);
    int i;

    int numCodes = 0;
    uint8_t byte = buff[0];
    /*Step 2 - go through the buffer - EOF indicator is for this buffer is '\0'*/
    for (i = numTotalChars, indexBuff = 0; i> 0; i--, huffmanTree = root)
    {
        /*Step 3 - transverse the tree until a char is found.
         *
         * - shift that current that one encodeod char till find a matching
         * - if leaf found jump out of the loop , start from root
         *
         * */

       while(!isLeaf(huffmanTree))
       {

           printf("debugging huffmanTree -> c %c\n", huffmanTree->c);
           /*mask from left to right is x000 1110, is x a 1 or 0? */
          if(buff[indexBuff] & MASK_MSB == 0x80 ) {
              huffmanTree = huffmanTree->left_child;
          }


          else if (buff[indexBuff] && MASK_MSB == 0x00) {
              huffmanTree = huffmanTree->right_child;
          }
          /*shift that buffer encoded char that is one byte 0001 _ 1110 buff[indexBuff]*/
          buff[indexBuff] = buff[indexBuff] << 1;

          /*incrment numCodes - reset once new chacter has been found*/
          numCodes++;


          /*if the numCodes seen in a char is 8 then move on to the next byte*/
          if(numCodes == 8)
          {
            indexBuff++;
            numCodes=0;
          }

       }


        /*Step 4 - after reading converting the code to characters write it out*/
       if (write(outFd, &huffmanTree->c, sizeof(char)) <= 0)
           perror("write error\n");


    }

}






void decodeFile(int inFd, int outFd, Node **huffmanTree, int **ft)
{

    int numUniqueChars =  decodeHeader(inFd, huffmanTree, ft);
    int i;

    /*we need to write decoded msg to the outfile*/
    decodeBody(inFd,outFd,totChars(*ft), *huffmanTree);


}

int totChars(int *ft)
{
    int tot = 0;

    if(ft == NULL)
        return 0;

    int j;

    for (j = 1; j < ALPHABET_SIZE; j++) {
        if (ft[j] > 0)
            tot += ft[j];
    }
    return tot;
}


int main(int argc, char *argv[])
{

    int inFd, outFd, inSavedFd, outSavedFd, *ft;
    char c;
    Node *root;
    uint32_t numOfChars;



    int readStdIn = argc == 1 || (argc == 2 && strcmp(argv[1] ,"-") == 0);

    /*Case 1 - if there is no arguments then read from stdin
     *          also output to stdout*/

    if(readStdIn)
    {

       /*check if can open file*/
       if((inFd = open(argv[1], O_RDONLY))==-1)
       {
            perror(argv[2]); /*1st argument permission denied*/
            exit(-1);
       }


    }else{ /*read from file*/

        /* if there are too many arguments throw an error*/
        if(argc > 3)
        {
            fprintf(stderr, "usage: ./hdecode infile [ ( infile | - ) [ outfile ] ]\n");
            exit(-1);
        }


        if((inFd = open(argv[1], O_RDONLY)) == -1 )
        {
            perror(argv[2]); /*1st argument permission denied*/
            exit(-1);
        }

        /*If right amount of arguments continue and check if we can open that file */
        if((outFd = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0700)) == -1 )
        {
            perror(argv[2]); /*1st argument permission denied*/
            exit(-1);
        } /*read from stdout*/
           /* outFd = 1;*/




        decodeFile(inFd,outFd, &root, &ft);
    }




    return 0;
}