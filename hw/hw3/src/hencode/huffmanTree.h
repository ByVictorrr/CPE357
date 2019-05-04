#ifndef HUFFMANTREE
#define HUFFMANTREE

#include "pQueue.h"

int codeLength;

#define ALPHABET_SIZE 256

enum boolean{FALSE,TRUE};
int numUniqueChar;

Node *buildHuffTree(int *freqTable);
void inorder(Node *root);
int isLeaf(Node *n);

#endif