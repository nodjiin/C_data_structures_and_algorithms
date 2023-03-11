/**
 * \file            sort.c
 * \brief           header file containing the definition of sort algorithms implemented in this library.
 */

#include "sort.h"
#include "data_structures/queue.h"
#include "data_structures/heap.h"

/**
 * \brief           swaps two data_type values.
 * \param[in]       a: pointer to the first data_type variable.
 * \param[in]       b: pointer to the second data_type variable.
 * \note            this function swaps the values of two data_type variables using a temporary variable.        
 */
static void
swap(data_type* a, data_type* b) {
    data_type temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * \brief           sorts an array of data_type values using selection sort algorithm.
 * \param[in]       array: pointer to the first element of the array to be sorted.
 * \param[in]       array_size: size of the array to be sorted.
 * \param[in]       compare: function used to compare two data_types values.
 * \note            the selection sort algorithm works by repeatedly finding the minimum element from unsorted part and putting it at the beginning. 
 *                  The algorithm maintains two subarrays in a given array: one subarray which is already sorted and another subarray which is unsorted. 
 *                  In every iteration of selection sort, the minimum element from the unsorted subarray is picked and moved to the sorted subarray.
 */
void
selection_sort(data_type array[], size_t array_size, data_type_compare_fn compare) {
    size_t i, j;      /* the sorted subarray lies between 0 and i, the unsorted between i + 1 and array_size */
    size_t min_index; /* index of the current minimum element in the right subarray */

    for (i = 0; i < array_size; i++) {
        min_index = i;

        for (j = i + 1; j < array_size; j++) {
            if (compare(array[j], array[min_index]) < 0) {
                min_index = j;
            }
        }

        swap(&array[i], &array[min_index]);
    }
}

/**
 * \brief           sorts an array of data_type values using insertion sort algorithm.
 * \param[in]       array: pointer to the first element of the array to be sorted.
 * \param[in]       array_size: size of the array to be sorted.
 * \param[in]       compare: function used to compare two data_types values.
 * \note            the insertion sort algorithm works by iterating through the array and moving each element to its correct position in the sorted subarray. 
 *                  The algorithm maintains two subarrays in a given array: one subarray which is already sorted and another subarray which is unsorted. In 
 *                  every iteration of insertion sort, an element from the unsorted subarray is picked and inserted into its correct position in the sorted 
 *                  subarray.
 */
void
insertion_sort(data_type array[], size_t array_size, data_type_compare_fn compare) {
    size_t i, j; /* the sorted subarray lies between 0 and i, the unsorted between i + 1 and array_size */

    for (i = 1; i < array_size; i++) {
        j = i; /* each iteration we include a new element (in position i) in the sorted subarray */

        while ((j > 0) && (compare(array[j], array[j - 1]) < 0)) { /* move the new element in the correct position */
            swap(&array[j], &array[j - 1]);
            j--;
        }
    }
}

/**
 * \brief           sorts an array of data_type values using bubble sort algorithm.
 * \param[in]       array: pointer to the first element of the array to be sorted.
 * \param[in]       array_size: size of the array to be sorted.
 * \param[in]       compare: function used to compare two data_types values.
 * \note            the bubble sort algorithm works by repeatedly swapping adjacent elements if they are in the wrong order. The algorithm maintains two 
 *                  subarrays in a given array: one subarray which is already sorted and another subarray which is unsorted. In every iteration of bubble sort,
 *                  the largest element from the unsorted subarray is picked and moved to the end of the unsorted subarray.
 */
void
bubble_sort(data_type array[], size_t array_size, data_type_compare_fn compare) {
    size_t i, j; /* the sorted subarray lies between i and array_size, the unsorted between 0 and i - 1 */

    for (i = array_size; i > 1; i--) {
        for (j = 0; j < i - 1; j++) {
            if (compare(array[j], array[j + 1]) > 0) {
                swap(&array[j], &array[j + 1]);
            }
        }
    }
}

/**
 * \brief           enqueue the array content in the given range in a newly created queue.
 * \param[in]       queue: queue that will be constructed and used.
 * \param[in]       array: array containing the value to enqueue.
 * \param[in]       start: the starting index of the range to enqueue.
 * \param[in]       end: the ending index of the range to enqueue.
 * \hideinitializer
 */
#define enqueue_interval(queue, array, start, end)                                                                     \
    queue = queue_construct();                                                                                         \
    for (size_t i = start; i <= end; i++) {                                                                            \
        queue_enqueue(queue, array[i]);                                                                                \
    }

/**
 * \brief           dequeue the queue content given array and free the queue.
 * \param[in]       queue: tail that will be emptied and deconstructed.
 * \param[in]       array: array that will contain the dequeued items.
 * \param[in]       index: index used to keep track of the position at which queue items are being inserted in the array.
 * \hideinitializer
 */
#define dequeue_all_to_array(queue, array, index)                                                                      \
    while (!queue_is_empty(queue)) {                                                                                   \
        array[index++] = queue_dequeue(queue);                                                                         \
    }                                                                                                                  \
    queue_clear(&queue);

/**
 * \brief           merges two subarrays of array.
 * \param[in]       array: the array to be sorted
 * \param[in]       low: the starting index of the first subarray.
 * \param[in]       middle: the ending index of the first subarray.
 * \param[in]       high: the ending index of the second subarray.
 * \param[in]       compare: function used to compare two data_types values.
 * \note            this function merges two subarrays [low..middle] and [middle+1..high] into a single sorted subarray.
 *
 */
static void
merge(data_type array[], size_t low, size_t middle, size_t high, data_type_compare_fn compare) {
    size_t index;
    queue_t *buffer1, *buffer2; /* buffers to hold elements for merging */

    enqueue_interval(buffer1, array, low, middle);
    enqueue_interval(buffer2, array, middle + 1, high);

    index = low;
    while (!(queue_is_empty(buffer1) || queue_is_empty(buffer2))) {
        if (compare(queue_peek(buffer1), queue_peek(buffer2)) <= 0) {
            array[index++] = queue_dequeue(buffer1);
        } else {
            array[index++] = queue_dequeue(buffer2);
        }
    }

    dequeue_all_to_array(buffer1, array, index);
    dequeue_all_to_array(buffer2, array, index);
}

/**
 * \brief           sorts an array using merge sort algorithm.
 * \param[in]       array: the array to be sorted.
 * \param[in]       low: the starting index of the portion to be sorted.
 * \param[in]       high: the ending index of the portion to be sorted.
 * \param[in]       compare: function used to compare two data_types values.
 * \note            merge sort is a sorting algorithm that uses the divide-and-conquer approach. It works by dividing an unsorted list into n sublists, 
 *                  each containing one element (a list of one element is considered sorted), then repeatedly merging sublists to produce new sorted sublists 
 *                  until there is only one sublist remaining. This will be the sorted list.
 */
void
merge_sort(data_type array[], size_t low, size_t high, data_type_compare_fn compare) {
    size_t middle; /* index of middle element */

    if (low < high) {
        middle = (low + high) / 2;
        merge_sort(array, low, middle, compare);
        merge_sort(array, middle + 1, high, compare);
        merge(array, low, middle, high, compare);
    }
}

/**
 * \brief           sorts an array using heap sort algorithm.
 * \param[in]       array: the array to be sorted.
 * \param[in]       array_size: the size of the array.
 * \param[in]       compare: function used to compare two data_types values.
 * \note            the heap sort algorithm constructs a heap from the given array and repeatedly extracts elements from it to form a sorted sequence.
 */
void
heap_sort(data_type array[], size_t array_size, data_type_compare_fn compare) {
    heap_t* heap;

    heap = heap_construct_from_array(array, array_size, compare);
    for (size_t i = 0; i < array_size; i++) {
        array[i] = heap_extract(heap);
    }
}

/**
 * \brief           partitions a subarray around a pivot element.
 * \param[in]       array: the array to be partitioned.
 * \param[in]       low: The starting index of the subarray.
 * \param[in]       high: The ending index of the subarray.
 * \param[in]       compare: function used to compare two data_types values.
 * \return          the index of the pivot element after partitioning.
 * \note            this function partitions a subarray [low..high] around a pivot element (selected as the last element of the subarray) such that all elements
 *                  smaller than the pivot are placed before it and all elements greater than or equal to it are placed after it. It returns the index of the 
 *                  pivot element after partitioning.
 */
static size_t
partition(data_type array[], size_t low, size_t high, data_type_compare_fn compare) {
    size_t pivot, high_subarray_start;

    pivot = high;                                  /* select last element as pivot */
    high_subarray_start = low;                     /* select first eleemnt as starting point for the high subarray */
    for (size_t i = low; i < high; i++) {          /* iterate on the given subarray */
        if (compare(array[i], array[pivot]) < 0) { /* if an element smaller than the pivot is found... */
            swap(&array[i], &array[high_subarray_start]); /* ... move it in the low part of the subarray... */
            high_subarray_start++;                        /* ...and update the high subarray starting position */
        }
    }

    swap(&array[pivot], &array[high_subarray_start]); /* move pivot to the first position of high subarray */
    return high_subarray_start;
}

/**
 * \brief           sorts an array of data using the quick sort algorithm.
 * \param[in]       array: the array to be sorted.
 * \param[in]       low: the starting index of the portion of the array to be sorted.
 * \param[in]       high: the ending index of the portion of the array to be sorted.
 * \param[in]       compare: function used to compare two data_types values.
 * \note            Quicksort is an efficient sorting algorithm that uses the divide-and-conquer approach. It works by selecting a ‘pivot’ element from the 
 *                  array and partitioning the other elements into two sub-arrays, according to whether they are less than or greater than the pivot. The 
 *                  function then recursively sorts the sub-arrays.
 */
void
quick_sort(data_type array[], size_t low, size_t high, data_type_compare_fn compare) {
    size_t partition_index;

    if (low < high) {
        partition_index = partition(array, low, high, compare);

        if (partition_index > 0) {
            quick_sort(array, low, partition_index - 1, compare);
        }

        quick_sort(array, partition_index + 1, high, compare);
    }
}