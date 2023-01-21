/**
 * \file            heap.h
 * \brief           header file containing the declaration of the heap data structure and operations.
 */

#ifndef HEAP
#define HEAP

#include <stdbool.h>
#include "dynamicarray.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief           heap data structure.
 * \note            this data structure has been implemented as a min heap. However, since the priority comparison operation is passed as a function pointer,
 *                  it is possible to convert it into a min heap by inverting the value returned by the custom implemented comparison.
 */
typedef struct {
    dynamic_array_t* array;       /*!< internal data storage */
    data_type_compare_fn compare; /*!< function used to evaluate value priority in the heap */
} heap_t;

__declspec(dllexport) heap_t* heap_construct(size_t initial_size, data_type_compare_fn compare);
__declspec(dllexport) void heap_insert(heap_t* heap, data_type value);
__declspec(dllexport) data_type heap_extract(heap_t* heap);
__declspec(dllexport) size_t heap_count(heap_t* heap);
__declspec(dllexport) bool heap_is_empty(heap_t* heap);
__declspec(dllexport) void heap_clear(heap_t** heap);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !HEAP