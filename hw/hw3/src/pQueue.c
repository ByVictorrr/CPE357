#include "node.h"

enum boolean {TRUE, FALSE};

typedef struct Queue{
	Node *head;
	Node *tail;

}pQueue;


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
pQueue* pEndQueue()
{


}
/*deletion operation*/
int deQueue()
{

}
k

