/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct WordItem
{
  int count;
  char word[20];
  struct WordItem *left;
  struct WordItem *right;
} WordItem;

void insertNode(WordItem **, char[]);
void read(WordItem *);
void TreeToArray(WordItem *, WordItem **, int);

int main()
{
  int i;
  WordItem *root = NULL;
  WordItem *arr[20];
  char word[20] = "bcd";
  insertNode(&root, word);
  insertNode(&root, "aaaaaple");
  insertNode(&root, "the");
  insertNode(&root, "monster");
  insertNode(&root, "baster");
  insertNode(&root, "lust");
  insertNode(&root, "in");
  insertNode(&root, "the");
  insertNode(&root, "city");
  read(root);

  TreeToArray(root, arr, 0);
  /*
    for(i = 0; i < 20; i++){
        printf("%s %d\n", arr[i]->word, arr[i]->count);
    }*/
  return 0;
}

void insertNode(WordItem **WordPtr, char word[20])
{
  WordItem *temp = NULL;

  if (!*WordPtr)
  {

    temp = (WordItem *)malloc(sizeof(WordItem));

    strcpy(temp->word, word);

    temp->count = 1;
    temp->left = NULL;
    temp->right = NULL;

    *WordPtr = temp;
  }
  else if (strcmp(word, (*WordPtr)->word) < 0)
  {

    insertNode(&((*WordPtr)->left), word);
  }
  else if (strcmp(word, (*WordPtr)->word) > 0)
  {

    insertNode(&((*WordPtr)->right), word);
  }
  else
  {
    /*oh it's already in the tree!*/
    ((*WordPtr)->count)++;
  }
}

void read(WordItem *WordPtr)
{
  printf("%s : %d   ", WordPtr->word, WordPtr->count);
  if (WordPtr->left)
  {
    read(WordPtr->left);
  }
  if (WordPtr->right)
  {
    read(WordPtr->right);
  }
}

void TreeToArray(WordItem *node, WordItem *arr[], int i)
/*pass in an arr - initiate total node count +1*/
{

  if (node)
  {
    if (node->left)
    {
      TreeToArray(node->left, arr, i);
    }
    printf("%s\n", node->word);
    arr[i++] = node;
    if (node->right)
    {
      TreeToArray(node->right, arr, i);
    }
  }
}
