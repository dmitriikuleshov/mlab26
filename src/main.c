#include <stdio.h>
#include "../headers/deque.h"

void test1() {
	printf("TEST1:\n");
	Deque* deque = deque_create();
	deque_push_front(deque, 1, 0);
	deque_push_back(deque, 3, 0);
	deque_pop_front(deque);
	deque_pop_back(deque);

	deque_push_front(deque, 1, 0);
	deque_push_back(deque, 3, 0);
	deque_pop_back(deque);
	deque_pop_front(deque);
	deque_clean(deque);
	free(deque);
	printf("\n");
}


void test3() {
	printf("TEST3:\n");
	Deque* deque1 = deque_create();
	deque_push_front(deque1, 3, 0);
	deque_push_front(deque1, 1, 0);
	deque_push_front(deque1, 4, 0);
	deque_push_front(deque1, 100, 0);
	deque_push_front(deque1, 6, 0);

	Deque* deque2 = deque_create();
	deque_push_front(deque2, 15, 0);
	deque_push_front(deque2, 3, 0);
	deque_push_front(deque2, 24, 0);
	deque_push_front(deque2, 10, 0);
	deque_push_front(deque2, 6, 0);
	deque_push_front(deque1, 1, 0);

	deque_merge_sort(deque1);
	deque_merge_sort(deque2);
	deque_print(deque1);
	printf("\n");
	deque_print(deque2);
	printf("\n");
	Deque* deque3 = merge_deques(deque1, deque2);
	deque_print(deque3);


	deque_clean(deque1);
	deque_clean(deque2);
	deque_clean(deque3);
	free(deque1);
	free(deque2);
	free(deque3);
	printf("\n");

	printf("Deque_size = %d\n", sizeof(Deque));
	printf("Node_size = %d\n", sizeof(Node));
}


void test4() {
	printf("TEST4:\n");
	Deque* deque1 = deque_create();
	deque_push_front(deque1, 3, 0);
	deque_push_front(deque1, 1, 0);
	deque_push_front(deque1, 4, 0);
	deque_push_front(deque1, 100, 0);
	deque_push_front(deque1, 6, 0);

	printf("%d", deque_is_empty(deque1));
	deque_clean(deque1);
	printf("%d", deque_is_empty(deque1));
	deque_print(deque1);
	free(deque1);
}


void test5() {
	printf("TEST5:\n");
	Deque* deque1 = deque_create();
	printf("%ld", deque_size(deque1));
	deque_push_front(deque1, 3, 0);
	deque_push_front(deque1, 1, 0);
	deque_push_front(deque1, 4, 0);
	deque_push_front(deque1, 100, 0);
	deque_push_front(deque1, 6, 0);
	printf("%ld", deque_size(deque1));
	deque_pop_back(deque1);
	printf("%ld", deque_size(deque1));
	deque_pop_front(deque1);
	printf("%ld", deque_size(deque1));

	deque_clean(deque1);
	printf("%ld", deque_size(deque1));
	free(deque1);
}


void test6() {
	Deque* deque = deque_create();
	deque_push_front(deque, 3, 0);
	deque_push_front(deque, 1, 0);
	deque_push_front(deque, 4, 0);
	deque_push_front(deque, 100, 0);

	deque_pop_back(deque);
	deque_pop_back(deque);
	deque_pop_back(deque);


	deque_push_back(deque, 3, 0);
	deque_push_back(deque, 1, 0);
	deque_push_back(deque, 4, 0);
	deque_push_back(deque, 100, 0);

	deque_pop_front(deque);
	deque_pop_front(deque);
	deque_pop_front(deque);

	deque_clean(deque);
	free(deque);
}


int main(void) {
	test3();
	return 0;
}