/**
 * \file            linkedlist.c
 * \brief           source file containing the definition of singly & doubly linked list connected functions.
 */

#include <stdlib.h>
#include "datatype.h"
#include "linkedlist.h"
#include "memalloc.h"

/**
  * \brief          construct a new singly linked list.
  * \note           since the curent implementation uses a single structure to contain both the nodes and the list itself, a simple NULL pointer will be returned.
  * \return         a pointer to head of the newly constructed linked list.
  */
singly_linked_list_t*
sllist_construct() {
    return NULL;
}

/**
 * \brief           insert a new item at the beginning of the linked list.
 * \param[in]       list: a pointer to a pointer of the list head.
 * \param[in]       value: the new value to insert.
 */
void
sllist_insert(singly_linked_list_t** list, data_type value) {
    singly_linked_list_t* new_node;

    new_node = malloc_s(sizeof(singly_linked_list_t));
    new_node->value = value;
    new_node->next = *list;

    /* insertion at the beginning of the list to achieve a constant time operation */
    *list = new_node;
}

/**
 * \brief           delete a node from the list.
 * \note            node_to_delete will always be freed, even if it was not found in the given list.
 * \param[in]       list: a pointer to a pointer of the list head.
 * \param[in]       node_to_delete: a pointer to the node of the list to delete.
 */
void
sllist_delete(singly_linked_list_t** list, singly_linked_list_t* node_to_delete) {
    singly_linked_list_t* node;

    node = *list;
    while (node != node_to_delete) { /* iterate on the list untill we find the node to delete */
        if (node == NULL) {          /* we reached the end of the list */
            free_s(node_to_delete);
            return;
        }

        node = node->next;
    }

    if (node == NULL) {
        return;
    }

    if (node->next == NULL) {
        list = NULL;
        return;
    }

    /* delete the node by overriding it with the next node of the list */
    node->value = node->next->value;
    node_to_delete = node->next;
    node->next = node->next->next;
    free_s(node_to_delete);
}

/**
 * \brief           search a value in the given list.
 * \param[in]       list: a pointer to the list head.
 * \param[in]       value: value to search.
 * \param[in]       compare: function to use to compare the input value and the content of the list nodes.
 * \param[in]       node_to_delete: a pointer to the node of the list containing the value. If none is found `NULL` will be returned instead.
 */
singly_linked_list_t*
sllist_search(singly_linked_list_t* list, data_type value, data_type_compare_fn compare) {
    if (list == NULL) {
        return NULL;
    }

    if (compare(list->value, value) == 0) {
        return list;
    } else {
        return (sllist_search(list->next, value, compare));
    }
}

/**
 * \brief           free all the elements contained in the list.
 * \note            the input pointer will be set to `NULL`.
 * \param[in]       list: a pointer to a pointer of the list head.
 */
void
sllist_clear(singly_linked_list_t** list) {
    singly_linked_list_t* node_to_free;

    node_to_free = *list;
    while (node_to_free != NULL) {
        (*list) = (*list)->next;
        free_s(node_to_free);
        node_to_free = *list;
    }
}

/**
 * \brief           construct a new doubly linked list.
 * \note            since the curent implementation uses a single structure to contain both the nodes and the list itself, a simple NULL pointer will be returned.
 * \return          a pointer to head of the newly constructed linked list.
 */
doubly_linked_list_t*
dllist_construct() {
    return NULL;
}

/**
 * \brief           insert a new item at the beginning of the linked list.
 * \param[in]       list: a pointer to a pointer of the list head.
 * \param[in]       value: the new value to insert.
 */
void
dllist_insert(doubly_linked_list_t** list, data_type value) {
    doubly_linked_list_t* new_node;

    new_node = malloc_s(sizeof(doubly_linked_list_t));
    new_node->value = value;
    new_node->next = *list;
    new_node->previous = NULL;
    if (*list != NULL) {
        (*list)->previous = new_node;
    }

    /* insertion at the beginning of the list to achieve a constant time operation */
    *list = new_node;
}

/**
 * \brief           delete a node from the list.
 * \note            node_to_delete will always be freed, even if it was not found in the given list.
 * \param[in]       list: a pointer to a pointer of the list head.
 * \param[in]       node_to_delete: a pointer to the node of the list to delete.
 */
void
dllist_delete(doubly_linked_list_t** list, doubly_linked_list_t* node_to_delete) {
    doubly_linked_list_t* node;

    node = *list;
    while (node != node_to_delete) { /* iterate on the list untill we find the node to delete */
        if (node == NULL) {          /* we reached the end of the list */
            free_s(node_to_delete);
            return;
        }

        node = node->next;
    }

    if (node == NULL) {
        return;
    }

    if (node->next == NULL) {
        list = NULL;
        return;
    }

    /* delete the node by overriding it with the next node of the list */
    node->value = node->next->value;
    node_to_delete = node->next;
    node->next = node->next->next;
    if (node->next != NULL) {
        node->next->previous = node;
    }
    free_s(node_to_delete);
}

/**
 * \brief           search a value in the given list.
 * \param[in]       list: a pointer to the list head.
 * \param[in]       value: value to search.
 * \param[in]       compare: function to use to compare the input value and the content of the list nodes.
 * \param[in]       node_to_delete: a pointer to the node of the list containing the value. If none is found `NULL` will be returned instead.
 */
doubly_linked_list_t*
dllist_search(doubly_linked_list_t* list, data_type value, data_type_compare_fn compare) {
    if (list == NULL) {
        return NULL;
    }

    if (compare(list->value, value) == 0) {
        return list;
    } else {
        return (dllist_search(list->next, value, compare));
    }
}

/**
 * \brief           free all the elements contained in the list.
 * \note            the input pointer will be set to `NULL`.
 * \param[in]       list: a pointer to a pointer of the list head.
 */
void
dllist_clear(doubly_linked_list_t** list) {
    doubly_linked_list_t* node_to_free;

    node_to_free = *list;
    while (node_to_free != NULL) {
        *list = (*list)->next;
        free_s(node_to_free);
        node_to_free = *list;
    }
}