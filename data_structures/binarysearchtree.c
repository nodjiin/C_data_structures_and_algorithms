/**
 * \file            binarysearchtree.c
 * \brief           source file containing the definition of binary search tree operations.
 */

#include <stdio.h>
#include <stdlib.h>
#include "binarysearchtree.h"
#include "memalloc.h"
#include "exitcodes.h"

/**
 * \brief           construct a new binary search tree.
 * \param[in]       compare: comparison function used to evaluate the value of each item in the tree. An output > 0 will be considered as a sign that the first value
 *                  passed to the function is greater than the second value, conversely with a value < 0 the first value will be considered smaller. 
 *                  If the output is 0 the 2 values will be considered of equals. `NULL` is not considered a valid input and will cause the program to exit early 
 *                  with an INVALID_INPUT status code.
 * \return          a pointer the newly constructed heap.
 */
binary_search_tree_t*
bstree_construct(data_type_compare_fn compare) {
    binary_search_tree_t* new_tree;

    if (compare == NULL) {
        fprintf(stderr, "[bstree_construct] Invalid input. Faulty construct request with NULL compare function.\n");
        exit(INVALID_INPUT);
    }

    new_tree = malloc_s(sizeof(binary_search_tree_t));
    new_tree->compare = compare;
    new_tree->count = 0;
    new_tree->root = NULL;

    return new_tree;
}

/**
 * \brief           recursively search a value in all the nodes of the subtree having the given node as root.
 * \param[in]       node: root node of the subtree to search into.
 * \param[in]       compare: compare function pointer.
 * \return          a pointer to the tree node holding the given value, or `NULL` if none is found.
 */
static binary_search_tree_node_t*
search_tree(binary_search_tree_node_t* node, data_type value, data_type_compare_fn compare) {
    int compare_value;

    if (node == NULL) {
        return NULL;
    }

    compare_value = compare(node->value, value);
    if (compare_value == 0) {
        return node;
    }
    if (compare_value < 0) {
        return (search_tree(node->left, value, compare));
    } else {
        return (search_tree(node->right, value, compare));
    }
}

/**
 * \brief           search the tree looking an existing node holding the given value.
 * \param[in]       tree: tree pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       value: value to search for.
 * \return          a pointer to the tree node holding the given value, or `NULL` if none is found.
 */
binary_search_tree_node_t*
bstree_search(binary_search_tree_t* tree, data_type value) {

    if (tree == NULL) {
        fprintf(stderr, "[bstree_search] Invalid input. Faulty search request on NULL tree.\n");
        exit(INVALID_INPUT);
    }

    /* we are allowing search operation to be executed on an empty tree, as the user will have to check for `NULL` return anyway. You could also handle it as an error */
    /* to keep the consistency with bstree_find_min & bstree_find_max */
    return search_tree(tree->root, value, tree->compare);
}

/**
 * \brief           find the node holding the minimum value inside the tree.
 * \param[in]       tree: tree pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \return          a pointer to the tree node holding the minimum value.
 * \note            using this function on an empty tree is considered an invalid operation, and will cause an early exit with INVALID_OPERATION status code.
 */
binary_search_tree_node_t*
bstree_find_min(binary_search_tree_t* tree) {
    binary_search_tree_node_t* min;

    if (tree == NULL) {
        fprintf(stderr, "[bstree_find_min] Invalid input. Faulty find min request with NULL tree.\n");
        exit(INVALID_INPUT);
    }

    if (tree->root == NULL) {
        fprintf(stderr, "[bstree_find_min] Invalid operation. Faulty find min request on empty tree");
        exit(INVALID_OPERATION);
    }

    min = tree->root;
    while (min->left != NULL) {
        min = min->left;
    }
    return min;
}

/**
 * \brief           find the node holding the maximum value inside the tree.
 * \param[in]       tree: tree pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \return          a pointer to the tree node holding the maximum value.
 * \note            using this function on an empty tree is considered an invalid operation, and will cause an early exit with INVALID_OPERATION status code.
 */
binary_search_tree_node_t*
bstree_find_max(binary_search_tree_t* tree) {
    binary_search_tree_node_t* max;

    if (tree == NULL) {
        fprintf(stderr, "[bstree_find_max] Invalid input. Faulty find max request with NULL tree.\n");
        exit(INVALID_INPUT);
    }

    if (tree->root == NULL) {
        fprintf(stderr, "[bstree_find_max] Invalid operation. Faulty find max request on empty tree");
        exit(INVALID_OPERATION);
    }

    max = tree->root;
    while (max->right != NULL) {
        max = max->right;
    }
    return max;
}

/**
 * \brief           recursively process all the nodes in the subtree having the given node as root.
 * \param[in]       node: root node of the subtree to process.
 * \param[in]       process: process function pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 */
static void
traverse_tree(binary_search_tree_node_t* node, process_node_value_fn process) {
    if (node == NULL) { /* we reached an empty leaf, so we can terminate the recursion */
        return;
    }

    traverse_tree(node->left, process);
    process(node->value);
    traverse_tree(node->right, process);
}

/**
 * \brief           perform an in-order traversal of the tree, processing all the visited node using the given function.
 * \param[in]       tree: tree pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       process: process function pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 */
void
bstree_traverse(binary_search_tree_t* tree, process_node_value_fn process) {
    if (tree == NULL) {
        fprintf(stderr, "[bstree_traverse] Invalid input. Faulty traverse request with NULL tree.\n");
        exit(INVALID_INPUT);
    }

    if (process == NULL) {
        fprintf(stderr, "[bstree_traverse] Invalid input. Faulty traverse request with NULL process function.\n");
        exit(INVALID_INPUT);
    }

    traverse_tree(tree->root, process);
}

/**
 * \brief           check how many nodes are contained in the tree.
 * \param[in]       heap: tree pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \return          the number of nodes currently in the tree.
 */
size_t
tree_count(binary_search_tree_t* tree) {
    if (tree == NULL) {
        fprintf(stderr, "[tree_count] Invalid input. Faulty count request on NULL tree.\n");
        exit(INVALID_INPUT);
    }

    return tree->count;
}

/**
 * \brief           check if the tree is empty.
 * \param[in]       stack: tree pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \return          true if the tree is empty, false otherwise.
 */
bool
tree_is_empty(binary_search_tree_t* tree) {
    if (tree == NULL) {
        fprintf(stderr, "[tree_is_empty] Invalid input. Faulty empty check request on NULL tree.\n");
        exit(INVALID_INPUT);
    }

    return tree->count == 0;
}

/**
 * \brief           recursively free all the nodes in the subtree having the given node as root.
 * \param[in]       node: root node of the subtree to free.
 */
static void
free_tree_nodes(binary_search_tree_node_t* node) {
    if (node == NULL) { /* we reached an empty leaf, so we can terminate the recursion */
        return;
    }

    free_tree_nodes(node->left);
    free_tree_nodes(node->right);
    free(node);
}

/**
 * \brief           free the given tree.
 * \param[in]       tree: pointer to tree pointer.
 * \note            this function will free the memory used by the tree. The input pointer itself will be set to `NULL`.
 */
void
bstree_clear(binary_search_tree_t** tree) {
    if (tree == NULL || *tree == NULL) {
        return;
    }

    if ((*tree)->root != NULL) {
        free_tree_nodes((*tree)->root);
    }

    free_s(*tree);
}