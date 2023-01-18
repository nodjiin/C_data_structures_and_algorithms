#ifndef LINKEDLIST
#define LINKEDLIST

#include "datatype.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

	typedef struct singly_linked_list_t {
		data_type value;
		struct singly_linked_list_t* next;
	} singly_linked_list_t;

	typedef struct doubly_linked_list_t {
		data_type value;
		struct doubly_linked_list_t* previous;
		struct doubly_linked_list_t* next;
	} doubly_linked_list_t;

	__declspec(dllexport)
		singly_linked_list_t* sllist_construct();
	__declspec(dllexport)
		void sllist_insert(singly_linked_list_t** list, data_type value);
	__declspec(dllexport)
		void sllist_delete(singly_linked_list_t** list, singly_linked_list_t* node_to_delete);
	__declspec(dllexport)
		singly_linked_list_t* sllist_search(singly_linked_list_t* list, data_type value, data_type_compare_fn compare);
	__declspec(dllexport)
		void sllist_clear(singly_linked_list_t** list);

	__declspec(dllexport)
		doubly_linked_list_t* dllist_construct();
	__declspec(dllexport)
		void dllist_insert(doubly_linked_list_t** list, data_type value);
	__declspec(dllexport)
		void dllist_delete(doubly_linked_list_t** list, doubly_linked_list_t* node_to_delete);
	__declspec(dllexport)
		doubly_linked_list_t* dllist_search(doubly_linked_list_t* list, data_type value, data_type_compare_fn compare);
	__declspec(dllexport)
		void dllist_clear(doubly_linked_list_t** list);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !LINKEDLIST