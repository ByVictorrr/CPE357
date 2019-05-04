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

struct huffmanEncoder {
    fieldHeader *header; /*a single header is an array of field header*/
    uint32_t header_size; /*num of unique chars*/
    uint8_t *body;
}packedCode = {

        .header = NULL,
        .body = NULL
        /*.header_size = numUniqueChar*/
};






/*packing the body into a smaller */
uint8_t *generateBody(struct lookUpTable *table, char *data ,int numBitsCode)
{

    int bytesToAllocate = (int)ceil((double)numBitsCode/BYTE);

    printf("Bytes to allocate: %d\n", bytesToAllocate);


  /*allocate n bytes*/
  uint8_t *encoded = (uint8_t*)malloc(bytesToAllocate* sizeof(uint8_t));


  while()
  for(i = 0; i< strlen(data[i]) )



  /*pack table[(*data++)].code into the body*/
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

generateBody(table,numBitsOfCode(table));

    fieldHeader *header = generateHeader(ft, numUniqueChar);

	printFieldHeader(header,numUniqueChar);

	printf("get codes : %d\n", numCodes);

/*=================================================*/
  free(header);
  free(head);
    free(ft);





   /*read once and store in to an inputbuffer*/


   int inFd, outFd;

   if(argc == 1 || argc <= 3)
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

   /*could write to the screen or outfile*/


        /*step 1 - write the header first to the file or stdout*/

       /*if there is a outfile listed*/
       if( argc == 3)
       {
          if((outFd = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0700) == -1)
          {
              perror(argv[2]); /*1st argument permission denied*/
              exit(-1);
          }

          dup2(outFd, 1); /*outFile is now stdout if there is a file to out to*/

       }else{ /*else write to std out*/

       }

       /*step 2 - write the body to file or stdout*/

       /*step 2.1 - build tree*/
       /*step 2.2 - get c->codes table*/
       /*step 2.3 - free treee*/

       
       /*step 3 - write to the header (read from input once again - decode the body)*/






    return 0;
 }
