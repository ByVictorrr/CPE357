#include "../hencode/huffmanTree.h"
#include "../hencode/freqTable.h"
#include "readLongLine.h"

#define RD_MODE 0444
enum boolean{FALSE, TRUE};
extern char *buff;

uint32_t totalNumberOfChars;

int decodeHeader(int inFd, Node **huffmanTree, int *ft)
{
    int numUniqueOfChars;
    numUniqueOfChars = 0;

    uint32_t i;

    uint8_t c;

   /* Step 1 - read the number of unique characters*/
    if((read(inFd, &numUniqueOfChars, sizeof(int))) <= 0)
    {
        perror("error reading file\n"); /*1st argument permission denied*/
        exit(-1);
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
        if((read(inFd, &ft[c], sizeof(uint32)t)) <= 0)
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


/* Might need to switch to a dynamic ref b limited space*/
uint32_t getTotalNumberOfChar(int *ft)
{
    int i;

    uint32_t tot

    tot = 0;

   if (ft != NULL)
   {
       for (i = 0; i < ALPHABET_SIZE; i++) {
           tot += freq[c];
       }

       return tot;
   }

   return 0;
}





/*Call after header, so left off at the first part of the body*/
void decodeBody(int inFd, int outFd, int numUniqueChars, Node *huffmanTree)
{

    /*Step 1 - read in the file from where left off
     *
     *         Decode while reading keep track of number of chars read
     * */
    if(read(inFd, &buff))
}





int main(int argc, char *argv[])
{

    int inFd, outFd, inSavedFd, outSavedFd, *ft;
    char c;
    Node *head;
    struct lookUpTable *codeTable;
    uint32_t numOfChars;
    fieldHeader *header;



    enum boolean readStdIn = argc == 1 || (argc == 2 && strcmp(argv[1] ,"-") == 0);

    /*Case 1 - if there is no arguments then read from stdin
     *          also output to stdout*/
    if(readStdIn)
    {
       /*check if can open file*/
       if((inFd = read(argv[1], RD_ONLY, RD_MODE))==-1)
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

        /*If right amount of arguments continue and check if we can open that file */
        if((outFd = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0700)) == -1 )
        {
            perror(argv[2]); /*1st argument permission denied*/
            exit(-1);
        }else /*read from stdout*/
            outFd = 1;
    }


    /*Case 2 - if argv[1] is [ (infile) | - ]
     * if infile then use that for the input
     * if - then use stdin for read in
     */
    if (argc > 1)
    {

    }
    /*Case 3 - if argc is greater than 2 then read in file

    if(argc == 1 || argc > 3)
    {
        fprintf(stderr, "usage: hencode infile [ outfile ]\n");
        exit(-1);
    }


    /*Therefor there is more than 1 argument and less than or equal to 3*/
    if((inFd = open(argv[1], O_RDONLY)) == -1)
    {
        perror(argv[1]); /*1st argument permission denied*/
        exit(-1);

    }

    /*Step 0 - build freq table*/
    ft = buildFreqTable();

    /*Step 1 - read one char at a time an insert at time in ft*/
    while(read(inFd, &c, sizeof(char)))
    {
        insertToFreqTable(&ft, c);
    }
    /*Step 2 - build code huffman tree*/
    head = buildHuffTree(ft);
    /*structure(head,0);

    /*Step 3 - build code look up table c->code*/
    codeTable = buildLookUpTable(head);

    /*printf("num of codes: %d\n", numBitsOfCode(codeTable));*/

    /*if argc = 3  just switch file descriptors*/

    /*if there is a outfile listed*/
    if( argc == 3 ) {

        if((outFd = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0700)) == -1)
        {
            perror(argv[2]); /*1st argument permission denied*/
            exit(-1);
        }

        outSavedFd = dup(1); /*save stdout */
        dup2(outFd, 1);

    }

    /*| num of chars = numofUniqueChar|[ c1 | count of c1 ... | cn | count of cn|]  = feild header */
    numOfChars = (uint32_t)numUniqueChar;

    /*Step 4 - build header table */
    header = generateHeader(ft, numOfChars);

    int i, n = 1;

    /*write header size then one header field at a time*/
    for(i =0 ; i< numOfChars+1 && n > 0; i++){
        if(i == 0) /*first write - write number of chars*/
            n = write(1, &numOfChars,  sizeof(uint32_t));
        else{  /*else write the fieldHeader */
            n = write(1, &header->character, sizeof(char));
            n = write(1, &header->frequency, sizeof(int));
            header++;
        }

    }

    lseek(inFd, 0,  0); /*start reading at the begging*/

    /*the max number numCodes can represent if there all 1's - 2^{numcodes}  + (1) plus if we need to pad 00's*/

    uint8_t output;

    int divisablity_by_8;

    /*Step 5 - build body (just read the file one more time and translate the code)*/
    while(read(inFd, &c, sizeof(uint8_t)) > 0) {
        /*codeTable[c].code - the code corresponding to char c*/
        divisablity_by_8 = writeBits(c, strlen(codeTable[c].code), &output, codeTable);
    }

    /*
    /*Step 6 - check if final add output if no div by 8*/
    printf("div 8 check %d", divisablity_by_8);
    if(divisablity_by_8 != 8)
    {
        /*shift it to fill in missing zeros*/
        output = output << (8 - divisablity_by_8);
        write(1, &output, sizeof(uint8_t));
    }

    /*restore stdout*/
    if(argc == 3)
    {
        dup2(outSavedFd, 1);
        close(outFd);
    }


    freeEveryThing(head, codeTable, ft, header);
    /*step 3 - write to the header (read from input once again - decode the body)*/


    return 0;
}