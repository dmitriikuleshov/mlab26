#ifndef ITERATOR_H
#define ITERATOR_H

#include "deque.h"

#define STRUCT_DATA_TYPE Node
#define STRUCT_TYPE Deque

typedef struct Iterator {
	STRUCT_DATA_TYPE* node;
} Iterator;

Iterator* iter_create(STRUCT_TYPE*);
STRUCT_DATA_TYPE* iter_next(Iterator* iter);
void iter_set(Iterator* iter, VALUE_TYPE);
VALUE_TYPE iter_get(Iterator* iter);
void iter_delete(Iterator* iter);

#endif