#ifndef HUFFMANTREE
#define HUFFMANTREE

#include "pQueue.h"

#define ALPHABET_SIZE 256

typedef enum boolean{FALSE,TRUE} bool;
int numCodes;

Node *buildHuffTree(int *freqTable);
void inorder(Node *root);
int isLeaf(Node *n);
void freeHuffmanTree(Node *tree);

#endif