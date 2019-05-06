#include "lookUpTable.h"


/*for debugging*/
char c;


void initLookUpTable(Node *node, char *s, int top ,struct lookUpTable **table)
 {
    printf("on character %c", node->c );

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




