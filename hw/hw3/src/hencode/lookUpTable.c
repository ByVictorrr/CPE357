#include "lookUpTable.h"



void initLookUpTable(Node *node, char *s, int top ,struct lookUpTable **table)
 {

    if(isLeaf(node))
    {

		(*table)[node->c].code = (char*)calloc(ALPHABET_SIZE,sizeof(char));
		strcpy((*table)[node->c].code,s);

	}else{
				s[top] = '0';
				initLookUpTable(node->left_child, s, top+1, table);

				s[top] = '1';
                initLookUpTable(node->right_child, s, top+1, table);
			}

 }


 struct lookUpTable *buildLookUpTable(Node *root)
{
    struct lookUpTable *table = (struct lookUpTable*)malloc(sizeof(struct lookUpTable)*ALPHABET_SIZE);
    char *s=(char*)calloc(ALPHABET_SIZE,sizeof(char));
    initLookUpTable(root,s, 0 ,&table);
    return table;
}


void freeLookUpTable(struct lookUpTable *table) {
    if (table != NULL)
    {
        int i;
        /*free each character corresonding to that code*/
        for (i = 0; i < ALPHABET_SIZE; i++) {
            if(table[i].code !=NULL)
                free(table[i].code);
        }
        free(table);
    }
    return;
}

