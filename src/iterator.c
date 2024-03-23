#include "iterator.h"


Iterator* iter_create(const STRUCT_TYPE* struct_object) {
	Iterator* iter = (Iterator *) malloc(sizeof(Iterator));
	if (iter == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	iter->node = struct_object->back;
	return iter;
}


STRUCT_NODE_TYPE* iter_next(Iterator* iter) {
	if (iter->node == NULL) {
		return NULL;
	}
	iter->node = iter->node->next;
	return iter->node;
}


void iter_set(Iterator* iter, VALUE_TYPE value) {
	if (iter->node == NULL) {
        fprintf(stderr, "Iterator is at the end.\n");
        return;
    }
	iter->node->value = value;
}


VALUE_TYPE iter_get(Iterator* iter) {
	if (iter->node == NULL) {
        fprintf(stderr, "Iterator is at the end.\n");
        exit(EXIT_FAILURE);
    }
	return iter->node->value;
}


void iter_delete(Iterator* iter) {
    if (iter == NULL || iter->node == NULL) {
        return;
    }
    STRUCT_NODE_TYPE* node_to_delete = iter->node;
    iter->node = iter->node->next; // Перемещаем указатель на следующий узел
    if (iter->node != NULL) {
        iter->node->prev = node_to_delete->prev; // Обновляем указатель на предыдущий узел у следующего узла
    }
    free(node_to_delete);
}

