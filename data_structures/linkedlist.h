/**
 * \file            linkedlist.h
 * \brief           header file containing the declaration of singly & doubly linked list data structures and operations.
 */

#ifndef LINKEDLIST
#define LINKEDLIST

#include "datatype.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief           singly linked list structure.
 * \note            this implementation joins list and node in a single structure. It is up to the user to maintain a reference to the head.
 */
typedef struct singly_linked_list_t {
    data_type value;                   /*!< value of the node */
    struct singly_linked_list_t* next; /*!< pointer to the next node of the list */
} singly_linked_list_t;

/**
 * \brief           doubly linked list structure.
 * \note            this implementation joins list and node in a single structure. It is up to the user to maintain a reference to the head.
 */
typedef struct doubly_linked_list_t {
    data_type value;                       /*!< value of the node */
    struct doubly_linked_list_t* previous; /*!< pointer to the previous node of the list */
    struct doubly_linked_list_t* next;     /*!< pointer to the next node of the list */
} doubly_linked_list_t;

__declspec(dllexport) singly_linked_list_t* sllist_construct();
__declspec(dllexport) void sllist_insert(singly_linked_list_t** list, data_type value);
__declspec(dllexport) void sllist_delete(singly_linked_list_t** list, singly_linked_list_t* node_to_delete);
__declspec(dllexport) singly_linked_list_t* sllist_search(singly_linked_list_t* list, data_type value,
                                                          data_type_compare_fn compare);
__declspec(dllexport) void sllist_clear(singly_linked_list_t** list);

__declspec(dllexport) doubly_linked_list_t* dllist_construct();
__declspec(dllexport) void dllist_insert(doubly_linked_list_t** list, data_type value);
__declspec(dllexport) void dllist_delete(doubly_linked_list_t** list, doubly_linked_list_t* node_to_delete);
__declspec(dllexport) doubly_linked_list_t* dllist_search(doubly_linked_list_t* list, data_type value,
                                                          data_type_compare_fn compare);
__declspec(dllexport) void dllist_clear(doubly_linked_list_t** list);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !LINKEDLIST