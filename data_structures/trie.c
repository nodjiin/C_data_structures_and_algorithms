#include <stdio.h>
#include "memalloc.h"
#include "trie.h"
#include "exitcodes.h"

/**
 * \brief           create a new trie node.
 * \return          a pointer the newly constructed trie node.
 */
static trie_node_t*
create_node(void) {
    trie_node_t* new_node;

    new_node = malloc_s(sizeof(trie_node_t));
    new_node->children = calloc_s(ALPHABET_SIZE, sizeof(trie_node_t));
    new_node->is_terminal = false;

    return new_node;
}

/**
 * \brief           construct a new trie.
 * \return          a pointer the newly constructed trie.
 * \relates         trie_t
 */
trie_t*
trie_construct(void) {
    trie_t* new_trie;

    new_trie = malloc_s(sizeof(trie_t));
    new_trie->root = create_node();
    new_trie->count = 0;

    return new_trie;
}

/**
 * \brief           insert the given key/value pair inside the trie.
 * \param[in]       trie: pointer to the trie. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       key: pointer to the character array containing the key. `NULL` and strings containing characters not belonging to the target alphabet 
 *                  (e.g., causing alphabet_index to output invalid indexes) are not considered a valid input and will cause an early exit with INVALID_INPUT
 *                  status code. Using keys which are not NUL-terminated will result in undefined behavior.
 * \param[in]       value: value to store in a terminal node.
 * \relates         trie_t
 */
void
trie_insert(trie_t* trie, char* key, data_type value) {
    trie_node_t* node;

    if (trie == NULL) {
        fprintf(stderr, "[trie_insert] Invalid input. Faulty insertion request on NULL trie.\n");
        exit(INVALID_INPUT);
    }

    if (key == NULL) {
        fprintf(stderr, "[trie_insert] Invalid input. Faulty insertion request with NULL key.\n");
        exit(INVALID_INPUT);
    }

    node = trie->root;
    while (*key != '\0') {
        int index;

        index = alphabet_index(*key);
        if (index < 0 || index >= ALPHABET_SIZE) {
            fprintf(
                stderr,
                "[trie_insert] Invalid input. Faulty insertion request with key containing invalid character: '%c'.\n",
                *key);
            exit(INVALID_INPUT);
        }

        if (node->children[index] == NULL) {
            node->children[index] = create_node();
        }

        node = node->children[index];
        key++;
    }

    node->value = value;
    node->is_terminal = true;
}