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
}

void
heap_construct_from_array_test(void) {
    heap_t* heap;
    data_type array[3] = {TESTVAL2, TESTVAL3, TESTVAL1};

    heap = heap_construct_from_array(array, 3, compare);

    assert(darray_get(heap->array, 1) == TESTVAL1);
    assert(darray_get(heap->array, 2) == TESTVAL3);
    assert(darray_get(heap->array, 3) == TESTVAL2);
}

void
heap_insert_test(void) {
    heap_t* heap;

    heap = heap_construct(3, compare);

    heap_insert(heap, TESTVAL2);
    heap_insert(heap, TESTVAL3);
    heap_insert(heap, TESTVAL1);

    assert(darray_get(heap->array, 1) == TESTVAL1);
    assert(darray_get(heap->array, 2) == TESTVAL3);
    assert(darray_get(heap->array, 3) == TESTVAL2);
}

void
heap_extract_test(void) {
    heap_t* heap;
    data_type value;

    heap = heap_construct(3, compare);

    heap_insert(heap, TESTVAL1);
    heap_insert(heap, TESTVAL2);
    heap_insert(heap, TESTVAL3);
    value = heap_extract(heap);

    assert(value == TESTVAL1);
    assert(darray_get(heap->array, 1) == TESTVAL2);
    assert(darray_get(heap->array, 2) == TESTVAL3);
}

void
heap_count_test(void) {
    heap_t* heap;

    heap = heap_construct(2, compare);

    heap_insert(heap, TESTVAL1);
    heap_insert(heap, TESTVAL2);

    assert(heap_count(heap) == 2);
}

void
heap_is_empty_test(void) {
    heap_t* heap;

    heap = heap_construct(2, compare);

    heap_insert(heap, TESTVAL1);
    heap_extract(heap);

    assert(heap_is_empty(heap));
}

void
heap_clear_test(void) {
    heap_t* heap;

    heap = heap_construct(2, compare);
    heap_insert(heap, TESTVAL1);
    heap_insert(heap, TESTVAL2);

    heap_clear(&heap);

    assert(heap == NULL);
}

void
heap_testall() {
    heap_construct_test();
    heap_construct_from_array_test();
    heap_insert_test();
    heap_extract_test();
    heap_count_test();
    heap_is_empty_test();
    heap_clear_test();
}
