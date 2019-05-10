#include "lookUpTable.h"



void initLookUpTable(Node *node, char *s, long top ,struct lookUpTable **table)
 {

    unsigned char c = (unsigned char)node->c;

    if(isLeaf(node))
    {
        s[top] = '\0';

		(*table)[c].code = (char*)calloc(strlen(s),sizeof(char));

		if(s!=NULL) {
            strcpy((*table)[c].code, s);
        }

    }
        if(node->left_child) {
            s[top] = '0';
            initLookUpTable(node->left_child, s, top +1 , table);
        }
        if(node->right_child) {
            s[top] = '1';
            initLookUpTable(node->right_child, s, top + 1, table);
        }

 }


 struct lookUpTable *buildLookUpTable(Node *root)
{
    struct lookUpTable *table = (struct lookUpTable*)calloc(ALPHABET_SIZE+1,sizeof(struct lookUpTable));
    char *s=(char*)calloc(ALPHABET_SIZE,sizeof(char));
    initLookUpTable(root,s, 0 ,&table);
    free(s);
    return table;
}



void printLookUpTable(struct lookUpTable *table) {
    if (table != NULL)
    {
        int i;
        /*free each character corresonding to that code*/
        for (i = 0; i < ALPHABET_SIZE; i++)
            if(table[i].code != NULL) {
                printf("0x%x: %s\n", i, table[i].code);
            }
    }
    return;
}

void freeLookUpTable(struct lookUpTable *table) {
    if (table != NULL)
    {
        int i;
        /*free each character corresonding to that code*/
        for (i = 0; i < ALPHABET_SIZE; i++)
            if(table[i].code != NULL) {
                free(table[i].code);
            }
        free(table);
    }
    return;
}

