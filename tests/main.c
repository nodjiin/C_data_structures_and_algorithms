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