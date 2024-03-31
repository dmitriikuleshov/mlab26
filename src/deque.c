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
	printf("\n");
	free(iter);
}


size_t deque_size(const Deque* deque) {
	return deque->size;
}


void deque_insert(Deque* deque, const int index, const KEY_TYPE key, const VALUE_TYPE value) {
    // check if index is not correct
    if (index < 0 || index > deque->size) {
        fprintf(stderr, "Invalid index for insertion.\n");
        return;
    }

	Node* new_node = node_create(key, value);

    // insert in the beginning 
    if (index == 0) {
        if (deque->back == NULL) { // if deque is empty
            deque->back = new_node;
            deque->front = new_node;
        } else {
            new_node->next = deque->back;
            deque->back->prev = new_node;
            deque->back = new_node;
        }
    } 
    // insert in the ending
    else if (index == deque->size) {
        if (deque->front == NULL) { // if deque is empty
            deque->back = new_node;
            deque->front = new_node;
        } else {
            new_node->prev = deque->front;
            deque->front->next = new_node;
            deque->front = new_node;
        }
    } 
    // insert in the middle
    else {
        int i;
        Node* current = deque->back;
        for (i = 0; i < index - 1; i++) {
            current = current->next;
        }
        new_node->next = current->next;
        new_node->prev = current;
        current->next->prev = new_node;
        current->next = new_node;
    }

    deque->size++;
}



void deque_remove(Deque* deque, const int index) {
    // check if index is not correct
    if (index < 0 || index >= deque->size) {
        fprintf(stderr, "Invalid index for removal.\n");
        return;
    }

    Node* node_to_delete;

    // remove from the beginning 
    if (index == 0) {
        if (deque->back == NULL) { // if deque is empty
            fprintf(stderr, "Deque is empty, cannot remove.\n");
            return;
        }
        node_to_delete = deque->back;
        deque->back = deque->back->next;
        if (deque->back == NULL) { // remove the last element
            deque->front = NULL;
        } else {
            deque->back->prev = NULL;
        }
    } 
    // remove from the end
    else if (index == deque->size - 1) {
        if (deque->front == NULL) { // if deque is empty
            fprintf(stderr, "Deque is empty, cannot remove.\n");
            return;
        }
        node_to_delete = deque->front;
        deque->front = deque->front->prev;
        if (deque->front == NULL) { // if remove the last element
            deque->back = NULL;
        } else {
            deque->front->next = NULL;
        }
    } 
    // remove from the middle
    else {
        int i;
        Node* current = deque->back;
        for (i = 0; i < index; i++) {
            current = current->next;
        }
        node_to_delete = current;
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    free(node_to_delete);
    deque->size--;
}


void deque_clean(Deque* deque) {
	while (!deque_is_empty(deque)) {
		deque_pop_front(deque);
	}
}


Deque* merge_deques(Deque* deque1, Deque* deque2) {
    Deque* result = deque_create();

    while (!deque_is_empty(deque1) && !deque_is_empty(deque2)) {
        if (deque1->front->key >= deque2->front->key) { 
            deque_push_back(result, deque1->front->key, deque1->front->value);
            deque_pop_front(deque1);
        } else {
            deque_push_back(result, deque2->front->key, deque2->front->value);
            deque_pop_front(deque2);
        }
    }

    // Add the remaining elements from deque1, if any
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
    if (deque_is_empty(deque)) {
        return;
    }
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
