/**
 * \file            sort.c
 * \brief           header file containing the definition of sort algorithms implemented in this library.
 */

#include "sort.h"
#include "data_structures/queue.h"

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
    size_t i, j;      /* the sorted subarray lies between 0 and i, the unsorted between i + 1 and array_size */
    size_t min_index; /* index of the current minimum element in the right subarray */

    for (i = 0; i < array_size; i++) {
        min_index = i;

        for (j = i + 1; j < array_size; j++) {
            if (array[j] < array[min_index]) {
                min_index = j;
            }
        }

        swap(&array[i], &array[min_index]);
    }
}

/**
 * \brief sorts an array of data_type values using insertion sort algorithm.
 *
 * this function sorts an array of data_type values in ascending order using the insertion sort algorithm. The insertion sort algorithm works by iterating 
 * through the array and moving each element to its correct position in the sorted subarray. The algorithm maintains two subarrays in a given array: one 
 * subarray which is already sorted and another subarray which is unsorted. In every iteration of insertion sort, an element from the unsorted subarray is 
 * picked and inserted into its correct position in the sorted subarray.
 *
 * \param[in] array: pointer to the first element of the array to be sorted.
 * \param[in] array_size: size of the array to be sorted.
 */
void
insertion_sort(data_type array[], size_t array_size) {
    size_t i, j; /* the sorted subarray lies between 0 and i, the unsorted between i + 1 and array_size */

    for (i = 1; i < array_size; i++) {
        j = i; /* each iteration we include a new element (in position i) in the sorted subarray */

        while ((j > 0) && (array[j] < array[j - 1])) { /* move the new element in the correct position */
            swap(&array[j], &array[j - 1]);
            j--;
        }
    }
}

/**
 * \brief sorts an array of data_type values using bubble sort algorithm.
 *
 * this function sorts an array of data_type values in ascending order using the bubble sort algorithm. The bubble sort algorithm works by repeatedly swapping 
 * adjacent elements if they are in the wrong order. The algorithm maintains two subarrays in a given array: one subarray which is already sorted and another 
 * subarray which is unsorted. In every iteration of bubble sort, the largest element from the unsorted subarray is picked and moved to the end of the unsorted
 * subarray.
 *
 * \param[in] array: pointer to the first element of the array to be sorted.
 * \param[in] array_size: size of the array to be sorted.
 */
void
bubble_sort(data_type array[], size_t array_size) {
    size_t i, j; /* the sorted subarray lies between i and array_size, the unsorted between 0 and i - 1 */

    for (i = array_size; i > 1; i--) {
        for (j = 0; j < i - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
            }
        }
    }
}

static void
merge(data_type array[], size_t low, size_t middle, size_t high) {
    size_t i;                   /* counter */
    queue_t *buffer1, *buffer2; /* buffers to hold elements for merging */

    buffer1 = queue_construct();
    buffer2 = queue_construct();

    for (i = low; i <= middle; i++) {
        queue_enqueue(buffer1, array[i]);
    }

    for (i = middle + 1; i <= high; i++) {
        queue_enqueue(buffer2, array[i]);
    }

    i = low;
    while (!(queue_is_empty(buffer1) || queue_is_empty(buffer2))) {
        if (queue_peek(buffer1) <= queue_peek(buffer2)) {
            array[i++] = queue_dequeue(buffer1);
        } else {
            array[i++] = queue_dequeue(buffer2);
        }
    }
    while (!queue_is_empty(buffer1)) {
        array[i++] = queue_dequeue(buffer1);
    }
    while (!queue_is_empty(buffer2)) {
        array[i++] = queue_dequeue(buffer2);
    }

    queue_clear(&buffer1);
    queue_clear(&buffer2);
}

void
merge_sort(data_type array[], size_t low, size_t high) {
    size_t middle; /* index of middle element */

    if (low < high) {
        middle = (low + high) / 2;
        merge_sort(array, low, middle);
        merge_sort(array, middle + 1, high);
        merge(array, low, middle, high);
    }
}