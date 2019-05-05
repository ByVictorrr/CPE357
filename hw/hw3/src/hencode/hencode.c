#include "hencode.h"

#define BYTE 8.0
/*=================Beg of header===================================*/

/*Should be 5 bytes {count | char| }*/
typedef struct headerBits
{
    uint8_t character;
    uint32_t frequency; /*number of chars in freq table*/

}fieldHeader;

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

/*========================End of Header============================*/



/*========================Encoded data===================================*/


/*WiteBits - writes the body (code to the outfile)
 * c - character getting input to translate to its code
 * lenCode - c's length its code
 * byte - value being writen every 8 bits
 * numcodeRead - keeps track of codes read
*/

int writeBits(char c, int lenCode, uint8_t *byte, struct lookUpTable *codeTable) {
    /*just  declares and assigns once*/
    int static bits_Left_to_write = BYTE;
    char *temp;

    if (lenCode == 0)
        return 0;

    int i;
    i = lenCode;
    temp = codeTable[c].code;

    /*Step 2 - go through each characters code and mask and shift save to byte*/
    while (i > 0) {

        /*when numOfBits read in global call is div by 8 then write and clear byte*/
        if (bits_Left_to_write == 0) {
            /*When bytes has gone through 8 bytes write it*/
            write(1, byte, sizeof(uint8_t));

            /*reset the value to BYTE bits left to be written*/
            bits_Left_to_write = BYTE;
            *byte = 0;
        }


        *byte = (*byte | *temp & MASK);
        *byte = *byte << 1;
        temp++;
        i--;
        bits_Left_to_write--;
    }

	return bits_Left_to_write;
}






/*getCodeLen - returns the length of the code
 * Example: if code (in char ) is 0110 10001
 *             returns - 9 length
 */
int numBitsOfCode(struct lookUpTable *table)
 {
    int numBits = 0;
    int j;
    for ( j = 0; j < ALPHABET_SIZE; ++j)
        if (table[j].code != NULL) {
            numBits += strlen(table[j].code);
            printf("num of bits: %d, for %s\n", strlen(table[j].code), table[j].code);
        }

     printf("num of totalbits from code %d\n", numBits);
        return numBits;
 }



int main(int argc, char *argv[])
{


    int inFd, outFd, outSavedFd, *ft;
    char c;
    Node *head;
    struct lookUpTable *codeTable;
    uint32_t numOfChars;
    fieldHeader *header;


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
    structure(head,0);

    /*Step 3 - build code look up table c->code*/
    codeTable = buildLookUpTable(head);


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

        int countNumBitsWR = 0;

       /*the max number numCodes can represent if there all 1's - 2^{numcodes}  + (1) plus if we need to pad 00's*/

		uint8_t output;
		int divisablity_by_8;

       /*Step 5 - build body (just read the file one more time and translate the code)*/
        while(read(inFd, &c, sizeof(uint8_t)))
        {
            /*codeTable[c].code - the code corresponding to char c*/ 
			divisablity_by_8 = writeBits(c, strlen(codeTable[c].code), &output, codeTable);
        }

		/*Step 6 - check if final add output is div by 8*/
		if(divisablity_by_8 != 0)
		{	
			/*add this value to the left over output*/
			output = output << divisablity_by_8;
            write(1, &output, sizeof(uint8_t));
        }

        /*restore stdout*/
        if(argc == 3)
        {
           dup2(outSavedFd, 1);
           close(outFd);
        }



    /*step 3 - write to the header (read from input once again - decode the body)*/



    /*======================================================================*/
/*free(header);
  free(head);
    free(ft);
*/

    return 0;
 }
