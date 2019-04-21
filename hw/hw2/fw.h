#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct WordItem {
   int count;   
   char* word;
   WordItem *left;
   WordItem *right;
} WordItem;

