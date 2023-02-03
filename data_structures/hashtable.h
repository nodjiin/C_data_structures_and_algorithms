/**
 * \file            hashtable.h
 * \brief           header file containing the declaration of the hash table data structure and operations.
 */

#ifndef HASHTABLE
#define HASHTABLE

#include <stdlib.h>
#include <stdint.h>
#include "datatype.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief           hash function used to bin a key in the dictionary.
 */
typedef size_t (*hash_key_fn)(key_type key);

/**
 * \brief           key/value pair structure stored in the hash table.
 */
typedef struct {
    key_type key;    /* element that will be hashed to determine the position of the pair in the table */
    data_type value; /* element that will contain the value to store */
} key_value_pair_t;

/**
 * \brief           bucket element, implemented as a doubly linked list node.
 */
typedef struct hashtable_bucket_element_t {
    struct hashtable_bucket_element_t* next;     /*!< pointer to the next element in the bucket */
    struct hashtable_bucket_element_t* previous; /*!< pointer to the previous element in the bucket */
    key_value_pair_t* pair;                      /*!< pair contained in this bucket element */
} hashtable_bucket_element_t;

/**
 * \brief           hash table data structure.
 * \note            the current implementation uses chaining to resolve collisions.
 */
typedef struct {
    hashtable_bucket_element_t** buckets; /*!< array of buckets */
    size_t count;                         /*!< count of item currently present inside the array */
    size_t capacity;                      /*!< current maximum capacity of the hash table */
    uint8_t load_factor;                  /*!< max fill percentage that is accepted before the hash table is resized */
    size_t load_threshold;                /*<! load factor applied to the current capacity*/
    hash_key_fn hash;                     /*!< hash function used when inserting items in the table */
} hashtable_t;

__declspec(dllexport) hashtable_t* htable_construct(size_t initial_capacity, uint8_t load_factor, hash_key_fn hash);
__declspec(dllexport) data_type htable_search(hashtable_t* htable, key_type key);
__declspec(dllexport) void htable_insert(hashtable_t* htable, key_type key, data_type value);
__declspec(dllexport) void htable_delete(hashtable_t* htable, key_type key);
__declspec(dllexport) void htable_clear(hashtable_t** htable);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !HASHTABLE