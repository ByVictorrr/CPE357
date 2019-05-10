#ifndef HTABLE_H
#define HTABLE_H


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include "pQueue.h"
#include "lookUpTable.h"
#include "huffmanTree.h"
#include "freqTable.h"

#define BUFSIZE 210
#define ALPHABET_SIZE 256

extern int numUniqueChar;
void freeEveryThing(Node *huffmanTree, struct lookUpTable *table, int *freqTable);

#endif
