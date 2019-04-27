#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*entry in the hash table*/
struct node{

	int key;
	int wCount;
	char *word;
	struct node * next;
};


/* Hash table */

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
	else if (!(hashtable *table = (hashtable*)malloc(sizeof(hashtable)))
		return NULL;
	//step 3: allocate buckets
	else if (!(hashtable *table = (hashtable*)malloc(sizeof(hashtable)))
}

void find_top_N_words(hashtable * words, int n){
	if(!words){
		/*hashtable empty*/
    }
	/*create a map - map string and int wCount
	O(n) ->  traverse through the hash table and return the k words with maximum counts. */
       
