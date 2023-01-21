#include <assert.h>
#include "data_structures/heap.h"
#include "heap_test.h"
#include "testvalues.h"

void
heap_construct_test(void) {
    heap_t* heap;

    heap = heap_construct(1, compare);

    assert(heap != NULL);
    assert(heap->compare == compare);
    assert(heap->array != NULL);
    assert(heap->array->length == 1);
}

void
heap_insert_test(void) {
    assert(0);
}

void
heap_extract_test(void) {
    assert(0);
}

void
heap_count_test(void) {
    assert(0);
}

void
heap_is_empty_test(void) {
    assert(0);
}

void
heap_clear_test(void) {
    assert(0);
}

void
heap_testall() {
    heap_construct_test();
    heap_insert_test();
    heap_extract_test();
    heap_count_test();
    heap_is_empty_test();
    heap_clear_test();
}
