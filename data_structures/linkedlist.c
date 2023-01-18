#include <stdlib.h>
#include "datatype.h"
#include "linkedlist.h"
#include "memalloc.h"

singly_linked_list_t* sllist_construct() {
	return NULL;
}

void sllist_insert(singly_linked_list_t** list, data_type value) {
	singly_linked_list_t* new_node;

	new_node = malloc_s(sizeof(singly_linked_list_t));
	new_node->value = value;
	new_node->next = *list;

	/* insertion at the beginning of the list to achieve a constant time operation */
	*list = new_node;
}

void sllist_delete(singly_linked_list_t** list, singly_linked_list_t* node_to_delete) {
	singly_linked_list_t* node;

	node = *list;
	while (node != node_to_delete) { /* iterate on the list untill we find the node to delete */
		if (node == NULL) { /* we reached the end of the list */
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

singly_linked_list_t* sllist_search(singly_linked_list_t* list, data_type value, data_type_compare_fn compare) {
	if (list == NULL) {
		return NULL;
	}

	if (compare(list->value, value) == 0) {
		return list;
	}
	else {
		return(sllist_search(list->next, value, compare));
	}
}

void sllist_clear(singly_linked_list_t** list) {
	singly_linked_list_t* node_to_free;

	node_to_free = *list;
	while (node_to_free != NULL)
	{
		(*list) = (*list)->next;
		free_s(node_to_free);
		node_to_free = *list;
	}
}

doubly_linked_list_t* dllist_construct() {
	return NULL;
}

void dllist_insert(doubly_linked_list_t** list, data_type value) {
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

void dllist_delete(doubly_linked_list_t** list, doubly_linked_list_t* node_to_delete) {
	doubly_linked_list_t* node;

	node = *list;
	while (node != node_to_delete) { /* iterate on the list untill we find the node to delete */
		if (node == NULL) { /* we reached the end of the list */
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

doubly_linked_list_t* dllist_search(doubly_linked_list_t* list, data_type value, data_type_compare_fn compare) {
	if (list == NULL) {
		return NULL;
	}

	if (compare(list->value, value) == 0) {
		return list;
	}
	else {
		return(dllist_search(list->next, value, compare));
	}
}

void dllist_clear(doubly_linked_list_t** list) {
	doubly_linked_list_t* node_to_free;

	node_to_free = *list;
	while (node_to_free != NULL)
	{
		*list = (*list)->next;
		free_s(node_to_free);
		node_to_free = *list;
	}
}