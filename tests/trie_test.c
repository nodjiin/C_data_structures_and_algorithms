#include <assert.h>
#include "data_structures/trie.h"
#include "trie_test.h"
#include "testvalues.h"

void
trie_construct_test(void) {
    trie_t* trie;

    trie = trie_construct();

    assert(trie != NULL);
    assert(trie->count == 0);
    assert(trie->root != NULL);
    assert(trie->root->children != NULL);
    assert(trie->root->is_terminal == false);
}

void
trie_insert_test(void) {
    trie_t* trie;

    trie = trie_construct();

    trie_insert(trie, TESTTRIEKEY1, TESTVAL1);
    trie_insert(trie, TESTTRIEKEY2, TESTVAL2);
    trie_insert(trie, TESTTRIEKEY3, TESTVAL3);

    assert(trie->count == 3);
    assert(trie->root->children[0]->is_terminal == true);
    assert(trie->root->children[0]->value == TESTVAL1);
    assert(trie->root->children[0]->children[0]->is_terminal == true);
    assert(trie->root->children[0]->children[0]->value == TESTVAL2);
    assert(trie->root->children[1]->is_terminal == true);
    assert(trie->root->children[1]->value == TESTVAL3);
}

void
trie_delete_test(void) {
    trie_t* trie;
    data_type value, value_not_inside;

    trie = trie_construct();
    trie_insert(trie, TESTTRIEKEY1, TESTVAL1);
    trie_insert(trie, TESTTRIEKEY2, TESTVAL2);

    value = trie_delete(trie, TESTTRIEKEY2);
    value_not_inside = trie_delete(trie, TESTTRIEKEY3);

    assert(trie->count == 1);
    assert(trie->root->children[0]->is_terminal == true);
    assert(trie->root->children[0]->value == TESTVAL1);
    assert(trie->root->children[0]->children[0] == NULL);
    assert(value == TESTVAL2);
    assert(value_not_inside == NULL_DATA);
}

void
trie_delete_test2(void) {
    trie_t* trie;
    data_type value;

    trie = trie_construct();
    trie_insert(trie, TESTTRIEKEY1, TESTVAL1);
    trie_insert(trie, TESTTRIEKEY2, TESTVAL2);
    trie_insert(trie, TESTTRIEKEY4, TESTVAL4);

    value = trie_delete(trie, TESTTRIEKEY2);

    assert(trie->count == 2);
    assert(trie->root->children[0]->is_terminal == true);
    assert(trie->root->children[0]->value == TESTVAL1);
    assert(trie->root->children[0]->children[0] != NULL);
    assert(trie->root->children[0]->children[0]->is_terminal == false);
    assert(value == TESTVAL2);
}

void
trie_search_test(void) {
    trie_t* trie;
    data_type value, value_not_inside;

    trie = trie_construct();
    trie_insert(trie, TESTTRIEKEY1, TESTVAL1);
    trie_insert(trie, TESTTRIEKEY2, TESTVAL2);
    trie_insert(trie, TESTTRIEKEY4, TESTVAL4);

    value = trie_search(trie, TESTTRIEKEY2);
    value_not_inside = trie_search(trie, TESTTRIEKEY3);

    assert(trie->count == 3);
    assert(value == TESTVAL2);
    assert(value_not_inside == NULL_DATA);
}

void
trie_clear_test(void) {
    trie_t* trie;

    trie = trie_construct();
    trie_insert(trie, TESTTRIEKEY1, TESTVAL1);
    trie_insert(trie, TESTTRIEKEY2, TESTVAL2);

    trie_clear(&trie);

    assert(trie == NULL);
}

void
trie_testall(void) {
    trie_construct_test();
    trie_insert_test();
    trie_delete_test();
    trie_delete_test2();
    trie_search_test();
    trie_clear_test();
}
