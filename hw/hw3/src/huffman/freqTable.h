#ifndef FREQTABLE
#define FREQTABLE

#define ALPHABET_SIZE 256
#include <stdio.h>
#include <stdlib.h>
int *buildFreqTable();
void insertToFreqTable(int **ft, unsigned char c);
void printFreqTable(int *ft);
void freeFreqTable(int *ft);

#endif
