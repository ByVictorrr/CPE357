#include "fw.h"
#include <stdio.h>

void readOutWords(int amount, struct node *arr[])
{
    int n = 0;
    printf("these are the %d top words", amount);
    for (n = 0; n < amount; n++)
    {
        printf("%s: count: %d\n", arr[n]->word, arr[n]->wCount);
    }
}
