#include <assert.h>
#include "data_structures/dynamicarray.h"
#include "dynamicarray_test.h"
#include "testvalues.h"

void
darray_construct_test(void) {
    dynamic_array_t* array;

    array = darray_construct(1);
    assert(array != NULL);
    assert(array->array != NULL);
    assert(array->count == 0);
    assert(array->length == 1);
}

void
darray_insert_test(void) {
    dynamic_array_t* array;

    array = darray_construct(1);
    darray_insert(array, TESTVAL1);
    darray_insert(array, TESTVAL2);

    assert(array->count == 2);
    assert(array->length == 2);
    assert(array->array[0] == TESTVAL1);
    assert(array->array[1] == TESTVAL2);
}

void
darray_insert_head_test(void) {
    dynamic_array_t* array;

    array = darray_construct(1);
    darray_insert(array, TESTVAL1);
    darray_insert_head(array, TESTVAL2);

    assert(array->count == 2);
    assert(array->length == 2);
    assert(array->array[0] == TESTVAL2);
    assert(array->array[1] == TESTVAL1);
}

void
darray_insert_at_test(void) {
    dynamic_array_t* array;

    array = darray_construct(1);
    darray_insert(array, TESTVAL1);
    darray_insert(array, TESTVAL2);
    darray_insert_at(array, TESTVAL3, 1);

    assert(array->count == 3);
    assert(array->length == 4);
    assert(array->array[0] == TESTVAL1);
    assert(array->array[1] == TESTVAL3);
    assert(array->array[2] == TESTVAL2);
}

void
darray_put_test(void) {
    dynamic_array_t* array;

    array = darray_construct(1);
    darray_insert(array, TESTVAL1);
    darray_insert(array, TESTVAL2);
    darray_put(array, TESTVAL3, 1);

    assert(array->count == 2);
    assert(array->length == 2);
    assert(array->array[0] == TESTVAL1);
    assert(array->array[1] == TESTVAL3);
}

void
darray_get_test(void) {
    dynamic_array_t* array;
    data_type value;

    array = darray_construct(1);
    darray_insert(array, TESTVAL1);
    darray_insert(array, TESTVAL2);
    value = darray_get(array, 1);

    assert(array->count == 2);
    assert(array->length == 2);
    assert(array->array[0] == TESTVAL1);
    assert(array->array[1] == TESTVAL2);
    assert(value == TESTVAL2);
}

void
darray_remove_test(void) {
    dynamic_array_t* array;
    data_type value;

    array = darray_construct(1);
    darray_insert(array, TESTVAL1);
    darray_insert(array, TESTVAL2);
    value = darray_remove(array, 1);

    assert(array->count == 1);
    assert(array->length == 2);
    assert(array->array[0] == TESTVAL1);
    assert(value == TESTVAL2);
}

void
darray_search_test(void) {
    dynamic_array_t* array;
    size_t index;

    array = darray_construct(1);
    darray_insert(array, TESTVAL1);
    darray_insert(array, TESTVAL2);
    darray_insert(array, TESTVAL3);
    index = darray_search(array, TESTVAL2, compare);

    assert(array->count == 3);
    assert(array->length == 4);
    assert(array->array[0] == TESTVAL1);
    assert(array->array[1] == TESTVAL2);
    assert(array->array[2] == TESTVAL3);
    assert(index == 1);
}

void
darray_clear_test(void) {
    dynamic_array_t* array;
    size_t index;

    array = darray_construct(1);
    darray_insert(array, TESTVAL1);
    darray_insert(array, TESTVAL2);
    darray_insert(array, TESTVAL3);
    darray_clear(&array);

    assert(array == NULL);
}

void
dynamicarray_testall(void) {
    darray_construct_test();
    darray_insert_test();
    darray_insert_head_test();
    darray_insert_at_test();
    darray_put_test();
    darray_get_test();
    darray_remove_test();
    darray_search_test();
    darray_clear_test();
}