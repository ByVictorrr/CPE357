
struct node{
	char * word;
	int wCount;
	struct node *left_child; //lexicographically less
	struct node *right_child; //lexicographically greater
};


struct node *newNode(char *word);
struct node *insertNode(struct node *root, char*word);
struct node *searchNode(struct node *root, char *word );
void inOrder(struct node *root);
void freeTree(struct node *root);
void freeNode(struct node *root);


