/**
 * \file            sort.c
 * \brief           header file containing the definition of sort algorithms implemented in this library.
 */

#include "sort.h"

/**
 * \brief swaps two data_type values.
 *
 * this function swaps the values of two data_type variables using a temporary variable.
 *
 * \param[in] a: pointer to the first data_type variable.
 * \param[in] b: pointer to the second data_type variable.
 */
static void
swap(data_type* a, data_type* b) {
    data_type temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * \brief sorts an array of data_type values using selection sort algorithm.
 *
 * this function sorts an array of data_type values in ascending order using the selection sort algorithm. The selection sort algorithm works by repeatedly 
 * finding the minimum element from unsorted part and putting it at the beginning. The algorithm maintains two subarrays in a given array: one subarray which
 * is already sorted and another subarray which is unsorted. In every iteration of selection sort, the minimum element from the unsorted subarray is picked 
 * and moved to the sorted subarray.
 *
 * \param[in] array: pointer to the first element of the array to be sorted.
 * \param[in] array_size: size of the array to be sorted.
 */
void
selection_sort(data_type array[], size_t array_size) {
    size_t min_index; /* index of the current minimum element in the right subarray */

    for (size_t i = 0; i < array_size; i++) {
        min_index = i;

        for (size_t j = i + 1; j < array_size; j++) {
            if (array[j] < array[min_index]) {
                min_index = j;
            }
        }

        swap(&array[i], &array[min_index]);
    }
}