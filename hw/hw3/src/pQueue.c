#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "node.c"

/*=========================================================================*/

/*=======================NodeList which is just node with a next==========*/

typedef struct nodeList{
    Node *curr;
    struct  nodeList *next;
}listNode;


listNode *newListNode(char c, int freq, Node *left , Node *right)
{
    listNode *new = (listNode*)malloc(sizeof(listNode));

    new->curr = newNode(c,freq, left, right);
    new->next=NULL;
    return new;
}




void *pushNew(listNode **head, char c, int freq)
{
    listNode *beg = *head; /*get address of first head*/

    /*new node*/
    listNode *tempNode;

    tempNode = newListNode(c, freq,NULL,NULL);

    /*if freq is less insert at the head*/
    if(beg->curr->freq < freq)
    {
        tempNode->next= *head;
        *head = tempNode;

    }
    else
    {
        /*find position where it belongs*/
        while ( beg->next != NULL && beg->next->curr->freq > freq)
        {
            beg = beg->next;
        }
        tempNode->next = beg->next;
        beg->next = tempNode;

    }

}
void *pushNode(listNode **head, listNode *parent)
{
    listNode *beg = *head; /*get address of first head*/

    /*new node*/
    listNode *tempNode;

    /*if freq is less insert at the head*/
    if(beg->curr->freq > parent->curr->freq)
    {
        parent->next= *head;
        *head = parent;

    }
    else
    {
        /*find position where it belongs*/
        while ( beg->next != NULL && beg->next->curr->freq < parent->curr->freq )
        {
            beg = beg->next;
        }
        parent->next = beg->next;
        beg->next = parent;

    }
}

void pop(listNode ** head)
{
    listNode *temp = *head;
    (*head) = (*head)->next;
    free(temp);
}

Node *peek(listNode ** head)
{
    return (*head)->curr;
}

/*removes head and retreives it*/
Node *poll(listNode **head)
{
    Node *temp = (Node*)malloc(sizeof(Node));

    if (*head == NULL)
        return NULL;
    else {
        /*copy contents of what is head before pop*/
        temp = peek(head);
        pop(head);
    }
    return temp;
}

int isEmpty(listNode **head)
{
    return (*head) == NULL;
}
/*=========================================================================*/




int main()
{

    listNode *head = newListNode('a', 1);
    push(&head, 'a', 2);
    push(&head, 'b', 2);
    printf("list");

    while(!isEmpty(&head))
    {
        printf("%d \n", poll(&head));
    }

    return 0;
}



