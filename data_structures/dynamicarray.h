/**
 * \file            linkedlist.h
 * \brief           header file containing the declaration of the dynamic array data structure, and connected functions.
 */

#ifndef DYNAMICARRAY
#define DYNAMICARRAY

#include <stdlib.h>
#include "datatype.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief           dynamic array structure.
 */
typedef struct {
    data_type* array;
    size_t count;
    size_t length;
} dynamic_array_t;

__declspec(dllexport) dynamic_array_t* darray_construct(size_t initial_size);
__declspec(dllexport) void darray_insert(dynamic_array_t* darray, data_type value);
__declspec(dllexport) void darray_insert_head(dynamic_array_t* darray, data_type value);
__declspec(dllexport) void darray_insert_at(dynamic_array_t* darray, data_type value, size_t index);
__declspec(dllexport) data_type darray_get(dynamic_array_t* darray, size_t index);
__declspec(dllexport) void darray_remove(dynamic_array_t* darray, size_t);
__declspec(dllexport) void darray_clear(dynamic_array_t* darray);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !DYNAMICARRAY