#include <stdio.h>
#include <stdbool.h>
#include <deque.h>

Node* node_create(KEY_TYPE key, VALUE_TYPE value) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL) {
		printf("Memory allocation error for the new node\n");
		exit(1);
	}
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}

void deque_create(Deque* deque) {
	Deque* new_deque = (Deque*)malloc(sizeof(Deque));
	if (new_deque == NULL) {
		printf("Memory allocation error for the new deque\n");
		exit(1);
	}
	new_deque->size = 0;
};


bool deque_is_empty(Deque* deque) {
	return (deque->left == NULL && deque->right == NULL);
}





