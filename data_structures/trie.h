/**
 * \file            trie.h
 * \brief           header file containing the declaration of the trie data structure and operations.
 */

#ifndef TRIE
#define TRIE

#include <stdlib.h>
#include <stdbool.h>
#include "datatype.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief           size of the alphabet to represent.
 * \hideinitializer
 */
#define ALPHABET_SIZE             26

/**
 * \brief           get the index of the character inside the chosen alphabet.
 * \param[in]       character: a character of the alphabet
 * \return          a numeric value between 0 and ALPHABET_SIZE
 * \hideinitializer
 */
#define alphabet_index(character) (character - 'a')

/**
 * \brief           data structure representing a single node of the trie.
 */
typedef struct trie_node_t {
    struct trie_node_t** children; /*!< pointer to the parent node */
    bool is_terminal; /*!< flag describing if this node is terminal for a certain key, and therefore contains a value */
    data_type value;  /*!< node value */
} trie_node_t;

/**
 * \brief           data structure representing the trie.
 * \note            this implementation of a prefix tree allows the insertion of a key/value pair. 
 *                  Internal connections between nodes are handled by arrays of size "ALPHABET_SIZE". This of course is costly in terms of memory used, 
 *                  but allows fast search operations without having to reorder the children of individual nodes at each insertion.
 */
typedef struct {
    trie_node_t** root; /*!< pointer to the root node */
    size_t count;       /*!< number of values contained in the tree */
} trie_t;

__declspec(dllexport) trie_t* trie_construct(void);
__declspec(dllexport) void trie_insert(trie_t* trie, char* key, data_type value);
__declspec(dllexport) void trie_delete(trie_t* trie, char* key);
__declspec(dllexport) data_type trie_search(trie_t* trie, char* key);
__declspec(dllexport) void trie_clear(trie_t** trie);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !TRIE