#ifndef HUFFMANTREE
#define HUFFMANTREE

#include "pQueue.h"

#define ALPHABET_SIZE 256

enum boolean{FALSE,TRUE};
int numUniqueChar;
int numCodes;

Node *buildHuffTree(int *freqTable);
void inorder(Node *root);
int isLeaf(Node *n);

#endif