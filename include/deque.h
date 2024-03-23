#ifndef DEQUE_H
#define DEQUE_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define DATA_TYPE int
#define KEY_TYPE int
#define VALUE_TYPE int
#define FORMAT_SPECIFIER_KEY_TYPE "%d"
#define FORMAT_SPECIFIER_VALUE_TYPE "%d"

typedef struct Node {
	KEY_TYPE key;
	VALUE_TYPE value; 
	struct Node* next;
	struct Node* prev;
} Node;


typedef struct Deque {
	int size;
	Node* back;
	Node* front;
} Deque;


Deque* deque_create();
bool deque_is_empty(const Deque* deque);
void deque_push_front(Deque* deque, const KEY_TYPE key, const VALUE_TYPE value);
void deque_push_back(Deque* deque,const KEY_TYPE key, const VALUE_TYPE value);
void deque_pop_front(Deque* deque);
void deque_pop_back(Deque* deque);
void deque_print(const Deque* deque);
size_t deque_size(const Deque*);
void deque_insert(Deque*, const int index, const KEY_TYPE, const VALUE_TYPE);
void deque_remove(Deque*, const int index);

#endif