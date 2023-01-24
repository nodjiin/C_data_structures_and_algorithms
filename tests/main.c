#include <stdlib.h>
#include "linkedlist_test.h"
#include "dynamicarray_test.h"
#include "stack_test.h"
#include "queue_test.h"
#include "heap_test.h"
#include "binarysearchtree_test.h"

int
main(void) {
    linkedlist_testall();
    dynamicarray_testall();
    stack_testall();
    queue_testall();
    heap_testall();
    bstree_testall();

    exit(0);
}