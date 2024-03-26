#include "../headers/deque.h"
#include "../headers/iterator.h"


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
	new_deque->back = NULL;
	new_deque->front = NULL;
	new_deque->size = 0;
	return new_deque;
}


bool deque_is_empty(const Deque* deque) {
	return (deque->back == NULL || deque->front == NULL);
}


void deque_push_front(Deque* deque, const KEY_TYPE key, const VALUE_TYPE value) {
	Node* new_node = node_create(key, value);
	if (deque->front == NULL || deque->back == NULL) {
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
	if (deque->back == NULL || deque->front == NULL) {
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
		deque->size -= 1;
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
		deque->size -= 1;
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

// void deque_clean(Deque* deque) {
// 	Iterator* iter = iter_create(deque);
// 	while (iter->node != NULL) {
// 		iter_delete(iter);
// 	}
// 	free(iter);
// }

void deque_clean(Deque* deque) {
	while (!deque_is_empty(deque)) {
		deque_pop_front(deque);
	}
}


Deque* merge_deques(Deque* deque1, Deque* deque2) {
    Deque* result = deque_create();

    while (!deque_is_empty(deque1) && !deque_is_empty(deque2)) {
        if (deque1->front->key >= deque2->front->key) { // Изменение здесь: заменяем "<=" на ">="
            deque_push_back(result, deque1->front->key, deque1->front->value);
            deque_pop_front(deque1);
        } else {
            deque_push_back(result, deque2->front->key, deque2->front->value);
            deque_pop_front(deque2);
        }
    }

    // Append remaining elements from deque1, if any
    while (!deque_is_empty(deque1)) {
        deque_push_back(result, deque1->front->key, deque1->front->value);
        deque_pop_front(deque1);
    }

    // Append remaining elements from deque2, if any
    while (!deque_is_empty(deque2)) {
        deque_push_back(result, deque2->front->key, deque2->front->value);
        deque_pop_front(deque2);
    }

    return result;
}


// TODO - debug
Deque* deque_merge_sort_recursive(Deque* deque, bool main_deque) {
    if (deque_size(deque) <= 1) {
        return deque;
	}

    // Split the deque into two halves
    Deque* left_half = deque_create();
    Deque* right_half = deque_create();
    size_t half_size = deque_size(deque) / 2;

    while (deque_size(deque) > half_size) {
        deque_push_back(left_half, deque->front->key, deque->front->value);
        deque_pop_front(deque);
    }

    while (!deque_is_empty(deque)) {
        deque_push_back(right_half, deque->front->key, deque->front->value);
        deque_pop_front(deque);
    }
	
	if (!main_deque) {
		free(deque);
	}

    // Recursively sort each half
    left_half = deque_merge_sort_recursive(left_half, false);
    right_half = deque_merge_sort_recursive(right_half, false);

    // Merge the sorted halves
    Deque* result = merge_deques(left_half, right_half);

    // Clean up temporary deques
    deque_clean(left_half);
    deque_clean(right_half);
	free(left_half);
	free(right_half);

    return result;
}


void deque_merge_sort(Deque* deque) {
    Deque* sorted_deque = deque_merge_sort_recursive(deque, true);
    // Copy sorted elements back to original deque
    while (!deque_is_empty(sorted_deque)) {
        deque_push_back(deque, sorted_deque->front->key, sorted_deque->front->value);
        deque_pop_front(sorted_deque);
    }
    // Clean up temporary deque
    deque_clean(sorted_deque);
	free(sorted_deque);
}
