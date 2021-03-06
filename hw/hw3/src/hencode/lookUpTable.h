#ifndef LOOKUPTABLE
#define LOOKUPTABLE

#include "huffmanTree.h"

#define ALPHABET_SIZE 256

struct lookUpTable{
        char *code;
};

void initLookUpTable(Node *node, char *s, int top ,struct lookUpTable **table);
struct lookUpTable *buildLookUpTable(Node *root);
void freeLookUpTable(struct lookUpTable *table);

#endif

