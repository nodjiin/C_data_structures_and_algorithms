/**
 * \file            dynamicarray.h
 * \brief           header file containing the declaration of the dynamic array data structure and operations.
 */

#ifndef DYNAMICARRAY
#define DYNAMICARRAY

#include <stdlib.h>
#include "core\datatype.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief           dynamic array structure.
 * \note            the dynamic array length will double each time a new item insertion would surpass its current capacity,
 *					and halve each time a new removal will reduce it under 1/4 of it's current capacity.
 */
typedef struct {
    data_type* array; /*!< internal array containing all the inserted item */
    size_t count;     /*!< count of item currently present inside the array */
    size_t length;    /*!< current maximum length of the array */
} dynamic_array_t;

__declspec(dllexport) dynamic_array_t* darray_construct(size_t initial_size);
__declspec(dllexport) void darray_insert(dynamic_array_t* darray, data_type value);
__declspec(dllexport) void darray_insert_head(dynamic_array_t* darray, data_type value);
__declspec(dllexport) void darray_insert_at(dynamic_array_t* darray, data_type value, size_t index);
__declspec(dllexport) void darray_put(dynamic_array_t* darray, data_type value, size_t index);
__declspec(dllexport) data_type darray_get(dynamic_array_t* darray, size_t index);
__declspec(dllexport) data_type darray_remove(dynamic_array_t* darray, size_t index);
__declspec(dllexport) size_t darray_search(dynamic_array_t* darray, data_type value, data_type_compare_fn compare);
__declspec(dllexport) void darray_clear(dynamic_array_t** darray);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !DYNAMICARRAY