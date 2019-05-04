



/*buildFrequencyTable: takes in a string and relates
 *
 */
int *buildFreqTable(char *data)
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

void printFreqTable(int *freqTable)
{
    for (int i = 1; i < ALPHABET_SIZE; i++)
    {
        if (freqTable[i] >0)
            printf("freqTable[ %c ] = %d\n", (char)i, freqTable[i]);
    }
}




