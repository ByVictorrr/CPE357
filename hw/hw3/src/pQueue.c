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

int size(listNode *head)
{
   /*single case return empty*/
   if(head == NULL)
       return 0;
   else if( head->next != NULL)
       return 1;

   /*count  has to be at least 1 by time to get here*/
   int count =1;
   while (head->next)
   {
       head=head->next;
       count++;
   }
   return count;
}

void pushNew(listNode **head, char c, int freq) {
    listNode *beg = *head; /*get address of first head*/

    /*new node*/
    listNode *tempNode;

    tempNode = newListNode(c, freq, NULL, NULL);

    /*case 1 - list is emtpy*/
    if (!beg->curr)
    {
        *head = tempNode;
        return;
    }

	/*case 2 - the data to be inserted has less freq than the head*/
    if(beg->curr->freq > freq)
    {
        tempNode->next= *head;
        *head = tempNode;
    }
	/*case 3 - general case (it goes through the list and finds a spot)*/
    else
    {
        /*find position where it belongs*/
        while ( beg->next != NULL && beg->next->curr->freq < freq)
        {
		   	beg = beg->next;
        }

		/* there could be equal freq, so prioritze it by 2nd field*/
		if( beg->next !=NULL &&  beg->next->curr->freq == freq)
		{
			/*case 3.1 - sort by character ascii code if have equal freq*/
			while(beg->next !=NULL &&  beg->next->curr->freq == freq)
			{
				
			}

		}

		/*At this poostion soon to inserted freq should be less than or equal to beg*/
        tempNode->next = beg->next;
        beg->next = tempNode;

    }

}
void pushNode(listNode **head, listNode *parent)
{
    listNode *beg = *head; /*get address of first head*/

    /*new node*/
    listNode *tempNode;

	/*check to see if we can insert at the head*/
    if(beg->curr->freq > parent->curr->freq)
    {
        parent->next= *head;
        *head = parent;

    }
    
	/*else if its frequenc isnt less than the head*/
        /*find position where it belongs*/
        while ( beg->next != NULL && beg->next->curr->freq < parent->curr->freq )
        {
            beg = beg->next;
        }
		/*At this point parent-curr->freq is less than beg->next-curr->breq or equal to*/
		if (beg->curr->
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

void transverse(listNode *head)
{

    int count =0;
    while(!head)
    {
        printf("node chacter, %c", head->curr->freq);
        head=head->next;
    }
}


int main()
{

    listNode *head = newListNode('a', 1);
    push(&head, 'a', 2);
    push(&head, 'b', 1);
    printf("list");

    while(!isEmpty(&head))
    {
        printf("%d \n", poll(&head));
    }

    return 0;
}


*/
