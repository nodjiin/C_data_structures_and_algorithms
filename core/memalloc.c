/**
 * \file            memalloc.c
 * \brief           header file containing the definition of the memory management wrapper functions used in this library.
 * \note            this library is built targeting code exercises / small test applications, and so it will follow a crash early approach
 *                  rather than try to implement a true fault tolerance policy.
 */

#include <stdio.h>
#include <stdlib.h>
#include "exitcodes.h"
#include "memalloc.h"

/**
  * \brief          allocate a new memory block of requested size.
  * \note           failing to allocate the requested memory will result in the program to exit with a MEMORY_EXHAUSTED code.
  * \param[in]      size: bytes of memory to allocate. `0` is not considered as a valid input and will cause the program to exit with an INVALID_INPUT code.
  * \return         a pointer to the newly allocated memory.
  */
void*
malloc_s(size_t size) {
    void* new_memory;

    if (size == 0) {
        fprintf(stderr, "[malloc_s] Invalid input. Faulty allocation request of size 0.\n");
        exit(INVALID_INPUT);
    }

    new_memory = malloc(size);
    if (new_memory == NULL) {
        fprintf(stderr, "[malloc_s] Memory exhausted. Failed to allocate %zu bytes.\n", size);
        exit(MEMORY_EXHAUSTED);
    }

    return new_memory;
}

/**
 * \brief           allocate a new memory block of requested size and then initialize it to `0`.
 * \note            failing to allocate the requested memory will result in the program to exit with a MEMORY_EXHAUSTED code.
 * \param[in]       count: number of objects to allocate. `0` is not considered as a valid input and will cause the program to exit with an INVALID_INPUT code.
 * \param[in]       size: bytes necessary to contain one of the allocated objects. `0` is not considered as a valid input and will cause the program to exit with an INVALID_INPUT code.
 * \return          a pointer to the newly allocated memory.
 */
void*
calloc_s(size_t count, size_t size) {
    void* new_memory;

    if (count == 0) {
        fprintf(stderr, "[calloc_s] Invalid input. Faulty memory allocation request of 0 items.\n");
        exit(INVALID_INPUT);
    }

    if (size == 0) {
        fprintf(stderr, "[calloc_s] Invalid input. Faulty memory allocation request of %zu items of size 0.\n", count);
        exit(INVALID_INPUT);
    }

    new_memory = calloc(count, size);
    if (new_memory == NULL) {
        fprintf(stderr, "[calloc_s] Memory exhausted. Failed to allocate %zu bytes.\n", count * size);
        exit(MEMORY_EXHAUSTED);
    }

    return new_memory;
}

/**
 * \brief           resize an existing memory block to the given value.
 * \note            failing to resize the memory block will result in the program to exit with a MEMORY_EXHAUSTED code.
 * \param[in]       block: memory block to resize. in case `NULL` is provided as input the function will act as a malloc_s would.
 * \param[in]       size: bytes of memory to allocate. `0` is not considered as a valid input and will cause the program to exit with an INVALID_INPUT code.
 * \return          a pointer to the newly allocated memory.
 */
void*
realloc_s(void* block, size_t size) {
    void* new_memory;

    if (size == 0) {
        fprintf(stderr, "[realloc_s] Invalid input. Faulty memory reallocation request of size 0.\n");
        exit(INVALID_INPUT);
    }

    new_memory = realloc(block, size); /* realloc acts as malloc for a NULL block, so we allow it as an input */
    if (new_memory == NULL) {
        fprintf(stderr, "[realloc_s] Memory exhausted. Failed to reallocate %zu bytes.\n", size);
        exit(MEMORY_EXHAUSTED);
    }

    return new_memory;
}
