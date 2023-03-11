/**
 * \file            queue.h
 * \brief           header file containing the declaration of the queue data structure and operations.
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
 * \note            this implementation uses a doubly linked list to store the queue content.
 */
typedef struct {
    doubly_linked_list_t* list;  /*!< internal data storage */
    doubly_linked_list_t* first; /*!< first value of the queue */
    size_t count;                /*!< number of values currently inside the queue */
} queue_t;

__declspec(dllexport) queue_t* queue_construct(void);
__declspec(dllexport) void queue_enqueue(queue_t* queue, data_type value);
__declspec(dllexport) data_type queue_dequeue(queue_t* queue);
__declspec(dllexport) data_type queue_peek(queue_t* queue);
__declspec(dllexport) size_t queue_count(queue_t* queue);
__declspec(dllexport) bool queue_is_empty(queue_t* queue);
__declspec(dllexport) void queue_clear(queue_t** queue);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !QUEUE