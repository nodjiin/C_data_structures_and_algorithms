#ifndef LINKEDLIST
#define LINKEDLIST

#include "datatype.h"

typedef struct singly_linked_list_t {
	data_type value;
	struct singly_linked_list_t* next;
} singly_linked_list_t;

typedef struct doubly_linked_list_t {
	data_type value;
	struct doubly_linked_list_t* previous;
	struct doubly_linked_list_t* next;
} doubly_linked_list_t;

singly_linked_list_t* sllist_construct();
void sllist_insert(singly_linked_list_t** list, data_type value);
void sllist_delete(singly_linked_list_t** list, singly_linked_list_t** node_to_delete);
singly_linked_list_t* sllist_search(singly_linked_list_t* list, data_type value);
void sllist_clear(singly_linked_list_t* list);

doubly_linked_list_t* dllist_construct();
void dllist_insert(doubly_linked_list_t** list, data_type value);
void dllist_delete(doubly_linked_list_t** list, doubly_linked_list_t** node_to_delete);
doubly_linked_list_t* dllist_search(doubly_linked_list_t* list, data_type value);
void dllist_clear(doubly_linked_list_t* list);

#endif // !LINKEDLIST