#include <assert.h>
#include "data_structures/queue.h"
#include "queue_test.h"
#include "testvalues.h"

void
queue_construct_test(void) {
    queue_t* queue;

    queue = queue_construct();

    assert(queue != NULL);
    assert(queue->first == NULL);
    assert(queue->list == NULL);
    assert(queue->count == 0);
}

void
queue_enqueue_test(void) {
    queue_t* queue;

    queue = queue_construct();
    queue_enqueue(queue, TESTVAL1);
    queue_enqueue(queue, TESTVAL2);

    assert(queue->count == 2);
    assert(queue->first->value == TESTVAL1);
    assert(queue->list->value == TESTVAL2);
}

void
queue_dequeue_test(void) {
    queue_t* queue;
    data_type deq1, deq2;

    queue = queue_construct();
    queue_enqueue(queue, TESTVAL1);
    queue_enqueue(queue, TESTVAL2);

    deq1 = queue_dequeue(queue);
    deq2 = queue_dequeue(queue);

    assert(queue->count == 0);
    assert(deq1 == TESTVAL1);
    assert(deq2 == TESTVAL2);
}

void
queue_count_test(void) {
    queue_t* queue;
    size_t count;

    queue = queue_construct();
    queue_enqueue(queue, TESTVAL1);
    queue_enqueue(queue, TESTVAL2);

    count = queue_count(queue);

    assert(count == 2);
}

void
queue_is_empty_test(void) {
    queue_t* queue;
    bool is_empty_pre_enqueue, is_empty_after_enqueue;

    queue = queue_construct();

    is_empty_pre_enqueue = queue_is_empty(queue);
    queue_enqueue(queue, TESTVAL1);
    is_empty_after_enqueue = queue_is_empty(queue);

    assert(is_empty_pre_enqueue);
    assert(!is_empty_after_enqueue);
}

void
queue_clear_test(void) {
    queue_t* queue;

    queue = queue_construct();
    queue_enqueue(queue, TESTVAL1);
    queue_enqueue(queue, TESTVAL2);

    queue_clear(&queue);

    assert(queue == NULL);
}

void
queue_testall(void) {
    queue_construct_test();
    queue_enqueue_test();
    queue_dequeue_test();
    queue_count_test();
    queue_is_empty_test();
    queue_clear_test();
}