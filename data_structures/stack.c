#include <stdio.h>
#include "exitcodes.h"
#include "memalloc.h"
#include "stack.h"

/**
 * \brief           construct a new stack array.
 * \param[in]       initial_size: number of items that the stack will be able to contain after initialization. 0 is not considered a valid input, 
 *                  and will cause an early exit with INVALID_INPUT status code.
 * \return          a pointer the newly constructed array.
 */
stack_t*
stack_construct(size_t initial_size) {
    stack_t* new_stack;

    if (initial_size == 0) {
        fprintf(stderr, "[stack_construct] Invalid input. Faulty construct request with size 0.\n");
        exit(INVALID_INPUT);
    }

    new_stack = malloc_s(sizeof(stack_t));
    new_stack->array = darray_construct(initial_size);

    return new_stack;
}

/**
 * \brief           push the given value on top of the stack.
 * \param[in]       stack: stack pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       value: new value to be pushed in the stack.
 */
void
stack_push(stack_t* stack, data_type value) {
    if (stack == NULL) {
        fprintf(stderr, "[stack_push] Invalid input. Faulty push request on NULL stack.\n");
        exit(INVALID_INPUT);
    }

    darray_insert(stack->array, value);
}

/**
 * \brief           pop the value on top of the stack.
 * \param[in]       stack: stack pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \return          the value on top of the stack.
 * \note            trying to pop an empty stack is considered an invalid operation, and will cause an early exit with INVALID_OPERATION status code.
 */
data_type
stack_pop(stack_t* stack) {
    data_type top_value;

    if (stack == NULL) {
        fprintf(stderr, "[stack_pop] Invalid input. Faulty pop request on NULL stack.\n");
        exit(INVALID_INPUT);
    }

    if (stack->array->count == 0) {
        fprintf(stderr, "[stack_pop] Invalid operation. Faulty pop request on empty stack.\n");
        exit(INVALID_OPERATION);
    }

    top_value = darray_remove(stack->array, stack->array->count - 1);
    return top_value;
}

/**
 * \brief           check how many values are contained in the stack.
 * \param[in]       stack: stack pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \return          the number of values currently in the stack.
 */
size_t
stack_count(stack_t* stack) {
    if (stack == NULL) {
        fprintf(stderr, "[stack_count] Invalid input. Faulty count request on NULL stack.\n");
        exit(INVALID_INPUT);
    }

    return stack->array->count;
}

/**
 * \brief           check if the stack is empty.
 * \param[in]       stack: stack pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \return          true if the stack is empty, false otherwise.
 */
bool
stack_is_empty(stack_t* stack) {
    if (stack == NULL) {
        fprintf(stderr, "[stack_is_empty] Invalid input. Faulty empty check request on NULL stack.\n");
        exit(INVALID_INPUT);
    }

    return stack->array->count == 0;
}

/**
 * \brief           free the given stack.
 * \param[in]       stack: pointer to stack pointer.
 * \note            this function will free the memory used by the stack. The input pointer itself will be set to `NULL`.
 */
void
stack_clear(stack_t** stack) {
    if (stack == NULL || *stack == NULL) {
        return;
    }

    darray_clear((*stack)->array);
    free_s(*stack)
}