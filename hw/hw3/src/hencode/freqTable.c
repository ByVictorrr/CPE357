#include "freqTable.h"
/*buildFrequencyTable: takes in a string and relates
 *
 */
int *buildFreqTable()
{
	/*make a freq table for each character that we are encoding*/
	int *freq = (int *)calloc(ALPHABET_SIZE,sizeof(int));

	return freq;
}

void insertToFreqTable(int **ft, char c)
{
		if(*ft != NULL)
		    ft[(int)c]++;
		return;
}

void printFreqTable(int *freqTable)
{
    int i;
    for (i = 1; i < ALPHABET_SIZE; i++)
    {
        if (freqTable[i] > 0 )
            printf("freqTable[ %c ] = %d\n", (char)i, freqTable[i]);
    }
}

void freeFreqTable(int *ft)
{
    if(ft!=NULL)
        free(ft);
    return;
}


