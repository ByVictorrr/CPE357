#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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
	hashtable * initalizeTable(int size); 

	/*inserts: information to the table*/
	int insert(hashtable *table, int key);
	
	int destroy(hashtable *table);




int main()
{


}


hashtable *initalizeTable(int size)
{
	//step 1: check if size is valid
	if (size <= 0) return NULL;
	//step 2: allocate the table using safe_malloc
	hashtable *table;
	else if (!(table = (hashtable*)malloc(sizeof(hashtable)))
		return NULL;
	//step 3: allocate buckets
	else if (!(table->buckets = (hashtable*)malloc(sizeof(node*)*size));
		return NULL;
	//step 4:  intialize all the buckets
	int i;
	for ( i = 0; i < size; i++)
		table-> buckets[i] = NULL; //setting each node ptr in the heap to NULL
	//step 5: initalize table vars
	table->size = size;
	table->numEnteries = 0;
	return table;
}

/*insertNode: returns the index at which node inserted*/
int insertNode(hashtable *table, char *word)
{
	//step1 - table is empty
	if(table == NULL)
		return -1;
	
	int index = hash(table, word); //index into table

	node *entry = hash->buckets[i]; //get the ith index in the table

	//step 2 - if entry isnt null that means there is a entry in there
	while (entry != NULL)
	{
		//Step 2.1 - check if the word is in the table alread 
		if(entry->word == word) //if the same word lets incrment wCount
		{
			entry->wCount++;
			return index; //if same word return that index
		}

		entry = entry->next; //go to the next node
	}
	//Step 2.2 - this means the two enteries share same hash value (key) but arent same word
	entry = (node*)malloc(sizeof(node)); //creat a new node
	entry->wCount = 1;
	entry->word = (char*)malloc(strlen(word));
	
	return index;
}

int hash(hash_table *table, char *word) 
{
	int i, hash;
	for(i=0; i<table->size; i++)
		hash = 31*hash + key[i];

	return hash % table->size;
}




