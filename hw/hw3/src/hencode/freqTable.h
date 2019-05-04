#ifndef FREQTABLE
#define FREQTABLE

#define ALPHABET_SIZE 256
#include <stdio.h>
#include <stdlib.h>

int *buildFreqTable(char *data);
void printFreqTable(int *freqTable);

#endif
