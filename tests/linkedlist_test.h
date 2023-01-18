#ifndef LINKEDLIST_TEST
#define LINKEDLIST_TEST

#include "data_structures/linkedlist.h"

#define TESTVAL1 1
#define TESTVAL2 2
#define TESTVAL3 3

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


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !LINKEDLIST_TEST