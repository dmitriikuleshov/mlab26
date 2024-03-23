#include <deque.h>
#include <iterator.h>


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


Deque* deque_create() {
	Deque* new_deque = (Deque*)malloc(sizeof(Deque));
	if (new_deque == NULL) {
		printf("Memory allocation error for the new deque\n");
		exit(1);
	}
	new_deque->size = 0;
	return new_deque;
}


bool deque_is_empty(const Deque* deque) {
	return (deque->back == NULL && deque->front == NULL);
}


void deque_push_front(Deque* deque, const KEY_TYPE key, const VALUE_TYPE value) {
	Node* new_node = node_create(key, value);
	if (deque->front == NULL && deque->back == NULL) {
		deque->back = new_node;
		deque->front = new_node;
	} else {
		new_node->prev = deque->front;
		deque->front->next = new_node;
		deque->front = new_node;
	}
	deque->size += 1;
}


void deque_push_back(Deque* deque,const KEY_TYPE key, const VALUE_TYPE value) {
	Node* new_node = node_create(key, value);
	if (deque->back == NULL && deque->front == NULL) {
		deque->back = new_node;
		deque->front = new_node;
	} else {
		new_node->next = deque->back;
		deque->back->prev = new_node;
		deque->back = new_node;
	}
	deque->size += 1;
}


void deque_pop_front(Deque* deque) {
	if (deque->front == NULL) {
		printf("pop_front from an empty deque!");
	} else if (deque->front->prev == NULL) {
		free(deque->front);
		deque->front = NULL;
		deque->back = NULL;
	} 
	else {
		Node* new_front = deque->front->prev;
		new_front->next = NULL;
		free(deque->front);
		deque->front = new_front;
		deque->size -= 1;
	}
}


void deque_pop_back(Deque* deque) {
	if(deque->back == NULL) {
		printf("pop_back from an empty deque!");
	} else if (deque->back->next == NULL) {
		free(deque->back);
		deque->back = NULL;
		deque->front = NULL;
	} else {
		Node* new_back = deque->back->next;
		new_back->prev = NULL;
		free(deque->back);
		deque->back = new_back;
		deque->size -= 1;
	}
}


void deque_print(const Deque* deque) {
	Iterator* iter = iter_create(deque);
	Node* cur_node = iter->node;
	while (cur_node != NULL) {
		printf("(key="FORMAT_SPECIFIER_KEY_TYPE ", value=" FORMAT_SPECIFIER_VALUE_TYPE ") ", cur_node->key, cur_node->value);
		cur_node = iter_next(iter);
	}
	free(iter);
}

size_t deque_size(const Deque* deque) {
	return deque->size;
}


void deque_insert(Deque* deque,const int index, const KEY_TYPE key, const VALUE_TYPE value) {
	Iterator* iter = iter_create(deque);
	int iter_index = 0;
	while (iter_index != index) {
		if (iter->node == NULL) {
        	fprintf(stderr, "Iterator is at the end. LIST INDEX OUT OF RANGE\n");
        	return;
		}
		iter_next(iter);
		iter_index += 1;
	}
	Node* new_node = node_create(key, value);
	new_node->next = iter->node;
	new_node->prev = iter->node->prev;

	iter->node->prev->next = new_node;
	iter->node->prev = new_node;
	
	deque->size += 1;
	free(iter);
}

void deque_remove(Deque* deque, const int index) {
	Iterator* iter = iter_create(deque);
	int iter_index = 0;
	while (iter_index != index) {
		if (iter->node == NULL) {
        	fprintf(stderr, "Iterator is at the end. LIST INDEX OUT OF RANGE\n");
        	return;
		}
		iter_next(iter);
		iter_index += 1;
	}
	iter->node->prev->next = iter->node->next;
	iter->node->next->prev = iter->node->prev;
	free(iter->node);

	deque->size -= 1;

	free(iter);
}

void deque_clean(Deque* deque) {
	Iterator* iter = iter_create(deque);
	while (iter->node != NULL) {
		iter_delete(iter);
	}
	free(iter);
}


