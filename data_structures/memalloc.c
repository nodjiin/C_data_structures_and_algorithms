#include <stdio.h>
#include <stdlib.h>
#include "exitcodes.h"

void* malloc_s(size_t size) {
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

void* calloc_s(size_t count, size_t size) {
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
	if (new_memory == NULL)
	{
		fprintf(stderr, "[calloc_s] Memory exhausted. Failed to allocate %zu bytes.\n", count * size);
		exit(MEMORY_EXHAUSTED);
	}

	return new_memory;
}

void* realloc_s(void* block, size_t size) {
	void* new_memory;

	if (size == 0) {
		fprintf(stderr, "[realloc_s] Invalid input. Faulty memory reallocation request of size 0.\n");
		exit(INVALID_INPUT);
	}

	new_memory = realloc(block, size); /* realloc acts as malloc for a NULL block, so we allow it as an input */
	if (new_memory == NULL)
	{
		fprintf(stderr, "[realloc_s] Memory exhausted. Failed to reallocate %zu bytes.\n", size);
		exit(MEMORY_EXHAUSTED);
	}

	return new_memory;
}