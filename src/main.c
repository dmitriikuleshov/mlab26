#include <stdio.h>
#include <deque.h>


int main(void) {
	Deque* deque = deque_create();
	deque_push_front(deque, 1, 2);
	deque_print(deque);
	return 0;
}