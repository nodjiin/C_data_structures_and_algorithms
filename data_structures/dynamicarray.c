/**
 * \file            dynamicarray.c
 * \brief           source file containing the definition dynamic array connected functions.
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "dynamicarray.h"
#include "memalloc.h"
#include "exitcodes.h"

/**
 * \brief           construct a new dynamic array.
 * \param[in]       initial_size: number of items that the array will be able to contain after initialization. 0 is not considered a valid input, 
 *                  and will result a program early exit with INVALID_INPUT code.
 * \return          a pointer the newly constructed array.
 */
dynamic_array_t*
darray_construct(size_t initial_size) {
    dynamic_array_t* new_array;

    if (initial_size == 0) {
        fprintf(stderr, "[darray_construct] Invalid input. Faulty construct request with size 0.\n");
    }

    new_array = malloc_s(sizeof(dynamic_array_t));
    new_array->array = malloc_s(sizeof(data_type) * initial_size);
    new_array->count = 0;
    new_array->length = initial_size;
    return new_array;
}

/**
 * \brief           double the length of the given array.
 * \param[in]       darray: dynamic array pointer.
 */
static void
double_length(dynamic_array_t* darray) {
    darray->length *= 2;
    darray->array = realloc_s(darray->array, sizeof(data_type) * darray->length);
}

/**
 * \brief           insert the given item inside the first free position of the array.
 * \param[in]       darray: dynamic array pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       value: new value to be inserted in the array.
 * \note            this function will try to double the array length if its current size is not enough to contain the new item. 
 *                  This might lead to the program exiting early if not enough memory is available.
 */
void
darray_insert(dynamic_array_t* darray, data_type value) {
    if (darray == NULL) {
        fprintf(stderr, "[darray_insert] Invalid input. Faulty insertion request on NULL array.\n");
        exit(INVALID_INPUT);
    }

    if (darray->count == darray->length) {
        double_length(darray);
    }

    darray->array[darray->count] = value;
    darray->count++;
}

/**
 * \brief           insert the given item in the first position of the array, shifting all the other elements right.
 * \param[in]       darray: dynamic array pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       value: new value to be inserted in the array.
 * \note            this function will try to double the array length if its current size is not enough to contain the new item. 
 *                  This might lead to the program exiting early if not enough memory is available.
 *                  This function running time is 0(n), where n is the current count of the array, as each insertion require a shift of all the existing elements.
 */
void
darray_insert_head(dynamic_array_t* darray, data_type value) {
    if (darray == NULL) {
        fprintf(stderr, "[darray_insert_head] Invalid input. Faulty insertion request on NULL array.\n");
        exit(INVALID_INPUT);
    }

    if (darray->count == darray->length) {
        double_length(darray);
    }

    for (size_t i = 0; i < darray->count; i++) {
        darray->array[i + 1] = darray->array[i];
    }

    darray->array[0] = value;
    darray->count++;
}

/**
 * \brief           insert the given item in the given position of the array, shifting all the remaining elements right.
 * \param[in]       darray: dynamic array pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       value: new value to be inserted in the array.
 * \param[in]       index: index to use for new element insertion. The value of the index has to be taken from the current spawn of the array. A value greater than the current
 *                  number of items in the array will cause an early exit with invalid input code.
 * \note            this function will try to double the array length if its current size is not enough to contain the new item. 
 *                  This might lead to the program exiting early if not enough memory is available.
 *					This function running time is 0(n - index), where n is the current count of the array, as each insertion require a shift of all the existing elements
 *                  located right to the index.
 */
void
darray_insert_at(dynamic_array_t* darray, data_type value, size_t index) {
    if (darray == NULL) {
        fprintf(stderr, "[darray_insert_at] Invalid input. Faulty insertion request on NULL array.\n");
        exit(INVALID_INPUT);
    }

    if (index >= darray->count) {
        fprintf(stderr,
                "[darray_insert_at] Invalid input. Faulty insertion request at position '%zu'"
                "while only '%zu' elements are currently stored in the array.\n",
                index, darray->count);
        exit(INVALID_INPUT);
    }

    if (darray->count == darray->length) {
        double_length(darray);
    }

    /* shift right of one position all elements from the index to the end of the array */
    for (size_t i = index; i < darray->count; i++) {
        darray->array[i + 1] = darray->array[i];
    }

    darray->array[index] = value;
    darray->count++;
}

/**
 * \brief           override an item already present at the given position in the array with the new value.
 * \param[in]       darray: dynamic array pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       value: new value to be put in the array, overriding an existing one.
 * \param[in]       index: index to use for value override. The value of the index has to be taken from the current spawn of the array. A value greater than the current
 *                  number of items in the array will cause an early exit with invalid input code.
 */
void
darray_put(dynamic_array_t* darray, data_type value, size_t index) {
    if (darray == NULL) {
        fprintf(stderr, "[darray_put] Invalid input. Faulty put request on NULL array.\n");
        exit(INVALID_INPUT);
    }

    if (index >= darray->count) {
        fprintf(stderr,
                "[darray_put] Invalid input. Faulty put request at position '%zu'"
                "while only '%zu' elements are currently stored in the array.\n",
                index, darray->count);
        exit(INVALID_INPUT);
    }

    darray->array[index] = value;
}

/**
 * \brief           get a value at the given position in the array.
 * \param[in]       darray: dynamic array pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       index: index to use. The value of the index has to be taken from the current spawn of the array. A value greater than the current
 *                  number of items in the array will cause an early exit with invalid input code.
 * \return          the value stored at the given index.
 * \note            this function won't remove the item from the array.
 */
data_type
darray_get(dynamic_array_t* darray, size_t index) {
    if (darray == NULL) {
        fprintf(stderr, "[darray_get] Invalid input. Faulty get request on NULL array.\n");
        exit(INVALID_INPUT);
    }

    if (index >= darray->count) {
        fprintf(stderr,
                "[darray_get] Invalid input. Faulty get request at position '%zu'"
                "while only '%zu' elements are currently stored in the array.\n",
                index, darray->count);
        exit(INVALID_INPUT);
    }

    return darray->array[index];
}

/**
 * \brief           remove and return an item at the given position in the array.
 * \param[in]       darray: dynamic array pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       index: index to use. The value of the index has to be taken from the current spawn of the array. A value greater than the current
 *                  number of items in the array will cause an early exit with invalid input code.
 * \return          the value stored at the given index.
 * \note            this function will try to halve the array length if the number of internal values dropped to a quarter of its length. Any error in the
 *                  resize operation will cause the program to exit early with a MEMORY_EXAHUSTED code.
 */
data_type
darray_remove(dynamic_array_t* darray, size_t index) {
    data_type value;

    if (darray == NULL) {
        fprintf(stderr, "[darray_remove] Invalid input. Faulty remove request on NULL array.\n");
        exit(INVALID_INPUT);
    }

    if (index >= darray->count) {
        fprintf(stderr,
                "[darray_remove] Invalid input. Faulty remove request at position '%zu'"
                "while only '%zu' elements are currently stored in the array.\n",
                index, darray->count);
        exit(INVALID_INPUT);
    }

    /* get value and shift left of one position all the remaining right values */
    value = darray->array[index];
    for (size_t i = index; i < (darray->count - 1); i++) {
        darray->array[index] = darray->array[index + 1];
    }
    darray->count--;

    /* halve array size if the array counts drops to a quarter of its length */
    size_t min_length = darray->length / 4;
    if (darray->count < min_length && min_length > 0) {
        darray->length = min_length;
        darray->array = realloc_s(darray->array, sizeof(data_type) * min_length);
    }

    return value;
}

/**
 * \brief           search a value inside the array and return its index.
 * \param[in]       darray: dynamic array pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       value: value to search.
 * \param[in]       compare: function to use to compare 2 data_type.
 * \return          the index where the value is stored. `SIZE_MAX` will be returned if the value has not been found in the array.
 */
size_t
darray_search(dynamic_array_t* darray, data_type value, data_type_compare_fn compare) {
    size_t index;

    if (darray == NULL) {
        fprintf(stderr, "[darray_search] Invalid input. Faulty search request on NULL array.\n");
        exit(INVALID_INPUT);
    }

    index = 0;
    while (index < darray->count) {
        if (compare(darray->array[index], value) == 0) {
            return index;
        }

        index++;
    }

    return SIZE_MAX;
}

/**
 * \brief           free the given array.
 * \param[in]       darray: dynamic array pointer.
 * \note            this function will free the memory used by the dynamic array. The input pointer itself will be set to `NULL`.
 */
void
darray_clear(dynamic_array_t** darray) {
    if (darray == NULL || *darray == NULL) {
        return;
    }

    free_s((*darray)->array);
    free_s(*darray);
}