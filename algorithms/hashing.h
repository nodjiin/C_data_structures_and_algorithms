/**
 * \file            HASHING.h
 * \brief           header file containing the declaration of hashing algorithms implemented in this library.
 */

#ifndef HASHING
#define HASHING

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

__declspec(dllexport) unsigned long hash_djb2(const unsigned char* string, size_t string_length);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !HASHTABLE