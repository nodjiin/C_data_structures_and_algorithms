#ifndef MEMALLOC
#define MEMALLOC

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

	void* malloc_s(size_t size);
	void* calloc_s(size_t count, size_t size);
	void* realloc_s(void* block, size_t size);
	void free_s(void* block);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !MEMALLOC
