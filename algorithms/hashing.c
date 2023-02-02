#include "hashing.h"

/**
 * \brief           hash the given string using Bernstein's djb2 hash function.
 * \param[in]       string: pointer to a character array.
 * \param[in]       string_length: size of the character array.
 * \return          the hashed value.
 * \note            this hashing function is based on Linear congruential generator, and follows the formula H(n) = (a*H(n - 1) + c)mod m, where:
 *                  `a` is 33. In the code belove Bernstein speed up the multiplication with a bit manipulation (hash << 5L)
 *                  `c` is the value of the hash until that point (e.g. H(n - 1)).
 *                  `m` is 32. We are working with an unsigned long (32 bits of size), an overflow will naturally result in a modulo 32 operation.
 */
unsigned long
hash_djb2(const unsigned char* string, size_t string_length) {
    unsigned long hash;

    hash = 5381;
    while (string_length--) {
        hash = ((hash << 5L) + hash) + *string++;
    }

    return hash;
}