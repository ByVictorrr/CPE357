#include "pQueue.h"

listNode *newListNode(unsigned char c, int freq, Node *left , Node *right)
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
   else if( head->next == NULL)
       return 1;

   /*count  has to be at least 1 by time to get here*/
   int count = 1;

   while (head->next)
   {
       head=head->next;
       count++;
   }
   return count;
}

void pushNewNode(listNode **head, unsigned char c, int freq) {

    listNode *beg = *head; /*get address of first head*/

    /*new node*/
    listNode *tempNode;

    tempNode = newListNode(c, freq, NULL, NULL);

    /*case 1 - list is emtpy*/
    if (!*head)
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
        /*Transverse till the tend of the list and on the way look for a node in
         * the list that has a frequency greater than that to be inserted*/

        while ( beg->next != NULL && beg->next->curr->freq < freq)
        {
		   	beg = beg->next;
        }
        /* At this point beg should be holding a lnode where its next is equal or greater
         * than the frequency node to be inserted*/

        /* case 3.1 - could be at the end of the list*/

        /* case 3.2 - that next node could possibly be equal to the one node to be inserted*/

			/*case 3.2.1 - because beg->next->curr->freq == freq */
			    /* we need to insert based upon character */

			    /*Tranverse the list until a node is found where they are not equal*/
			while(beg->next !=NULL && beg->next->curr->freq == freq && beg->next->curr->c < c )
			{
			    /*If the soon to be entered character is less than c next*/
			    /*we found the location for new node to be inserted*/
			   beg = beg->next;

			}


		/*At this poostion soon to inserted freq should be less than or equal to beg*/
        tempNode->next = beg->next;
        beg->next = tempNode;

    }

}


void pushNode(listNode **head, listNode *parent) {

    listNode *beg = *head; /*get address of first head*/

    /*case 1 - list is emtpy*/
    if (!*head)
    {
        *head = parent;
        return;
    }

	/*case 2 - the data to be inserted has less freq than the head*/
    if(beg->curr->freq > parent->curr->freq)
    {
        parent->next= *head;
        *head = parent;
    }

	/*case 3 - general case (it goes through the list and finds a spot)*/
    else
    {
        /*Transverse till the tend of the list and on the way look for a node in
         * the list that has a frequency greater than that to be inserted*/

        while ( beg->next != NULL && beg->next->curr->freq < parent->curr->freq)
        {
		   	beg = beg->next;
        }
        /* At this point beg should be holding a lnode where its next is equal or greater
         * than the frequency node to be inserted*/

        /* case 3.1 - could be at the end of the list*/

        /* case 3.2 - that next node could possibly be equal to the one node to be inserted*/

		if( beg->next !=NULL &&  beg->next->curr->freq == parent->curr->freq)
		{
			/*case 3.2.1 - because beg->next->curr->freq == freq */
			    /* we need to insert based upon character */

			    /*Tranverse the list until a node is found where they are not equal*/
			while(beg->next !=NULL && beg->next->curr->freq == parent->curr->freq && beg->next->curr->c < parent->curr->c )
			{
			    /*If the soon to be entered character is less than c next*/
			        /*we found the location for new node to be inserted*/
			   beg = beg->next;

			}

		}

		/*At this poostion soon to inserted freq should be less than or equal to beg*/
        parent->next = beg->next;
        beg->next = parent;

    }

}
void pop(listNode ** head)
{
    listNode *temp = *head;

    (*head) = (*head)->next;

    free(temp->curr);
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
        temp->c = peek(head)->c;
        temp->freq = peek(head)->freq;
        temp->right_child = peek(head)->right_child;
        temp->left_child = peek(head)->left_child;

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
    while(head->next != NULL)
    {
        printf("node chacter %c and  %d\n", head->curr->c, head->curr->freq);
        head=head->next;
    }
        printf("node chacter %c and  %d\n", head->curr->c, head->curr->freq);
}
/*
int main()
{

    listNode *head = NULL;
    pushNewNode(&head, 'h', 2);
    pushNewNode(&head, 'b', 1);
    pushNewNode(&head, 'f', 3);
    pushNewNode(&head, 'a', 1);

    listNode *add = newListNode('h',2,NULL,NULL);



    pushNode(&head, add);


    printf("list\n");

    Node *temp ;


    transverse(head);

    while(!isEmpty(&head))
    {

        temp = poll(&head);
        printf("character %c and frequency found: %d \n", temp->c, temp->freq);
        free(temp);
    }



    return 0;
}
 */
