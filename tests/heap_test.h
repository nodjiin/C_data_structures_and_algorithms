#ifndef HEAP_TEST
#define HEAP_TEST

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void heap_construct_test(void);
void heap_construct_from_array_test(void);
void heap_insert_test(void);
void heap_extract_test(void);
void heap_count_test(void);
void heap_is_empty_test(void);
void heap_clear_test(void);

void heap_testall(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !HEAP_TEST