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
	return (deque->back == NULL && deque->front == NULL);
}


void deque_push_front(Deque* deque, KEY_TYPE key, VALUE_TYPE value) {
	Node* new_node = node_create(key, value);
	if (deque->front == NULL && deque->back == NULL) {
		deque->back = new_node;
		deque->front = new_node;
	} else {
		new_node->prev = deque->front;
		deque->front->next = new_node;
		deque->front = new_node;
	}
}


void deque_push_back(Deque* deque, KEY_TYPE key, VALUE_TYPE value) {
	Node* new_node = node_create(key, value);
	if (deque->back == NULL && deque->front == NULL) {
		deque->back = new_node;
		deque->front = new_node;
	} else {
		new_node->next = deque->back;
		deque->back->prev = new_node;
		deque->back = new_node;
	}
}


void deque_pop_front(Deque* deque) {
	if (deque->front == NULL) {
		printf("pop_front from an empty deque!");
	} else {
		Node* new_front = deque->front->prev;
		free(deque->front);
		deque->front = new_front;
		deque->front->next = NULL;
	}
}


void deque_pop_back(Deque* deque) {
	if(deque->back == NULL) {
		printf("pop_back from an empty deque!");
	} else {
		Node* new_back = deque->back->next;
		free(deque->back);
		deque->back = new_back;
		deque->back->prev = NULL;
	}
}


void deque_print(const Deque* deque) {
	
}


size_t deque_size(const Deque*) {

}


