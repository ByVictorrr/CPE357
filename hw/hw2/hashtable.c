#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 1000

/*entry in the hash table*/
struct node{

	int wCount; //value
	char *word; //key
	struct node * next;
};


/* Has tablee */

struct hashtable
{
	int size;
	int numEnteries;
	struct node **buckets;

};
	/*initalizeTable: allocates a finite size table*/
	struct hashtable * initalizeTable(int size); 

	/*inserts: information to the table*/
	int insertNode(struct hashtable *table, char *word);
	
	int destroy(struct hashtable *table);
	int hash(struct hashtable* table, char *word);



int main()
{
struct hashtable * table = initalizeTable(SIZE);

char *tWord = "victor";

int index1 = insertNode(table, tWord);
	
int index2 = insertNode(table,"victor");

//shoud print out prinf("wCount = 2);
printf("inputed %s at: %d\n", tWord, index1);
printf("inputed %s at: %d\n", tWord, index2);

return 0;
}


struct hashtable *initalizeTable(int size)
{
	//step 1: check if size is valid
	if (size <= 0) return NULL;
	//step 2: allocate the table using safe_malloc
	struct hashtable *table;
	if (!(table = (struct hashtable*)malloc(sizeof(struct hashtable))))
		return NULL;
	//step 3: allocate buckets
	else if (!(table->buckets = (struct node**)malloc(sizeof(struct node*)*size)))
		return NULL;
	//step 4:  intialize all the buckets
	int i;
	for ( i = 0; i < size; i++)
		table-> buckets[i] = NULL; //setting each struct node ptr in the heap to NULL
	//step 5: initalize table vars
	table->size = size;
	table->numEnteries = 0;
	return table;
}

/*locationNode: lookeds for a word in the table for a given hash value*/
struct *locationNode(struct *hashtable, char *word)
{
	struct node * find = hashtable->buckets[hash(word)]; 
	struct node *prev = NULL;

	if(find == NULL) return NULL; //if the head is NULL

	while(find != NULL) //checks from the 1st plus node
	{
		//if input word already exist, return the address
		if(!strcmp(find->word,word))
			return find;

			prev = find;
			find=find->next;
	}
	return prev; //return node before NULL hits
}




/*createUniqueWord - returns a unqiue word*/ 
struct node *createUniqueWord(char *word)
{
	if (!table) return NULL;

	struct node *temp = (struct node*)malloc(sizeof(struct node)); //creat a new struct node
	temp->word = (char*)malloc(strlen(word));
	strcpy(temp->word,word); //copy string contents to knew node
	temp->wCount = 1;
	temp->next = NULL;

	return temp;
}

/*insertNode: returns the index at which struct node inserted*/
int insertNode(struct hashtable *table, char *word)
{
	//step1 - table is empty
	if(table == NULL)
		return -1;
	
	int index = hash(table, word); //index into table

	struct node **bucketsCpy= table->buckets; //get the ith index in the table

	struct node *list;

	//if word doesnt exist
	if (!(list = locationNode(hashtable, word))) 
	{
		list->next = createUniqueWord(word);
		
	}
	else{ //list has prev addresss to the NULL in it

	}
	while (bucketsCpy[index]  )
	{
		//Step 2.1 - check if the word is in the table alread 
		if(entry->word == word) //if the same word lets incrment wCount
		{
			entry->wCount++;
			printf("wCount =%d \n", entry->wCount);
			return index; //if same word return that index
		}

		prev = entry;
		entry = entry->next; //go to the next struct node
	}
	entry = table->buckets[i];

	while (table->buckets[i] != prev)
		prev=prev->next;

	prev->next = temp;
	
	while(buckets -> 
	table->buckets[i];
	table->numEnteries++;
	
	return index;
}


struct node *addNodeNext

/*hash - djb2 algorithm */
int hash(struct hashtable *table, char *word) 
{
	int i, hash = 0;
	for(i=0; i<table->size; i++)
		hash = 31*hash + word[i];

	return hash % table->size;
}




