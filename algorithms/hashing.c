#include "hashing.h"

/**
 * \brief           hash the given string using Daniel Julius Bernstein's hash function.
 * \param[in]       string: pointer to a NUL terminated character array.
 * \return          the hashed value.
 * \note            this hashing function is based on Linear congruential generator, and follows the formula H(n) = (a*H(n - 1) + c)mod m, where:
 *                  `a` is 33. In the code belove Bernstein speed up the multiplication with bit manipulation: (hash << 5L) + hash.
 *                  `c` is the value of character in position n inside the string.
 *                  `m` is 32. We are working with an unsigned long (32 bits of size), an overflow will naturally result in a modulo 32 operation.
 */
uint32_t
hash_djb2(const unsigned char* string) {
    uint32_t hash;

    hash = 5381; /* B. has chosen this number as testing showed results of fewer collisions and better avalanching. */
    while (*string != '\0') {
        hash = ((hash << 5) + hash) + *string;
        string++;
    }

    return hash;
}

/**
 * \brief           hash the given string using the Fowler–Noll–Vo 1a hash function.
 * \param[in]       string: pointer to a NUL terminated character array.
 * \param[in]       string_length: size of the character array.
 * \return          the hashed value.
 */
uint64_t
hash_fnv(const unsigned char* string) {
    uint64_t hash;

    hash = 14695981039346656037UL; /* set hash to the 64 bits value of the FNV offset */
    while (*string != '\0') {
        hash ^= (uint64_t)*string;
        hash *= 1099511628211UL; /* multiply by the 64 bits value of the FNV prime */
        string++;
    }

    return hash;
}