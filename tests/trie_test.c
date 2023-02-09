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
}

void
trie_insert_test(void) {
    assert(0);
}

void
trie_delete_test(void) {
    assert(0);
}

void
trie_search_test(void) {
    assert(0);
}

void
trie_clear_test(void) {
    assert(0);
}

void
trie_testall(void) {
    trie_construct_test();
    trie_insert_test();
    trie_delete_test();
    trie_search_test();
    trie_clear_test();
}
