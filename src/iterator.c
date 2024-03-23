#include "iterator.h"


Iterator* iter_create(STRUCT_TYPE* struct_object) {
	Iterator* iter = (Iterator *) malloc(sizeof(Iterator));
	iter->node = struct_object->back;
}



STRUCT_DATA_TYPE* iter_next(Iterator* iter);
void iter_set(Iterator* iter, VALUE_TYPE);
VALUE_TYPE iter_get(Iterator* iter);
void iter_delete(Iterator* iter);
