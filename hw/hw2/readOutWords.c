#include "fw.h"
void readOutWords(int amount, WordItem *arr[])
{
    int n = 0;
    printf("these are the %d top words", amount);
    for (n = 0; n < amount; n++)
    {
        printf("%s: count: %d\n", arr[n]->word, arr[n]->count);
    }
}