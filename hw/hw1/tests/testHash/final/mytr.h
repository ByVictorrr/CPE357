#define ASCII 256
#define DELETED -1

struct node
{
	int value;
	struct node *next;
};

struct node hashTable[ASCII]; 
void initTable(struct node *table);
int strl(char * s);
int cmpStr(char *set1, char *set2);
int getLine( struct node *table);
int getFormat(int argc, char *set1);
char getEscChar(char c);
void fillDeleteTable(struct node *table, char *set);
void fillTranslateTable(struct node *table, char *set1, char *set2);


