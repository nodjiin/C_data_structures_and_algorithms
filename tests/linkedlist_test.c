#include "linkedlist_test.h"
#include <assert.h>

void
sllist_construct_test(void) {
    assert(sllist_construct() == NULL);
}

void
sllist_insert_test(void) {
    singly_linked_list_t* list;

    list = sllist_construct();
    sllist_insert(&list, TESTVAL1);
    sllist_insert(&list, TESTVAL2);

    assert(list->value == TESTVAL2);
    assert(list->next->value == TESTVAL1);
    assert(list->next->next == NULL);
}

void
sllist_delete_test(void) {
    singly_linked_list_t* list;

    list = sllist_construct();
    sllist_insert(&list, TESTVAL1);
    sllist_insert(&list, TESTVAL2);
    sllist_insert(&list, TESTVAL3);
    sllist_delete(&list, list->next);

    assert(list->value == TESTVAL3);
    assert(list->next->value == TESTVAL1);
    assert(list->next->next == NULL);
}

void
sllist_search_test(void) {
    singly_linked_list_t *list, *node;

    list = sllist_construct();
    sllist_insert(&list, TESTVAL1);
    sllist_insert(&list, TESTVAL2);
    node = sllist_search(list, TESTVAL1, compare);
    assert(list->next == node);
}

void
sllist_clear_test(void) {
    singly_linked_list_t* list;

    list = sllist_construct();
    sllist_insert(&list, TESTVAL1);
    sllist_clear(&list);

    assert(list == NULL);
}

void
dllist_construct_test(void) {
    assert(dllist_construct() == NULL);
}

void
dllist_insert_test(void) {
    doubly_linked_list_t* list;

    list = dllist_construct();
    dllist_insert(&list, TESTVAL1);
    dllist_insert(&list, TESTVAL2);

    assert(list->value == TESTVAL2);
    assert(list->next->value == TESTVAL1);
    assert(list->next->next == NULL);
    assert(list->next->previous == list);
    assert(list->previous == NULL);
}

void
dllist_delete_test(void) {
    doubly_linked_list_t* list;

    list = dllist_construct();
    dllist_insert(&list, TESTVAL1);
    dllist_insert(&list, TESTVAL2);
    dllist_insert(&list, TESTVAL3);
    dllist_delete(&list, list->next);

    assert(list->value == TESTVAL3);
    assert(list->previous == NULL);
    assert(list->next->value == TESTVAL1);
    assert(list->next->previous == list);
    assert(list->next->next == NULL);
}

void
dllist_search_test(void) {
    doubly_linked_list_t *list, *node;

    list = dllist_construct();
    dllist_insert(&list, TESTVAL1);
    dllist_insert(&list, TESTVAL2);
    node = dllist_search(list, TESTVAL1, compare);

    assert(list->next == node);
}

void
dllist_clear_test(void) {
    doubly_linked_list_t* list;

    list = dllist_construct();
    dllist_insert(&list, TESTVAL1);
    dllist_clear(&list);

    assert(list == NULL);
}

void
linkedlist_testall(void) {
    sllist_construct_test();
    sllist_insert_test();
    sllist_delete_test();
    sllist_search_test();
    sllist_clear_test();

    dllist_construct_test();
    dllist_insert_test();
    dllist_delete_test();
    dllist_search_test();
    dllist_clear_test();
}