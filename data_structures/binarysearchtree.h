/**
 * \file            binarysearchtree.h
 * \brief           header file containing the declaration of the binary search tree data structure and operations.
 */

#ifndef BINARYSEARCHTREE
#define BINARYSEARCHTREE

#include <stdbool.h>
#include "datatype.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief           function used to process the value of a node during a tree traversal.
 */
typedef void (*process_node_value_fn)(data_type value);

/**
 * \brief           type used to define the color of a binary search tree node.
 */
typedef enum { BLACK, RED } bstnode_color_t;

/**
 * \brief           data structure representing a single node of the binary search tree.
 */
typedef struct binary_search_tree_node_t {
    data_type value;                          /*!< node value */
    struct binary_search_tree_node_t* parent; /*!< pointer to the parent node */
    struct binary_search_tree_node_t* left;   /*!< pointer to the left child node */
    struct binary_search_tree_node_t* right;  /*!< pointer to the right child node */
    bstnode_color_t color;                    /*!< color of the node */
} binary_search_tree_node_t;

/**
 * \brief           binary search tree data structure.
 * \note            this structure is implemented as a self-balancing red/black tree.
 */
typedef struct {
    binary_search_tree_node_t* root; /*!< pointer to the tree root */
    size_t count;                    /*!< number of elements inside the tree */
    data_type_compare_fn compare;    /*!< function used to compare node values during search operations */
} binary_search_tree_t;

__declspec(dllexport) binary_search_tree_t* bstree_construct(data_type_compare_fn compare);
__declspec(dllexport) void bstree_insert(binary_search_tree_t* tree, data_type value);
__declspec(dllexport) void bstree_delete(binary_search_tree_t* tree, binary_search_tree_node_t* node);
__declspec(dllexport) binary_search_tree_node_t* bstree_search(binary_search_tree_t* tree, data_type value);
__declspec(dllexport) binary_search_tree_node_t* bstree_find_min(binary_search_tree_t* tree);
__declspec(dllexport) binary_search_tree_node_t* bstree_find_max(binary_search_tree_t* tree);
__declspec(dllexport) size_t tree_count(binary_search_tree_t* tree);
__declspec(dllexport) bool tree_is_empty(binary_search_tree_t* tree);
__declspec(dllexport) void bstree_traverse(binary_search_tree_t* tree, process_node_value_fn process);
__declspec(dllexport) void bstree_clear(binary_search_tree_t** tree);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !BINARYSEARCHTREE