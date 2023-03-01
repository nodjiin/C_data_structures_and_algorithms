/**
 * \file            memalloc.h
 * \brief           header file containing the declaration of the memory management wrapper functions used in this library.
 */

#ifndef MEMALLOC
#define MEMALLOC

/**
 * \brief           free the given memory block, setting the input parameter to `NULL`.
 * \param[in]       block: memory block to free.
 * \hideinitializer
 */
#define free_s(block)                                                                                                  \
    do {                                                                                                               \
        free((block));                                                                                                 \
        (block) = NULL;                                                                                                \
    } while (0);

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

__declspec(dllexport) void* malloc_s(size_t size);
__declspec(dllexport) void* calloc_s(size_t count, size_t size);
__declspec(dllexport) void* realloc_s(void* block, size_t size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !MEMALLOC
