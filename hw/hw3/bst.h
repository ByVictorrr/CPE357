
typedef struct node{
	char character;
	int freq;
	Node *left_child;
	Node *right_child;
}Node;

Node *newNode(char, int, Node*, Node*);
Node *insertNode(Node *root, char*word);
Node *searchNode(Node *root, char *word );
void inOrder(Node *root);
void freeTree(Node *root);
void freeNode(Node *root);



