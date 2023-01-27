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
 * \brief           perform a left rotation on the subtree starting from the given node.
 * \param[in]       tree: tree pointer.
 * \param[in]       root: current root of the subtree to rotate.
 */
static void
rotate_left(binary_search_tree_t* tree, binary_search_tree_node_t* root) {
    binary_search_tree_node_t *pivot, *new_right;

    pivot = root->right;     /* choose as pivot the right child of the original subtree root */
    new_right = pivot->left; /* get the left subtree of the pivot (all values in this subtree are > root) */

    pivot->parent = root->parent; /* update the parent of the pivot*/
    if (root->parent == NULL) {   /* we rotated the root of the tree, so we need to update it */
        tree->root = pivot;
    } else if (root == root->parent->left) { /* find which subtree we rotated and update the reference */
        root->parent->left = pivot;
    } else {
        root->parent->right = pivot;
    }

    root->parent = pivot;    /* make the pivot into the new parent of the old root */
    pivot->left = root;      /* move the root on the left side of the pivot */
    root->right = new_right; /* attach the left side of the pivot to the right side of the old root */

    if (new_right != NULL) { /* update the parent of this new right side, if necessary */
        new_right->parent = root;
    }
}

/**
 * \brief           perform a right rotation on the subtree starting from the given node.
 * \param[in]       tree: tree pointer.
 * \param[in]       root: current root of the subtree to rotate.
 */
static void
rotate_right(binary_search_tree_t* tree, binary_search_tree_node_t* root) {
    binary_search_tree_node_t *pivot, *new_left;

    pivot = root->left;      /* choose as pivot the left child of the original subtree root */
    new_left = pivot->right; /* get the right subtree of the pivot (all values in this subtree are < root) */

    pivot->parent = root->parent; /* update the parent of the pivot*/
    if (root->parent == NULL) {   /* we rotated the root of the tree, so we need to update it */
        tree->root = pivot;
    } else if (root == root->parent->left) { /* find which subtree we rotated and update the reference */
        root->parent->left = pivot;
    } else {
        root->parent->right = pivot;
    }

    root->parent = pivot;  /* make the pivot into the new parent of the old root */
    pivot->right = root;   /* move the root on the right side of the pivot */
    root->left = new_left; /* attach the right side of the pivot to the left side of the old root */

    if (new_left != NULL) { /* update the parent of this new right side, if necessary */
        new_left->parent = root;
    }
}

/**
 * \brief           create a new tree new, initializing it with the given values.
 * \param[in]       parent: parent node of the node.
 * \param[in]       value: value to be contained in the node.
 * \param[in]       color: color of the node.
 * \return          a pointer to the new tree node.
 */
static binary_search_tree_node_t*
construct_node(data_type value, bstnode_color_t color) {
    binary_search_tree_node_t* new_node;

    new_node = malloc_s(sizeof(binary_search_tree_node_t));
    new_node->value = value;
    new_node->color = color;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

/**
 * \brief           insert a new node in the tree.
 * \param[in]       tree: pointer to the tree.
 * \param[in]       node: node to insert.
 */
static void
insert_node(binary_search_tree_t* tree, binary_search_tree_node_t* node) {
    binary_search_tree_node_t* root; /* root of all the subtrees we are going to explore */

    root = tree->root;
    while (root != NULL) {
        int compare_value;

        compare_value = tree->compare(node->value, root->value);
        if (compare_value == 0) { /* terminate early if we found a duplicate */
            fprintf(stderr,
                    "[bstree_insert] Invalid operation. Faulty insert request of duplicated value " DATA_PRINT_FORMAT
                    ".\n",
                    node->value);
            exit(INVALID_OPERATION);
        }

        if (compare_value > 0) { /* if new node > root, explore the right subtree for an empty spot... */
            if (root->right == NULL) {
                root->right = node;
                node->parent = root;
                break;
            }

            root = root->right;
        } else { /* otherwise explore the left subtree */
            if (root->left == NULL) {
                root->left = node;
                node->parent = root;
                break;
            }

            root = root->left;
        }
    }
}

/**
 * \brief           swap colors of 2 existing tree nodes.
 * \param[in]       a: first node.
 * \param[in]       b: second node.
 */
static void
swap_colors(binary_search_tree_node_t* a, binary_search_tree_node_t* b) {
    bstnode_color_t temp = a->color;
    a->color = b->color;
    b->color = temp;
}

/**
 * \brief           balance an existing tree after the insertion of a new node.
 * \param[in]       tree: pointer to the tree.
 * \param[in]       node: node from which start balancing.
 */
static void
balance_tree_after_insert(binary_search_tree_t* tree, binary_search_tree_node_t* node) {
    binary_search_tree_node_t *root, *parent, *grand_parent, *uncle;

    root = tree->root;
    parent = NULL;
    grand_parent = NULL;

    while (                                /* keep iterating while... */
           (node != root)                  /* we didn't reach the root... */
           && (node->color != BLACK)       /* ...the node need recoloring... */
           && (node->parent->color == RED) /* ...because its parent has its same color (red-red conflict) */
    ) {
        parent = node->parent;
        if (parent == NULL) {
            fprintf(
                stderr,
                "[balance_tree_after_insert] Internal error. The balancing operation resulted in a malformed tree.");
            exit(INTERNAL_ERROR);
        }

        grand_parent = parent->parent;
        if (grand_parent == NULL) {
            fprintf(
                stderr,
                "[balance_tree_after_insert] Internal error. The balancing operation resulted in a malformed tree.");
            exit(INTERNAL_ERROR);
        }

        /* get the uncle as the child of grandparent opposite to parent */
        uncle = parent == grand_parent->left ? grand_parent->right : grand_parent->left;
        if (uncle != NULL && uncle->color == RED) { /* uncle and parent are both red, we can recolor and continue */
            grand_parent->color = RED;
            parent->color = BLACK;
            uncle->color = BLACK;
            node = grand_parent; /* move the focus to the grand_parent and keep iterating */
            continue;
        }

        /* parent is red and uncle is black (NULL leafs are considered black), we need to rotate*/
        if (parent == grand_parent->left) {
            if (node == parent->right) { /* "rectify" the edge if we are in a complex state */
                /*
                    *           gp                  gp
                    *          /  \                /   \
                    *         p    u      =>      n     u
                    *          \                 /
                    *           n               p
                    */
                rotate_left(tree, parent);

                /* swap node and parent variables to adapt to the new configuration */
                node = parent;
                parent = node->parent;
            }

            /* fix the balance by performing a right rotation on the grandparent, update colors 
                * 
                *          gp                 p
                *         /   \             /   \
                *        p     u     =>    n     gp
                *       /                          \
                *      n                            u
                */
            rotate_right(tree, grand_parent);
            swap_colors(parent, grand_parent);
            node = parent;
        } else {
            if (node == parent->left) { /* "rectify" the edge if we are in a complex state */
                /* 
                *          gp                gp
                *         /   \             /   \
                *        u     p     =>    u     n
                *             /                    \
                *            n                      p
                */
                rotate_right(tree, parent);

                /* swap node and parent variables to adapt to the new configuration */
                node = parent;
                parent = node->parent;
            }

            /* fix the balance by performing a right rotation on the grandparent, update colors 
            * 
            *          gp                 p
            *         /   \             /   \
            *        u     p     =>    gp    n
            *               \         /         
            *                n       u         
            */
            rotate_left(tree, grand_parent);
            swap_colors(parent, grand_parent);
            node = parent;
        }
    }

    if (tree->root == NULL) {
        fprintf(stderr, "[balance_tree] Internal error. The balancing operation resulted in a empty tree.");
        exit(INTERNAL_ERROR);
    }

    tree->root->color = BLACK;
}

/**
 * \brief           insert a new value in the tree.
 * \param[in]       tree: tree pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       value: value to insert. Trying to insert a duplicate value in the tree is considered an invalid operation, and will result in the program exiting early
 *                  with INVALID_OPERATION status code.
 */
void
bstree_insert(binary_search_tree_t* tree, data_type value) {
    if (tree == NULL) {
        fprintf(stderr, "[bstree_insert] Invalid input. Faulty insert request on NULL tree.\n");
        exit(INVALID_INPUT);
    }

    if (tree->root == NULL) { /* if the tree is empty, initialize a new root node... */
        tree->root = construct_node(value, BLACK);
    } else { /* ...otherwise insert the value and re-balance the tree (if needed) */
        binary_search_tree_node_t* new_node;

        new_node = construct_node(value, RED);
        insert_node(tree, new_node);
        balance_tree_after_insert(tree, new_node);
    }

    tree->count++;
}

static void
rb_transplant(binary_search_tree_t* t, binary_search_tree_node_t* u, binary_search_tree_node_t* v) {
    if (u->parent == NULL) {
        t->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }

    if (v != NULL) {
        v->parent = u->parent;
    }
}

static binary_search_tree_node_t*
find_subtree_min(binary_search_tree_node_t* x) {
    while (x->left != NULL) {
        x = x->left;
    }
    return x;
}

/**
 * \brief           balance an existing tree after the deletion of a node.
 * \param[in]       tree: pointer to the tree.
 * \param[in]       node: node that replaced the deleted value, from which we should start balancing.
 * \param[in]       leaf_parent: parent of the node. We are forced to pass this parameter as we are not using a special struct to handle empty leafs and we might need to handle
 *                  `NULL` node values.
 */
static void
balance_tree_after_delete(binary_search_tree_t* t, binary_search_tree_node_t* x,
                          binary_search_tree_node_t* leaf_parent) {
    binary_search_tree_node_t *parent, *w;

    while (x != t->root && (x == NULL || x->color == BLACK)) {
        parent = x != NULL ? x->parent : leaf_parent;
        if (parent == NULL) {
            fprintf(
                stderr,
                "[balance_tree_after_delete] Internal error. The balancing operation resulted in a malformed tree.");
            exit(INTERNAL_ERROR);
        }

        if (x == parent->left) {
            w = parent->right;
            if (w == NULL) {
                fprintf(stderr, "[balance_tree_after_delete] Internal error. The balancing operation resulted in a "
                                "malformed tree.");
                exit(INTERNAL_ERROR);
            }

            if (w->color == RED) {
                w->color = BLACK;
                parent->color = RED;
                rotate_left(t, parent);
                w = parent->right;
            }

            if ((w->left == NULL || w->left->color == BLACK) && (w->right == NULL || w->right->color == BLACK)) {
                w->color = RED;
                x = parent;
            } else {
                if (w->right == NULL || w->right->color == BLACK) {
                    if (w->left != NULL) {
                        w->left->color = BLACK;
                    }

                    w->color = RED;
                    rotate_right(t, w);
                    w = parent->right;
                }
                w->color = parent->color;
                parent->color = BLACK;

                if (w->right != NULL) {
                    w->right->color = BLACK;
                }

                rotate_left(t, parent);
                x = t->root;
            }
        } else {
            w = parent->left;
            if (w == NULL) {
                fprintf(stderr, "[balance_tree_after_delete] Internal error. The balancing operation resulted in a "
                                "malformed tree.");
                exit(INTERNAL_ERROR);
            }

            if (w->color == RED) {
                w->color = BLACK;
                parent->color = RED;
                rotate_right(t, parent);
                w = parent->left;
            }
            if ((w->left == NULL || w->left->color == BLACK) && (w->right == NULL || w->right->color == BLACK)) {
                w->color = RED;
                x = parent;
            } else {
                if (w->left == NULL || w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotate_left(t, w);
                    w = parent->left;
                }
                w->color = parent->color;
                parent->color = BLACK;

                if (w->left != NULL) {
                    w->left->color = BLACK;
                }

                rotate_right(t, parent);
                x = t->root;
            }
        }
    }

    if (x != NULL) {
        x->color = BLACK;
    }
}

/**
 * \brief           delete the given node from the tree.
 * \param[in]       tree: tree pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       node: node to delete. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 */
void
bstree_delete(binary_search_tree_t* tree, binary_search_tree_node_t* node) {
    if (tree == NULL) {
        fprintf(stderr, "[bstree_delete] Invalid input. Faulty delete request on NULL tree.\n");
        exit(INVALID_INPUT);
    }

    if (node == NULL) {
        fprintf(stderr, "[bstree_delete] Invalid input. Faulty delete request of NULL node.\n");
        exit(INVALID_INPUT);
    }

    if (node == tree->root && node->left == NULL && node->right == NULL) {
        free_s(tree->root);
        return;
    }

    binary_search_tree_node_t* y = node;
    binary_search_tree_node_t* x;

    bstnode_color_t y_original_color = y->color;
    if (node->left == NULL) {
        x = node->right;
        rb_transplant(tree, node, node->right);
    } else if (node->right == NULL) {
        x = node->left;
        rb_transplant(tree, node, node->left);
    } else {
        y = find_subtree_min(node->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == node) {
            if (x != NULL) {
                x->parent = node;
            }
        } else {
            rb_transplant(tree, y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        rb_transplant(tree, node, y);
        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;
    }

    if (y_original_color == BLACK) {
        balance_tree_after_delete(tree, x, node->parent);
    }

    free_s(node);
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
    if (compare_value > 0) {
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
bstree_count(binary_search_tree_t* tree) {
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
bstree_is_empty(binary_search_tree_t* tree) {
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