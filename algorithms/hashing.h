/**
 * \file            HASHING.h
 * \brief           header file containing the declaration of hashing algorithms implemented in this library.
 */

#ifndef HASHING
#define HASHING

#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

__declspec(dllexport) uint32_t hash_djb2(const unsigned char* string);
__declspec(dllexport) uint64_t hash_fnv(const unsigned char* string);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !HASHTABLE