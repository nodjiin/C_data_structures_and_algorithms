#include <stdlib.h>
#include "linkedlist_test.h"
#include "dynamicarray_test.h"
#include "stack_test.h"
#include "queue_test.h"
#include "heap_test.h"
#include "binarysearchtree_test.h"
#include "hashtable_test.h"
#include "trie_test.h"
#include "graph_test.h"
#include "search_test.h"

/* TODO
 *	Most test procedures currently allocate memory without releasing it. Given the fairly limited scope of data used this is not a problem,
 *	and the tests themselves run faster not having to waste time freeing the used memory. In the future it might be interesting to implement
 *	true atomic setup and teardown procedures, maybe calling them in a wrapper function of the individual test methods
 */

int
main(void) {
    linkedlist_testall();
    dynamicarray_testall();
    stack_testall();
    queue_testall();
    heap_testall();
    bstree_testall();
    hashtable_testall();
    trie_testall();
    graph_testall();
    search_testall();

    exit(0);
}