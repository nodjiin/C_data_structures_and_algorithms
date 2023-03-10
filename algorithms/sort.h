/**
 * \file            sort.h
 * \brief           header file containing the declaration of sort algorithms implemented in this library.
 */

#ifndef SORT
#define SORT

#include <stdlib.h>
#include <core/datatype.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

__declspec(dllexport) void selection_sort(data_type array[], size_t array_size, data_type_compare_fn compare);
__declspec(dllexport) void insertion_sort(data_type array[], size_t array_size, data_type_compare_fn compare);
__declspec(dllexport) void bubble_sort(data_type array[], size_t array_size, data_type_compare_fn compare);
__declspec(dllexport) void merge_sort(data_type array[], size_t low, size_t high, data_type_compare_fn compare);
__declspec(dllexport) void heap_sort(data_type array[], size_t array_size, data_type_compare_fn compare);
__declspec(dllexport) void quick_sort(data_type array[], size_t low, size_t high, data_type_compare_fn compare);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !SORT