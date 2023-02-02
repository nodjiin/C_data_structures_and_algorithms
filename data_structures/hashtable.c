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
htable_construct(size_t initial_capacity, uint8_t load_factor, hash_key_fn hash) {
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

    real_size = get_prime(initial_capacity);
    new_hashtable = malloc_s(sizeof(hashtable_t));
    new_hashtable->buckets = calloc_s(real_size, sizeof(hashtable_bucket_element_t));
    new_hashtable->count = 0;
    new_hashtable->capacity = real_size;
    new_hashtable->load_factor = load_factor;
    new_hashtable->hash = hash;

    return new_hashtable;
}