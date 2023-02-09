#include "memalloc.h"
#include "trie.h"

/**
 * \brief           construct a new trie.
 * \return          a pointer the newly constructed trie.
 * \relates         trie_t
 */
trie_t*
trie_construct(void) {
    trie_t* new_trie;

    new_trie = malloc_s(sizeof(trie_t));
    new_trie->root = calloc_s(ALPHABET_SIZE, sizeof(trie_node_t));
    new_trie->count = 0;

    return new_trie;
}
