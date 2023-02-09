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
    trie->count++;
}

/**
 * \brief           check if the given node can be deleted (not terminal and without any children) and do so if that's the cause.
 * \param[in]       node: pointer to the node.
 * \return          a value indicating whether the node has been deleted (true) or not (false).
 */
static bool
check_node_and_delete(trie_node_t* node) {
    if (node->is_terminal) { /* check if the node is terminal */
        return false;
    }

    for (size_t i = 0; i < ALPHABET_SIZE; i++) { /* or if it's part of a key */
        if (node->children[i] != NULL) {
            return false;
        }
    }

    free(node->children); /* if it's not, free it */
    free(node);
    return true;
}

/**
 * \brief           navigate to the node termination of the given key (if present) and either mark it as non-terminal (if still valuable for another key)
 *                  or delete it, together with other non valuable nodes in the key chain.
 * \param[in]       trie: pointer to the trie.
 * \param[in]       node: pointer to the node.
 * \param[in]       key: pointer to the key string.
 * \param[out]      value: value contained in the deleted node. NULL_DATA if the node was not found.
 * \return          a value indicating whether the node has been deleted (true) or not (false).
 */
static bool
trie_delete_recursive(trie_t* trie, trie_node_t* node, char* key, data_type* value) {
    int index;
    bool children_deleted;

    if (node == NULL) { /* if we reached a NULL node the key is not contained in the trie, e.g. nothing to delete */
        *value = NULL_DATA;
        return false;
    }

    if (*key == '\0') {           /* if we reached the end of the key */
        if (node->is_terminal) {  /* and the node is terminal */
            *value = node->value; /* we can extract a value */
            node->is_terminal = false;
            trie->count--;
        } else {
            *value = NULL_DATA; /* otherwise set it to NULL_DATA */
        }

        return check_node_and_delete(node);
    }

    index = alphabet_index(*key);
    if (index < 0 || index >= ALPHABET_SIZE) {
        fprintf(stderr,
                "[trie_delete] Invalid input. Faulty deletion request with key containing invalid character: '%c'.\n",
                *key);
        exit(INVALID_INPUT);
    }

    children_deleted = trie_delete_recursive(trie, node->children[index], ++key, value);

    if (children_deleted) {
        node->children[index] = NULL;
        return check_node_and_delete(node);
    }

    return false;
}

/**
 * \brief           delete the given key/value pair from the trie.
 * \param[in]       trie: pointer to the trie. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       key: pointer to the character array containing the key. `NULL` and strings containing characters not belonging to the target alphabet 
 *                  (e.g., causing alphabet_index to output invalid indexes) are not considered a valid input and will cause an early exit with INVALID_INPUT
 *                  status code. Using keys which are not NUL-terminated will result in undefined behavior.
 * \return          the value connected to the deleted key.
 * \relates         trie_t
 */
data_type
trie_delete(trie_t* trie, char* key) {
    data_type value;

    if (trie == NULL) {
        fprintf(stderr, "[trie_delete] Invalid input. Faulty deletion request on NULL trie.\n");
        exit(INVALID_INPUT);
    }

    if (key == NULL) {
        fprintf(stderr, "[trie_delete] Invalid input. Faulty deletion request with NULL key.\n");
        exit(INVALID_INPUT);
    }

    trie_delete_recursive(trie, trie->root, key, &value);
    return value;
}