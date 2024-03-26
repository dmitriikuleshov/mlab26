#include <stdio.h>
#include "../headers/deque.h"


int test1() {
	// test pop_back, push_front
	Deque* deque = deque_create();
	if (deque_size(deque) != 0) return 1;
	deque_push_front(deque, 1, 0);
	if (deque_size(deque) != 1) return 2;
	deque_push_front(deque, 2, 0);
	deque_push_front(deque, 3, 0);
	deque_push_front(deque, 4, 0);
	if (deque_size(deque) != 4) return 3;

	deque_pop_back(deque);
	if (deque_size(deque) != 3) return 4;
	deque_pop_back(deque);
	deque_pop_back(deque);
	deque_pop_back(deque);
	if (deque_size(deque) != 0) return 5;

	// test pop_front, push_back
	if (deque_size(deque) != 0) return 6;
	deque_push_back(deque, 1, 0);
	if (deque_size(deque) != 1) return 7;
	deque_push_back(deque, 2, 0);
	deque_push_back(deque, 3, 0);
	deque_push_back(deque, 4, 0);
	if (deque_size(deque) != 4) return 8;

	deque_pop_front(deque);
	if (deque_size(deque) != 3) return 9;
	deque_pop_front(deque);
	deque_pop_front(deque);
	deque_pop_front(deque);
	if (deque_size(deque) != 0) return 10;

	deque_clean(deque);
	free(deque);
	return 0;
}


void test2() {
	//test_insert
	Deque* deque = deque_create();
	deque_push_front(deque, 0, 0);
	deque_push_front(deque, 1, 0);
	deque_push_front(deque, 2, 0);
	deque_push_front(deque, 3, 0);
	deque_push_front(deque, 4, 0);
	deque_insert(deque, 0, 100000, 0);
	deque_insert(deque, 1, 100001, 0);
	deque_insert(deque, 5, 100006, 0);
	deque_insert(deque, 8, 100008, 0);
	deque_insert(deque, 15, 100015, 0);
	deque_print(deque);

	deque_clean(deque);
	free(deque);
}


void test3() {
	//test_insert
	Deque* deque = deque_create();
	deque_push_front(deque, 0, 0);
	deque_push_front(deque, 1, 0);
	deque_push_front(deque, 2, 0);
	deque_push_front(deque, 3, 0);
	deque_push_front(deque, 4, 0);
	deque_push_front(deque, 5, 0);
	deque_push_front(deque, 6, 0);

	deque_remove(deque, -100); // error
	deque_remove(deque, 3); // removes element with key = 3
	deque_remove(deque, 0); // removes element with key = 0
	deque_remove(deque, 4); // removes element with key = 6
	deque_remove(deque, 4); // error
	deque_print(deque);

	deque_clean(deque);
	free(deque);
}


void test4() {
	// tests merge sort
	Deque* deque1 = deque_create();
	deque_push_front(deque1, 5, 0);
	deque_push_front(deque1, 0, 0);
	deque_push_front(deque1, 2, 0);
	deque_push_front(deque1, 1, 0);
	deque_push_front(deque1, 4, 0);
	deque_push_front(deque1, 6, 0);
	deque_push_front(deque1, 3, 0);
	deque_merge_sort(deque1);
	deque_print(deque1);

	Deque* deque2 = deque_create();
	deque_push_front(deque2, 7, 0);
	deque_push_front(deque2, 9, 0);
	deque_push_front(deque2, 8, 0);
	deque_push_front(deque2, 11, 0);
	deque_push_front(deque2, 10, 0);
	deque_push_front(deque2, 12, 0);
	deque_push_front(deque2, 13, 0);
	deque_merge_sort(deque2);
	deque_print(deque2);

	Deque* deque3 = merge_deques(deque1, deque2);
	deque_print(deque3);

	deque_clean(deque1);
	deque_clean(deque2);
	deque_clean(deque3);
	free(deque1);
	free(deque2);
	free(deque3);
}


int main(void) {
	//printf("test1: %d", test1());
	test4();
	return 0;
}