#ifndef HDECODE
#define HDECODE

#include "huffmanTree.h"
#include "freqTable.h"
#include <stdint.h>
#include "readLongLine.h"

#define RD_MODE 0444
extern char *buff;

char charToInt[4];

uint32_t totalNumberOfChars;

extern char *read_long_line(int inFd);

int decodeHeader(int inFd, Node **huffmanTree, int **ft);
void decodeBody(int inFd, int outFd, int numTotalChars, Node *huffmanTree);
int totChars(int *ft);
void decodeFile(int inFd, int outFd, Node **huffmanTree, int **ft);

#endif