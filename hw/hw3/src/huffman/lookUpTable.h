#ifndef LOOKUPTABLE
#define LOOKUPTABLE

#include "huffmanTree.h"

#define ALPHABET_SIZE 256

struct lookUpTable{
        char *code;
};

void initLookUpTable(Node *node, char *s, long top ,struct lookUpTable **table);
struct lookUpTable *buildLookUpTable(Node *root);
void printLookUpTable(struct lookUpTable *table);
void freeLookUpTable(struct lookUpTable *table);

#endif

