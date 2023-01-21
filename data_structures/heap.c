/**
 * \file            heap.c
 * \brief           source file containing the definition of heap operations.
 */

#include <stdio.h>
#include <stdlib.h>
#include "exitcodes.h"
#include "memalloc.h"
#include "heap.h"

/**
 * \brief           construct a new heap.
 * \param[in]       initial_size: number of items that the heap will be able to contain after initialization. 0 is not considered a valid input, 
 *                  and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       compare: comparison function used to evaluate the priority of each item in the heap. An output < 0 will be considered as a sign that the first value
 *                  passed to the function has lower priority than the second value, conversely with a value > 0 the first value will be considered having greater priority. 
 *                  If the output is 0 the 2 values will be considered of equal priority. `NULL` is not considered a valid input and will cause the program to exit early 
 *                  with an INVALID_INPUT status code.
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
    new_heap->array = darray_construct(initial_size);
    new_heap->compare = compare;

    return new_heap;
}