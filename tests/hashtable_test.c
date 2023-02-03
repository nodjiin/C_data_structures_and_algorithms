#include <assert.h>
#include "data_structures/hashtable.h"

void htable_construct_test(void){ assert(0);}
void htable_insert_test(void){ assert(0);}
void htable_delete_test(void){ assert(0);}
void htable_search_test(void){ assert(0);}
void htable_clear_test(void){ assert(0);}

void
hashtable_testall(void) {
    htable_construct_test();
    htable_insert_test();
    htable_delete_test();
    htable_search_test();
    htable_clear_test();
}