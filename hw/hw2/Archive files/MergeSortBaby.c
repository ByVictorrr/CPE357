#include <stdlib.h>
#include <stdio.h>
#include "fw.h"

void merge(struct node *arr[], int left, int middle, int right)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    /* create temp arrays */
    struct node *L[n1], *R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;    // Initial index of first subarray
    j = 0;    // Initial index of second subarray
    k = left; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if(L[i]->wCount > R[j]->wCount){
            arr[k]=L[i];
            i++;
        }
        else if(L[i]->wCount < R[j]->wCount){
            arr[k]=R[j];
            j++;
        }
        else if (L[i]->wCount == R[j]->wCount)
        {
            if (strcmp((L[i]->word), (R[j]->word)) == -1)
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
    }

    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* left is initally 0 and right is n-1 for the size */
void mergeSort(struct node arr[], int left, int right)
{
    if (left < right)
    {
        // this is the better way to do it.. no segfault
        int middi = left + (right - left) / 2;

        // Sort first then the second...the dirty dirty second
        mergeSort(arr, left, middi);
        mergeSort(arr, middi + 1, right);

        merge(arr, left, middi, right);
    }
}
