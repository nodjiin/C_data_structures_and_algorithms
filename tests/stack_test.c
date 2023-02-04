#include <assert.h>
#include "data_structures/stack.h"
#include "stack_test.h"
#include "testvalues.h"

void
stack_construct_test(void) {
    stack_t* stack;

    stack = stack_construct(2);

    assert(stack != NULL);
    assert(stack->array != NULL);
    assert(stack->array->count == 0);
    assert(stack->array->length == 2);
}

void
stack_push_test(void) {
    stack_t* stack;

    stack = stack_construct(2);
    stack_push(stack, TESTVAL1);
    stack_push(stack, TESTVAL2);

    assert(stack->array->count == 2);
    assert(darray_get(stack->array, 0) == TESTVAL1);
    assert(darray_get(stack->array, 1) == TESTVAL2);
}

void
stack_pop_test(void) {
    stack_t* stack;
    data_type pop1, pop2;

    stack = stack_construct(2);
    stack_push(stack, TESTVAL1);
    stack_push(stack, TESTVAL2);

    pop1 = stack_pop(stack);
    pop2 = stack_pop(stack);

    assert(stack->array->count == 0);
    assert(pop1 == TESTVAL2);
    assert(pop2 == TESTVAL1);
}

void
stack_count_test(void) {
    stack_t* stack;
    size_t count;

    stack = stack_construct(2);
    stack_push(stack, TESTVAL1);
    stack_push(stack, TESTVAL2);

    count = stack_count(stack);

    assert(count == 2);
}

void
stack_is_empty_test(void) {
    stack_t* stack;
    bool is_empty_pre_push, is_empty_after_push;

    stack = stack_construct(1);

    is_empty_pre_push = stack_is_empty(stack);
    stack_push(stack, TESTVAL1);
    is_empty_after_push = stack_is_empty(stack);

    assert(is_empty_pre_push);
    assert(!is_empty_after_push);
}

void
stack_clear_test(void) {
    stack_t* stack;

    stack = stack_construct(2);
    stack_push(stack, TESTVAL1);
    stack_push(stack, TESTVAL2);

    stack_clear(&stack);

    assert(stack == NULL);
}

void
stack_testall(void) {
    stack_construct_test();
    stack_push_test();
    stack_pop_test();
    stack_count_test();
    stack_is_empty_test();
    stack_clear_test();
}