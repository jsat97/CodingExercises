#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_SIZE 16

#define SPACE ' '
#define PUT_SPACES(n) \
int i;	\
for(i=0; i<n; i++) {	\
puchar(SPACE);	\
}
struct Node {
	struct Node* left;
	struct Node* right;
	int data;
};

typedef struct Node Node_t;

Node_t *node;

Node_t *stack[STACK_SIZE];
int top =0;

void
push(Node_t *node)
{
	if (top == STACK_SIZE) {
		printf("push: reached max size for stack \n");
		exit(1);
	}
	//printf("push: node %p top %d\n", node, top);
	stack[top] = node;
	top++;
}

Node_t *pop()
{
	Node_t *node;
	top--;
	if (top < 0) {
		printf("pop: reached bottom of stack \n");
		exit(1);
	}
	node =stack[top];	
	//printf("pop: node %p top %d\n", node, top);
	return node;
}

void
init_node(Node_t **node, int data)
{
	*node = malloc(sizeof(Node_t));
	(*node)->data = data;
	(*node)->left = (*node)->right =NULL;
}

int
insert(Node_t *node, int data)
{
	if (node == NULL) {
		printf("NULL node\n");
		return -1;
	}

	if (data < node->data) {
		if (node->left == NULL) {
			init_node(&node->left, data); 
			//printf("inserted %d\n", data);
			return 0;
		} else
			return insert(node->left, data);
	} else if (data > node->data) {
		if (node->right == NULL) {
			init_node(&node->right, data); 
			//printf("inserted %d\n", data);
			return 0;
		} else	
			return insert(node->right, data);
	} else {
		//printf("error: duplicate data %d\n", data);
		return -1;
	}	

}

//L,R, P
void
print_tree_postorder(Node_t *node)
{
	if (node !=NULL){			
		print_tree_postorder(node->left);		
		print_tree_postorder(node->right);		
		printf("%d\n", node->data);	
	}	
}

//L,P, R
void
print_tree_inorder(Node_t *node)
{
	if (node != NULL){			
		print_tree_inorder(node->left);		
		printf("%d\n", node->data);	
		print_tree_inorder(node->right);		
	}
}

//P, L, R
void
print_tree_preorder(Node_t *node)
{
	if (node != NULL){			
		printf("%d\n", node->data);
		print_tree_preorder(node->left);
		print_tree_preorder(node->right);
	}
}


void
print_tree_levelorder(Node_t *root)
{
	Node_t *node = root;
	printf("%d\n",root->data);
	while (node != NULL) {
		if (node->left)
			printf("%d\t", node->left->data);
		if (node->right)
			printf("%d", node->right->data);
		printf("\n");
		push(node->left);
		push(node->right);
		node = pop();
	}

}

int 
count(Node_t*node)
{
	if (node) {
		return (1+count(node->left) + count(node->right));
	} else 
		return 0;	
}

void
TrackPath(Node_t *node, int *path, int last)
{
	int   j;
	Node_t *left, *right;
	//printf("%d\n", node->data);
	if (node == NULL) return;
	path[last++] = node->data;
	if (node->left == NULL && node->right == NULL) {
		for (j=0; j<last; j++) 
			printf("%d ", path[j]);
			printf("\n");
	} else {
		TrackPath(node->left, path, last);
		TrackPath(node->right, path, last);
	}
}

int
min(Node_t *node)
{
	if (node->left != NULL) {
		return min(node->left);
	}
	return node->data;
}

int
max(Node_t *node)
{
	if (node->right != NULL) {
		return max(node->right);
	}
	return node->data;
}

int
main(int argc, char*argv[])
{
	FILE *fp;
	int i,n, val[100];
	int path[100];

	Node_t root={0,0, 2}; 			

	if (argc != 3) {
		printf("%s <input file> <test name>\n", argv[0]);
		exit(1);
	}	
	if ( (fp = fopen(argv[1], "r")) == NULL) {
		printf("fopen error\n");
		exit(1);
	}
	fscanf(fp, "%d", &n);
	for (i=0; i<n; i++)
		fscanf(fp, "%d", &val[i]);

	root.data = val[0];

	for (i=1; i<n; i++)
		insert(&root, val[i]);
		
	if (!strcmp(argv[2], "inorder")) {
		printf("inorder\n");
		print_tree_inorder(&root);
	} else if(!strcmp(argv[2], "preorder")) {
		printf("preorder\n");
			print_tree_preorder(&root);
	} else if(!strcmp(argv[2], "postorder")) {
		printf("postorder\n");
		print_tree_postorder(&root);
	} else if(!strcmp(argv[2], "levelorder")) {
		printf("level order\n");
		print_tree_levelorder(&root);	
	} else if(!strcmp(argv[2], "count")) {
		printf("count of nodes \n");
		printf ("%d\n", count(&root));	
	} else if(!strcmp(argv[2], "path")) {
		printf("paths\n");
		TrackPath(&root, path, 0);	
	} else if(!strcmp(argv[2], "min")) {
		printf("min %d\n", min(&root));
	} else if(!strcmp(argv[2], "max")) {
		printf("max %d\n", max(&root));
	}
}
