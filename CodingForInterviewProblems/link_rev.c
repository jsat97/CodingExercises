#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	struct Node *next;
	int data;
} Node_t;

Node_t*
init_node(int data)
{
	Node_t *node;
	node = malloc(sizeof(Node_t));
	node->data = data;
	node->next = NULL;

	return node;
}

Node_t*
reverse_recur(Node_t**head, Node_t *node)
{
	Node_t *cur = *head;

	if (node->next == NULL) {
		return;

	reverse_recur(head, cur->next);	
	cur->next->next = cur;
	cur->next = NULL;

	return cur;
}

//insert at head of list
void
insert_node(Node_t **head, int data)
{
	Node_t *node;
	node = init_node(data);		
	node->next = *head;
	*head = node;
}

void
print_list(Node_t *head)
{
	Node_t *node = head;
	while (node != NULL) {
		printf("%d ", node->data);
		node = node->next;
	}
	printf("\n");
}
int
main()
{
	Node_t *head = init_node(5);
	
	insert_node(&head, 10);
	insert_node(&head, 2);
	insert_node(&head, 13);
	print_list(head);
	reverse_recur(head);	
	print_list(head);

}
