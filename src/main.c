#include <stdio.h>
#include "deque.h"

void test1() {
	Deque* deque = deque_create();
	deque_push_front(deque, 1, 2);
	deque_push_back(deque, 3, 4);
	deque_pop_front(deque);
	deque_pop_back(deque);

	deque_push_front(deque, 1, 2);
	deque_push_back(deque, 3, 4);
	deque_pop_back(deque);
	deque_pop_front(deque);
	deque_clean(deque);
	free(deque);
}

void test2() {
	
}


int main(void) {
	test1();
	test2();

	return 0;
}