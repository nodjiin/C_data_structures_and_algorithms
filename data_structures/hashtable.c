/**
 * \file            hashtable.c
 * \brief           source file containing the definition of hash table operations.
 */

#include <stdio.h>
#include "exitcodes.h"
#include "hashtable.h"
#include "memalloc.h"
#include "hashtable_primes.h"

/**
 * \brief           get the first prime number greater than the given value, stored in the internal collection.
 * \param[in]       size: a numeric value.
 * \return          a prime number greater than value, or `SIZE_MAX` if none was found.
 */
static size_t
get_prime(size_t value) {
    for (size_t i = 0; i < PRIME_NUMBERS_64BIT; i++) {
        if (hashtable_primes[i] >= value) {
            return hashtable_primes[i];
        }
    }

    return SIZE_MAX;
}

/**
 * \brief           updated the load threshold associated with the given hash table.
 * \param[in]       htable: pointer to an hash table.
 * \note            the load threshold is calculated as a percentage of its current capacity, determined by the load factor.
 */
static void
update_load_threshold(hashtable_t* htable) {
    htable->load_threshold = (htable->load_factor * htable->capacity) / 100;
}

/**
 * \brief           construct a new hash table.
 * \param[in]       initial_capacity: number of items that the hash table will be able to contain after initialization. 0 is not considered a valid input, 
 *                  and will result a program early exit with INVALID_INPUT code. If the value is not one of the prime numbers listed inside the array `hashtable_prime_sizes`
 *                  of `hashtable_primes.h` the real capacity will be larger than expected, as the first prime greater than initial_capacity will be used instead.
 * \param[in]       load_factor: measure that decides when to increase the hash table capacity. Once the ratio of elements in the table to current capacity exceeds the load 
 *                  factor, a resize operation is performed. A common value for this parameter (used even by Java standard HashMap implementation) is 75. 0 is not considered 
 *                  a valid input, and will result a program early exit with INVALID_INPUT code.
 * \param[in]       hash: hash function which will be used to insert new values in the table.
 * \return          a pointer the newly constructed hash table.
 */
hashtable_t*
htable_construct(size_t initial_capacity, uint8_t load_factor, hash_key_fn hash, key_type_compare_fn key_compare) {
    hashtable_t* new_hashtable;
    size_t real_size;

    if (initial_capacity == 0) {
        fprintf(stderr, "[htable_construct] Invalid input. Faulty construct request with size 0.\n");
        exit(INVALID_INPUT);
    }

    if (load_factor == 0) {
        fprintf(stderr,
                "[htable_construct] Invalid input. Faulty construct request with invalid load factor: '%hhu'.\n",
                load_factor);
        exit(INVALID_INPUT);
    }

    if (hash == NULL) {
        fprintf(stderr, "[htable_construct] Invalid input. Faulty construct request with NULL hash function.\n");
        exit(INVALID_INPUT);
    }

    if (key_compare == NULL) {
        fprintf(stderr, "[htable_construct] Invalid input. Faulty construct request with NULL key compare function.\n");
        exit(INVALID_INPUT);
    }

    real_size = get_prime(initial_capacity);
    new_hashtable = malloc_s(sizeof(hashtable_t));
    new_hashtable->buckets = calloc_s(real_size, sizeof(hashtable_bucket_element_t*));
    new_hashtable->count = 0;
    new_hashtable->capacity = real_size;
    new_hashtable->load_factor = load_factor;
    new_hashtable->hash = hash;
    new_hashtable->key_compare = key_compare;
    update_load_threshold(new_hashtable);

    return new_hashtable;
}

/**
 * \brief           get the index of the value corresponding to the given key.
 * \param[in]       htable: pointer to a table.
 * \param[in]       key: key used to obtain the index.
 * \return          a numerical value representing the index of the bucket.
 */
static size_t
get_bucket_index(hashtable_t* htable, key_type key) {
    return htable->hash(key) % htable->capacity;
}

/**
 * \brief           create a new bucket element.
 * \param[in]       key: key to insert in the pair structure contained in the element.
 * \param[in]       value: value to insert in the pair structure contained in the element.
 * \return          the newly created element.
 */
static hashtable_bucket_element_t*
construct_bucket_element(key_type key, data_type value) {
    hashtable_bucket_element_t* bucket_element;
    key_value_pair_t* pair;

    pair = malloc_s(sizeof(key_value_pair_t));
    pair->key = key;
    pair->value = value;

    bucket_element = malloc_s(sizeof(hashtable_bucket_element_t));
    bucket_element->pair = pair;
    bucket_element->next = NULL;
    bucket_element->previous = NULL;

    return bucket_element;
}

/**
 * \brief           resize the given hash table, and rehash its content.
 * \param[in]       htable: pointer to the hash table.
 * \param[in]       new_size: new capacity of the resized table.
 */
static void
resize_table(hashtable_t* htable, size_t new_size) {
    hashtable_bucket_element_t **new_buckets, *element;
    size_t original_capacity, rehash_index;

    new_buckets = calloc_s(new_size, sizeof(hashtable_bucket_element_t*));
    original_capacity = htable->capacity;
    htable->capacity = new_size;

    /* rehash */
    for (size_t i = 0; i < original_capacity; i++) {
        element = htable->buckets[i];

        while (element != NULL) {
            hashtable_bucket_element_t* next;

            next = element->next;
            rehash_index = get_bucket_index(htable, element->pair->key);

            if (new_buckets[rehash_index] == NULL) {
                element->previous = NULL;
                element->next = NULL;
                new_buckets[rehash_index] = element;
            } else { /* insert as head of the list to speed up the operation */
                element->previous = NULL;
                element->next = new_buckets[rehash_index];
                new_buckets[rehash_index]->previous = element;
                new_buckets[rehash_index] = element;
            }

            element = next;
        }
    }

    free(htable->buckets);
    htable->buckets = new_buckets;
    update_load_threshold(htable);
}

/**
 * \brief           insert a new key/value pair in the hash table.
 * \param[in]       htable: pointer to the hash table. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       key: key of the value. Performing an inserting operation with a key already contained inside the table will cause the existing value to be overwritten.
 * \param[in]       value: value to insert.
 * \note            this function will try to increase the table capacity if the number of internal elements stored surpasses the load_threshold. Any error in the
 *                  resize operation will cause the program to exit early with a MEMORY_EXHAUSTED code.
 */
void
htable_insert(hashtable_t* htable, key_type key, data_type value) {
    size_t bucket_index;
    hashtable_bucket_element_t* bucket;

    if (htable == NULL) {
        fprintf(stderr, "[htable_insert] Invalid input. Faulty insert request on NULL table.\n");
        exit(INVALID_INPUT);
    }

    bucket_index = get_bucket_index(htable, key);
    bucket = htable->buckets[bucket_index];
    if (bucket == NULL) { /* add first element to the bucket if still empty */
        htable->buckets[bucket_index] = construct_bucket_element(key, value);
        goto finish;
    }

    if (htable->key_compare(bucket->pair->key, key) == 0) {
        bucket->pair->value = value;
        return;
    }

    while (bucket->next != NULL) { /* iterate until you find the empty value... */
        bucket = bucket->next;

        if (htable->key_compare(bucket->pair->key, key) == 0) { /*... or an existing pair to update */
            bucket->pair->value = value;
            return;
        }
    }

    bucket->next = construct_bucket_element(key, value); /* add the new element to the bucket */
    bucket->next->previous = bucket;

finish: /* increase count and resize if necessary */
    htable->count++;

    if (htable->count > htable->load_threshold) {
        resize_table(htable, get_prime(2 * htable->count));
    }
}

/**
 * \brief           free the memory associated with a given bucket element.
 * \param[in]       element: element to clear.
 */
static void
clear_bucket_element(hashtable_bucket_element_t* element) {
    free(element->pair);
    free(element);
}

/**
 * \brief           delete a pair with the given key from the hash table.
 * \param[in]       htable: pointer to the hash table. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       key: key of the value to delete.
 * \note            if the given key is not contained in the hash table the function will terminate without raising an error message.
 */
void
htable_delete(hashtable_t* htable, key_type key) {
    size_t bucket_index;
    hashtable_bucket_element_t* bucket;

    if (htable == NULL) {
        fprintf(stderr, "[htable_delete] Invalid input. Faulty delete request on NULL table.\n");
        exit(INVALID_INPUT);
    }

    bucket_index = get_bucket_index(htable, key);
    bucket = htable->buckets[bucket_index];
    if (bucket == NULL) { /* the key has not been found in the table */
        return;
    }

    /* if the key is contained in the first element of a bucket we can update it directly */
    if (htable->key_compare(bucket->pair->key, key) == 0) {
        htable->buckets[bucket_index] = bucket->next;
        if (bucket->next != NULL) {
            bucket->next->previous = NULL;
        }

        htable->count--;
        clear_bucket_element(bucket);
        return;
    }

    /* if it's not we need to explore the bucket to find our element */
    while (bucket != NULL && htable->key_compare(bucket->pair->key, key) != 0) {
        bucket = bucket->next;
    }

    if (bucket != NULL) { /* proceed to delete, if we actually found it */
        bucket->previous->next = bucket->next;
        if (bucket->next != NULL) {
            bucket->next->previous = bucket->previous;
        }

        htable->count--;
        clear_bucket_element(bucket);
    }
}

/**
 * \brief           search a pair with the given key in the hash table, and return the associated value.
 * \param[in]       htable: pointer to the hash table. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       key: key of the value to search.
 * \return          the value associated with the given key, or `NULL_DATA` if none is found.
 * \note            choosing to return a "pseudo-NULL" item in this case instead of exiting early with an error state is a remarkable departure from what 
 *                  I have done on other structures. However, keeping in mind the common usage of an hash table, it might be a worthy trade off for anyone using 
 *                  this library with pointers or other easily data types with an easily defined NULL value.
 */
data_type
htable_search(hashtable_t* htable, key_type key) {
    hashtable_bucket_element_t* bucket;

    if (htable == NULL) {
        fprintf(stderr, "[htable_search] Invalid input. Faulty search request on NULL table.\n");
        exit(INVALID_INPUT);
    }

    bucket = htable->buckets[get_bucket_index(htable, key)];
    while (bucket != NULL && htable->key_compare(bucket->pair->key, key) != 0) {
        bucket = bucket->next;
    }

    return bucket != NULL ? bucket->pair->value : NULL_DATA;
}

/**
 * \brief           free the given hash table.
 * \param[in]       htable: pointer to hash table pointer.
 * \note            this function will free the memory used by the hash table. The input pointer itself will be set to `NULL`.
 */
void
htable_clear(hashtable_t** htable) {
    hashtable_bucket_element_t *bucket, *to_free;

    if (htable == NULL || *htable == NULL) {
        return;
    }

    for (size_t i = 0; i < (*htable)->capacity; i++) {
        bucket = (*htable)->buckets[i];
        while (bucket != NULL) {
            to_free = bucket;
            bucket = bucket->next;
            clear_bucket_element(to_free);
        }
    }

    free_s(*htable);
}