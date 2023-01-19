#ifndef LINKEDLIST_TEST
#define LINKEDLIST_TEST

#include "data_structures/linkedlist.h"
#include "testvalues.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void sllist_construct_test(void);
void sllist_insert_test(void);
void sllist_delete_test(void);
void sllist_search_test(void);
void sllist_clear_test(void);

void dllist_construct_test(void);
void dllist_insert_test(void);
void dllist_delete_test(void);
void dllist_search_test(void);
void dllist_clear_test(void);

void linkedlist_testall(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !LINKEDLIST_TEST