/**
 * \file            queue.h
 * \brief           header file containing the declaration of queue data structure, and connected functions.
 */

#ifndef QUEUE
#define QUEUE

#include <stdbool.h>
#include "linkedlist.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief           queue data structure.
 * \note            this implementation uses a singly linked list to store the queue content.
 */
typedef struct {
    singly_linked_list_t* array; /*!< internal data storage */
} queue_t;

__declspec(dllexport) queue_t* queue_construct(size_t initial_size);
__declspec(dllexport) void queue_enqueue(queue_t* queue, data_type value);
__declspec(dllexport) data_type queue_dequeue(queue_t* queue);
__declspec(dllexport) size_t queue_count(queue_t* queue);
__declspec(dllexport) bool queue_is_empty(queue_t* queue);
__declspec(dllexport) void queue_clear(queue_t** queue);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !QUEUE