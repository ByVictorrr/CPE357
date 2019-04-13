#define ASCII 256
#define DELETED -1


int hashTable[ASCII]; 
void initTable(int *table);
int strl(char * s);
int getLine( int *table);
int getFormat(int argc, char *set1);
char getEscChar(char c);
void fillDeleteTable(int *table, char *set);
void fillTranslateTable(int *table, char *set1, char *set2);


