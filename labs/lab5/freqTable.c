#include "freqTable.h"
/*buildFrequencyTable: takes in a string and relates
 *
 */
int numUniqueChar = 0;

int *buildFreqTable()
{
	/*make a freq table for each character that we are encoding*/
	int *freq = (int *)malloc(ALPHABET_SIZE*sizeof(int));

    int i;
	for(i=0; i< ALPHABET_SIZE; i++)
	    freq[i]=0;

	return freq;
}

void insertToFreqTable(int **ft, unsigned char c)
{

		if(*ft != NULL)
        {
            if(ft[0][(unsigned char)c] == 0) {
                numUniqueChar++;
            }

		    ft[0][(unsigned char)c]++;
        }
		return;
}

void printFreqTable(int *freqTable)
{
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++)
    {
        if (freqTable[i] > 0 )
            printf("freqTable[ %c ] = %d\n", (unsigned char)i, freqTable[i]);
    }
}

void freeFreqTable(int *ft)
{
    if(ft!=NULL)
        free(ft);
    return;
}


