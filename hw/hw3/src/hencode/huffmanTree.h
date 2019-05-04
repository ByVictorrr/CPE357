#ifndef HUFFMANTREE
#define HUFFMANTREE

#include "pQueue.h"
#include "node.h"
int codeLength;

#define ALPHABET_SIZE 256

enum boolean{FALSE,TRUE};
int numUniqueChar = 0;

Node *buildHuffTree(int *freqTable);
void inorder(Node *root);
int isLeaf(Node *n);
#endif