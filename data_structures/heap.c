/**
 * \file            heap.c
 * \brief           source file containing the definition of heap operations.
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "exitcodes.h"
#include "memalloc.h"
#include "heap.h"

/**
 * \brief           value identifying the parent index for a root item (e.g. without a parent).
 * \hideinitializer
 */
#define ROOT           0

/**
 * \brief           first position used in the heap, right after the offset.
 * \hideinitializer
 */
#define FIRST_POSITION 1

/**
 * \brief           construct a new heap.
 * \param[in]       initial_size: number of items that the heap will be able to contain after initialization. 0 is not considered a valid input, 
 *                  and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       compare: comparison function used to evaluate the priority of each item in the heap. An output > 0 will be considered as a sign that the first value
 *                  passed to the function has lower priority than the second value, conversely with a value < 0 the first value will be considered having greater priority. 
 *                  If the output is 0 the 2 values will be considered of equal priority. `NULL` is not considered a valid input and will cause the program to exit early 
 *                  with an INVALID_INPUT status code.
 * \note            the actual size of the heap will always one unit bigger of the given initial_size. The additional space is used as offset as the beginning to simplify 
 *                  heap elements position calculations.
 * \return          a pointer the newly constructed heap.
 */
heap_t*
heap_construct(size_t initial_size, data_type_compare_fn compare) {
    heap_t* new_heap;

    if (initial_size == 0) {
        fprintf(stderr, "[heap_construct] Invalid input. Faulty construct request with size 0.\n");
        exit(INVALID_INPUT);
    }

    if (compare == NULL) {
        fprintf(stderr, "[heap_construct] Invalid input. Faulty construct request with NULL compare function.\n");
        exit(INVALID_INPUT);
    }

    new_heap = malloc_s(sizeof(heap_t));
    new_heap->array = darray_construct(initial_size + 1);
    darray_insert(new_heap->array, NULL_DATA); /* null data offset, allow us to manipulate the array starting from 1 */
    new_heap->compare = compare;

    return new_heap;
}

/**
 * \brief           find the parent of the given index.
 * \param[in]       index: index of an element inside the heap. Will return ROOT if the element is the first one in the heap (e.g. doesn't have a parent)
 * \return          the parent index.
 */
static size_t
get_parent(size_t index) {
    if (index == FIRST_POSITION) {
        return ROOT;
    }
    return (index / 2); /* implicitly take floor(n/2) */
}

/**
 * \brief           find the first child of the given index.
 * \param[in]       index: index of an element inside the heap.
 * \return          the child index.
 */
static size_t
get_first_child(size_t n) {
    return (2 * n);
}

/**
 * \brief           swap the values located at the 2 given indexes.
 * \param[in]       heap: pointer to heap.
 * \param[in]       index1: index of the first element to swap.
 * \param[in]       index2: index of the second element to swap.
 */
static void
swap(heap_t* heap, size_t index1, size_t index2) {
    data_type temp;
    dynamic_array_t* darray;

    darray = heap->array;
    temp = darray_get(darray, index1);
    darray_put(darray, darray_get(darray, index2), index1);
    darray_put(darray, temp, index2);
}

/**
 * \brief           recursively swap the value at the given index with its parent, until a parent with higher priority is found.
 * \param[in]       heap: pointer to heap.
 * \param[in]       index: index of the element to bubble up.
 */
static void
bubble_up(heap_t* heap, size_t index) {
    size_t parent_index;

    parent_index = get_parent(index);
    if (parent_index == ROOT) { /* we are the first element of the heap, there's no need to bubble up */
        return;
    }

    /* keep bubbling up until we find a parent element with higher priority*/
    if (heap->compare(darray_get(heap->array, parent_index), darray_get(heap->array, index)) > 0) {
        swap(heap, index, parent_index);
        bubble_up(heap, parent_index);
    }
}

/**
 * \brief           insert a new value in the heap.
 * \param[in]       heap: heap pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       value: value to be inserted.
 */
void
heap_insert(heap_t* heap, data_type value) {
    if (heap == NULL) {
        fprintf(stderr, "[heap_insert] Invalid input. Faulty insert request on NULL heap.\n");
        exit(INVALID_INPUT);
    }

    darray_insert(heap->array, value); /* insert the element at the end of the array */
    /* bubble it up untill there's no other value with higher priority on top of it*/
    bubble_up(heap, heap->array->count - 1); /* -1 to address the initial offset */
}

/**
 * \brief           recursively swap the value at the given index with one of it's childre, until no children with higher priority is found.
 * \param[in]       heap: pointer to heap.
 * \param[in]       index: index of the element to bubble down.
 */
static void
bubble_down(heap_t* heap, size_t index) {
    size_t child_index, min_index;
    dynamic_array_t* darray;

    darray = heap->array;
    child_index = get_first_child(index);
    min_index = index;
    for (size_t i = 0; i <= 1; i++) { /* each element in the heap has got 2 children, so we check the value of both */
        child_index += i;
        if ((child_index) < darray->count) {
            if (heap->compare(darray_get(darray, min_index), darray_get(darray, child_index)) > 0) {
                min_index = child_index;
            }
        }
    }

    if (min_index != index) { /* keep the recursion going if we found a children with higher priority*/
        swap(heap, index, min_index);
        bubble_down(heap, min_index);
    }
}

/**
 * \brief           extract the highest priority value from the heap.
 * \param[in]       heap: heap pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \return          the highest priority value of the heap.
 * \note            trying to extract a value from an empty stack is considered an invalid operation, and will cause an early exit with INVALID_OPERATION status code.
 */
data_type
heap_extract(heap_t* heap) {
    data_type first, last;
    dynamic_array_t* darray;

    if (heap == NULL) {
        fprintf(stderr, "[heap_extract] Invalid input. Faulty extract request on NULL heap.\n");
        exit(INVALID_INPUT);
    }

    darray = heap->array;
    if (darray->count == 1) { /* count == 1 to take into account the offset element */
        fprintf(stderr, "[heap_extract] Invalid operation. Faulty extract request on empty heap.\n");
        exit(INVALID_OPERATION);
    }

    first = darray_get(darray, FIRST_POSITION);      /* get the first (highest priority) value in the heap */
    last = darray_remove(darray, darray->count - 1); /* extract the last value in the queue */
    darray_put(darray, last, FIRST_POSITION);        /* override the first value with the last */
    bubble_down(heap, FIRST_POSITION);               /* bubble down to re-establish the correct priority */
    return first;
}

/**
 * \brief           check how many values are contained in the heap.
 * \param[in]       heap: heap pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \return          the number of values currently in the heap.
 */
size_t
heap_count(heap_t* heap) {
    if (heap == NULL) {
        fprintf(stderr, "[heap_count] Invalid input. Faulty count request on NULL heap.\n");
        exit(INVALID_INPUT);
    }

    return heap->array->count - 1;
}

/**
 * \brief           check if the heap is empty.
 * \param[in]       stack: heap pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \return          true if the heap is empty, false otherwise.
 */
bool
heap_is_empty(heap_t* heap) {
    if (heap == NULL) {
        fprintf(stderr, "[heap_is_empty] Invalid input. Faulty empty check request on NULL heap.\n");
        exit(INVALID_INPUT);
    }

    return heap->array->count == 1;
}

/**
 * \brief           free the given heap.
 * \param[in]       heap: pointer to heap pointer.
 * \note            this function will free the memory used by the heap. The input pointer itself will be set to `NULL`.
 */
void
heap_clear(heap_t** heap) {
    if (heap == NULL || *heap == NULL) {
        return;
    }

    darray_clear(&((*heap)->array));
    free_s(*heap);
}