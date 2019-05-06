#include "huffmanTree.h"
#include "freqTable.h"
#include "readLongLine.h"
#include <stdint.h>

#define RD_MODE 0444
extern char *buff;

uint32_t totalNumberOfChars;

int decodeHeader(int inFd, Node **huffmanTree, int **ft)
{
    int numUniqueOfChars;
    numUniqueOfChars = 0;

    uint32_t i;

    uint8_t c;

    *ft = buildFreqTable();

   /* Step 1 - read the number of unique characters*/
    if((read(inFd, &numUniqueOfChars, sizeof(int))) <= 0)
    {
        perror("error reading file\n"); /*1st argument permission denied*/
      /*  exit(-1);*/
    }

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

        /* Step 4 - read the corresponding frequency of that character*/
        if((read(inFd, &ft[c], sizeof(uint32_t))) <= 0)
        {
            perror("error reading file\n"); /*1st argument permission denied*/
            exit(-1);
        }

    }
   /*step 5 - build huffmanTree from freqTable*/
   if(ft != NULL) {
       *huffmanTree = buildHuffTree(ft);
   }
   return numUniqueOfChars;

}








/*Call after header, so left off at the first part of the body*/
void decodeBody(int inFd, int outFd, int numTotalChars, Node *huffmanTree)
{

    /*Step 1 - read in the file from where left off
     *
     *         Decode while reading keep track of number of chars read
     * */

    int indexBuff;

    Node *root = huffmanTree;

    if(read(inFd, &buff, MAXCHAR) <= 0)
    {
       /*throw error s*/
       perror("error reading file\n"); /*1st argument permission denied*/
            exit(-1);
    }

    int i;
    /*Step 2 - go through the buffer - EOF indicator is for this buffer is '\0'*/
    for (i = numTotalChars, indexBuff = 0; i> 0; i--, huffmanTree = root)
    {
        /*Step 3 - transverse the tree until a char is found.
         *
         * - incrment the buffer each time until a char is found
         * - if leaf found jump out of the loop , start from root
         *
         * */
       while(!isLeaf(huffmanTree))
       {
           /*if the current byte is 0 */
          if(buff[indexBuff] == '0')
             huffmanTree = huffmanTree->left_child;

          else if (buff[indexBuff] == '1')
              huffmanTree = huffmanTree->right_child;

          indexBuff++;
       }

        /*Step 4 - after reading converting the code to characters write it out*/
       if (write(outFd, &huffmanTree->c, sizeof(char)) <= 0)
           perror("write error\n");


    }


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




void writeCode(int inFd, int outFd, Node **huffmanTree, int **ft)
{

    int numUniqueChars =  decodeHeader(inFd, huffmanTree, ft);
    int i;

    /*we need to write decoded msg to the outfile*/
    decodeBody(inFd,outFd,totChars(*ft), huffmanTree);


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
       if((inFd = read(argv[1], O_RDONLY, RD_MODE))==-1)
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


        if((inFd = open(argv[1], O_CREAT|O_WRONLY|O_TRUNC, 0700)) == -1 )
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




        writeCode(inFd,outFd, &root, &ft);
    }




    return 0;
}