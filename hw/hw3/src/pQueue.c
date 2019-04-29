#include "node.h"

enum boolean {TRUE, FALSE};


typedef struct nodeList {
    Node *next;
}listNode;


typedef struct Queue{
	listNode *head;
	listNode *tail;
}*pQueue;


listNode *newListNode(char )

/*making a queue*/
pQueue *initQueue()
{
    if((pQueue * q = (pQueue*)malloc(sizeof(pQueue))) ==NULL)
        return NULL;

    q->head = NULL;
    q->tail = NULL;
    return q;
}
/*check if q is empty*/
int isEmpty(pQueue q)
{
   if(q.head==NULL)
    return TRUE;

   return FALSE
}



/*add in queue*/
pQueue* pEndQueue(pQueue q, char character, int freq)
{
    listNode *new;

    if ((new = newListNode(character, freq, NULL, NULL)) == NULL)
        return NULL;

    if(!isEmpty(q))
    {
        /*check where to insert in the pQueue*/
        if(new->freq < q->head->freq )
        {
           new->next = q->head;
           q->head = new;

        }
    }



}



/*deletion operation*/
int deQueue()
{

}

