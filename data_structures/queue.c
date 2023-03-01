/**
 * \file            queue.c
 * \brief           source file containing the definition of queue operations.
 */

#include <stdio.h>
#include <stdlib.h>
#include "core\exitcodes.h"
#include "core\memalloc.h"
#include "queue.h"

/**
 * \brief           construct a new queue.
 * \return          a pointer the newly constructed queue.
 * \relates         queue_t
 */
queue_t*
queue_construct(void) {
    queue_t* new_queue;

    new_queue = malloc_s(sizeof(queue_t));
    new_queue->list = dllist_construct();
    new_queue->first = NULL;
    new_queue->count = 0;

    return new_queue;
}

/**
 * \brief           enqueue the given value.
 * \param[in]       queue: queue pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       value: new value to be enqueued.
 * \relates         queue_t
 */
void
queue_enqueue(queue_t* queue, data_type value) {
    if (queue == NULL) {
        fprintf(stderr, "[queue_enqueue] Invalid input. Faulty enqueue request on NULL queue.\n");
        exit(INVALID_INPUT);
    }

    dllist_insert(&(queue->list), value);
    if (queue->first == NULL) { /* update  reference to the first item is the queue is currently empty*/
        queue->first = queue->list;
    }
    queue->count++;
}

/**
 * \brief           dequeue the first value of the queue.
 * \param[in]       queue: queue pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \return          the first value of the queue.
 * \note            trying to dequeue a value from an empty queue is considered an invalid operation, and will cause an early exit with INVALID_OPERATION status code.
 * \relates         queue_t
 */
data_type
queue_dequeue(queue_t* queue) {
    data_type value;
    doubly_linked_list_t* first;

    if (queue == NULL) {
        fprintf(stderr, "[queue_dequeue] Invalid input. Faulty dequeue request on NULL queue.\n");
        exit(INVALID_INPUT);
    }

    if (queue->first == NULL) {
        fprintf(stderr, "[queue_dequeue] Invalid operation. Faulty dequeue request on empty queue.\n");
        exit(INVALID_OPERATION);
    }

    first = queue->first;                 /* dereference current first node of the queue */
    value = first->value;                 /* save its value in a local variable */
    queue->first = first->previous;       /* set as new first the second node on the queue */
    dllist_delete(&(queue->list), first); /* delete the old first from the internal list */
    queue->count--;

    return value;
}

/**
 * \brief           get the number of elements currently in the queue.
 * \param[in]       queue: queue pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \return          the number of elements in the queue.
 * \relates         queue_t
 */
size_t
queue_count(queue_t* queue) {
    if (queue == NULL) {
        fprintf(stderr, "[queue_count] Invalid input. Faulty count request on NULL queue.\n");
        exit(INVALID_INPUT);
    }

    return queue->count;
}

/**
 * \brief           check if the queue is empty.
 * \param[in]       queue: queue pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \return          true if the queue is empty, false otherwise.
 * \relates         queue_t
 */
bool
queue_is_empty(queue_t* queue) {
    if (queue == NULL) {
        fprintf(stderr, "[queue_is_empty] Invalid input. Faulty empty check request on NULL queue.\n");
        exit(INVALID_INPUT);
    }

    return queue->count == 0;
}

/**
 * \brief           free the given queue.
 * \param[in]       queue: pointer to queue pointer.
 * \note            this function will free the memory used by the queue. The input pointer itself will be set to `NULL`.
 * \relates         queue_t
 */
void
queue_clear(queue_t** queue) {
    if (queue == NULL || *queue == NULL) {
        return;
    }

    dllist_clear(&((*queue)->list));
    free_s(*queue);
}