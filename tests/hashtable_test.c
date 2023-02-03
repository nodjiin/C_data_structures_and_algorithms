#include <assert.h>
#include "hashtable_test.h"
#include "data_structures/hashtable.h"
#include "testvalues.h"

void
htable_construct_test(void) {
    hashtable_t* table;

    table = htable_construct(5, 75, hash, key_compare);

    assert(table != NULL);
    assert(table->buckets != NULL);
    assert(table->count == 0);
    assert(table->capacity == 5);
    assert(table->load_factor == 75);
    assert(table->load_threshold == 3);
    assert(table->hash == hash);
    assert(table->key_compare == key_compare);
}

void
htable_insert_test(void) {
    hashtable_t* table;

    table = htable_construct(5, 75, hash, key_compare);

    htable_insert(table, TESTKEY1, TESTVAL1);
    htable_insert(table, TESTKEY2, TESTVAL2);
    htable_insert(table, TESTKEY3, TESTVAL3); /* collision */
    htable_insert(table, TESTKEY4, TESTVAL4); /* resize */
    htable_insert(table, TESTKEY5, TESTVAL5);
    htable_insert(table, TESTKEY5, TESTVAL6); /* overwrite */

    assert(table->count == 5);
    assert(table->capacity == 11);
    assert(table->load_threshold == 8);

    /* N.B. the followings asserts are based on prediction done using djb2 as hash function */
    assert(table->buckets[1]->pair->value == TESTVAL1);
    assert(table->buckets[3]->pair->value == TESTVAL3);
    assert(table->buckets[4]->pair->value == TESTVAL4);
    assert(table->buckets[5]->pair->value == TESTVAL2);
    assert(table->buckets[5]->next->pair->value == TESTVAL6);
}

void
htable_delete_test(void) {
    hashtable_t* table;

    table = htable_construct(5, 75, hash, key_compare);

    htable_insert(table, TESTKEY1, TESTVAL1);
    htable_insert(table, TESTKEY2, TESTVAL2);
    htable_insert(table, TESTKEY3, TESTVAL3);
    htable_insert(table, TESTKEY4, TESTVAL4);
    htable_insert(table, TESTKEY5, TESTVAL5);

    htable_delete(table, TESTKEY1);
    htable_delete(table, TESTKEY5);
    htable_delete(table, TESTKEY6); /* key not present */

    assert(table->count == 3);
    assert(table->capacity == 11);
    assert(table->load_threshold == 8);
    assert(table->buckets[1] == NULL);
    assert(table->buckets[5]->next == NULL);
}

void
htable_search_test(void) {
    hashtable_t* table;
    data_type stored_val1, stored_val2, missing_val;

    table = htable_construct(5, 75, hash, key_compare);

    htable_insert(table, TESTKEY1, TESTVAL1);
    htable_insert(table, TESTKEY2, TESTVAL2);
    htable_insert(table, TESTKEY3, TESTVAL3);
    htable_insert(table, TESTKEY4, TESTVAL4);
    htable_insert(table, TESTKEY5, TESTVAL5);
    htable_delete(table, TESTKEY3);

    stored_val1 = htable_search(table, TESTKEY1);
    stored_val2 = htable_search(table, TESTKEY2);
    missing_val = htable_search(table, TESTKEY3);

    assert(stored_val1 == TESTVAL1);
    assert(stored_val2 == TESTVAL2);
    assert(missing_val == NULL_DATA);
}

void
htable_clear_test(void) {
    hashtable_t* table;

    table = htable_construct(5, 75, hash, key_compare);
    htable_insert(table, TESTKEY1, TESTVAL1);
    htable_insert(table, TESTKEY2, TESTVAL2);
    htable_insert(table, TESTKEY3, TESTVAL3);
    htable_insert(table, TESTKEY4, TESTVAL4); /* resize */
    htable_insert(table, TESTKEY5, TESTVAL5);

    htable_clear(&table);

    assert(table == NULL);
}

void
hashtable_testall(void) {
    htable_construct_test();
    htable_insert_test();
    htable_delete_test();
    htable_search_test();
    htable_clear_test();
}