#ifndef NODE
#define NODE

typedef struct node{
    unsigned char c;
    int freq;
    struct node *left_child;
    struct node *right_child;
}Node;

Node *newNode(unsigned char c, int freq, Node *left, Node *right);
void padding ( unsigned char ch, int n );
void structure ( struct node *root, int level );

#endif