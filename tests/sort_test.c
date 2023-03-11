#include <assert.h>
#include "algorithms/sort.h"
#include "sort_test.h"
#include "testvalues.h"

#define ARRAY_SIZE 9
#define is_sorted(array)                                                                                               \
    (array[0] == TESTVAL1 && array[1] == TESTVAL2 && array[2] == TESTVAL3 && array[3] == TESTVAL4                      \
     && array[4] == TESTVAL5 && array[5] == TESTVAL6 && array[6] == TESTVAL7 && array[7] == TESTVAL8                   \
     && array[8] == TESTVAL9)

data_type array_to_sort[ARRAY_SIZE];

static void
setup() {
    array_to_sort[0] = TESTVAL9;
    array_to_sort[1] = TESTVAL2;
    array_to_sort[2] = TESTVAL4;
    array_to_sort[3] = TESTVAL6;
    array_to_sort[4] = TESTVAL1;
    array_to_sort[5] = TESTVAL3;
    array_to_sort[6] = TESTVAL5;
    array_to_sort[7] = TESTVAL8;
    array_to_sort[8] = TESTVAL7;
}

static void
setup_and_run(void (*test)(void)) {
    setup();
    test();
}

void
selection_sort_test(void) {
    selection_sort(array_to_sort, ARRAY_SIZE);

    assert(is_sorted(array_to_sort));
}

void
insertion_sort_test(void) {
    insertion_sort(array_to_sort, ARRAY_SIZE);

    assert(is_sorted(array_to_sort));
}

void
bubble_sort_test(void) {
    bubble_sort(array_to_sort, ARRAY_SIZE);

    assert(is_sorted(array_to_sort));
}

void
merge_sort_test(void) {
    merge_sort(array_to_sort, 0, ARRAY_SIZE - 1);

    assert(is_sorted(array_to_sort));
}

void
sort_testall(void) {
    setup_and_run(selection_sort_test);
    setup_and_run(insertion_sort_test);
    setup_and_run(bubble_sort_test);
    setup_and_run(merge_sort_test);
}