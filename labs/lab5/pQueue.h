#ifndef PQUEUE
#define PQUEUE
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "node.h"

typedef struct nodeList{
    Node *curr;
    struct  nodeList *next;
}listNode;


listNode *newListNode(unsigned char c, int freq, Node *left , Node *right);
int size(listNode *head);
void pushNewNode(listNode **head, unsigned char c, int freq);
void pushNode(listNode **head, listNode *parent);
void pop(listNode ** head);
Node *peek(listNode ** head);
/*removes head and retreives it*/
Node *poll(listNode **head);
int isEmpty(listNode **head);
void transverse(listNode *head);



#endif

