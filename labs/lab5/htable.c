#include "htable.h"


void freeEveryThing(Node *huffmanTree, struct lookUpTable *table, int *freqTable) {
    freeFreqTable(freqTable);
    freeLookUpTable(table);
    freeHuffmanTree(huffmanTree);

}

int main(int argc, char *argv[])
{

    int inFd, *ft = NULL;
    unsigned char c;
    Node *head = NULL;
    struct lookUpTable *codeTable = NULL;
    uint32_t numOfChars;
    uint8_t output;
    uint32_t output_for_nothing = 0;
    int i, n = 1;

    if(argc == 1 || argc > 3)
    {
        fprintf(stderr, "usage: ./hencode <infile> \n");
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
    while(read(inFd, &c, sizeof(unsigned char)))
    {
        insertToFreqTable(&ft, c);
    }

    /*CURRENTLY KNOW HOW MANY UNIQUE CHARS THERE ARE*/
    if(numUniqueChar >= 2 )
    {
        /*case 2 - build tree if there is at least 2 char*/
        head = buildHuffTree(ft);
        /*case 3 - build look up table if there are at least two char*/
        if((codeTable = buildLookUpTable(head)) == NULL)
            exit(-1);
    }

		printLookUpTable(codeTable);



       freeEveryThing(head, codeTable, ft);


		close(inFd);


    /*step 3 - write to the  (read from input once again - decode the body)*/


    return 0;
 }
