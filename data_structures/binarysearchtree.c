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
 * \relates         binary_search_tree_t
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
            /*
            *           gp(B)               gp(R)
            *          /  \                /   \
            *         p(R) u(R)   =>      p(B)  u(B)
            *        /                   /
            *       n(R)                n(R)           
            * 
            *  the position of grandfather, uncle and father do not matter in this configuration, since we do not have to perform any rotations.
            */
            grand_parent->color = RED;
            parent->color = BLACK;
            uncle->color = BLACK;

            node = grand_parent; /* move the focus to grand_parent... */
            continue;            /*... and keep iterating */
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
            *          gp(B)              p(B)
            *         /   \             /   \
            *        p(R)  u(B)  =>    n(R)  gp(R)
            *       /                          \
            *      n(R)                         u(B)
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
            *          gp(B)              p(B)
            *         /   \             /   \
            *        u(B)  p(R)  =>    gp(R) n(R)
            *               \         /         
            *                n(R)    u(B)      
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
 * \relates         binary_search_tree_t
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

/**
 * \brief           replace an existing node in the tree.
 * \param[in]       tree: tree pointer. 
 * \param[in]       node_to_be_replaced: node which will be replaced. 
 * \param[in]       replacement: node that will replace the existing node. It can be NULL.
 */
static void
replace_node(binary_search_tree_t* tree, binary_search_tree_node_t* node_to_be_replaced,
             binary_search_tree_node_t* replacement) {
    if (node_to_be_replaced->parent == NULL) {
        tree->root = replacement;
    } else if (node_to_be_replaced == node_to_be_replaced->parent->left) {
        node_to_be_replaced->parent->left = replacement;
    } else {
        node_to_be_replaced->parent->right = replacement;
    }

    if (replacement != NULL) {
        replacement->parent = node_to_be_replaced->parent;
    }
}

/**
 * \brief           find the node containing the minimum value in the given subtree.
 * \param[in]       node: root node of the subtree. 
 * \return          the minimum subtree node.
 */
static binary_search_tree_node_t*
find_subtree_min(binary_search_tree_node_t* node) {
    if (node == NULL) {
        return NULL;
    }

    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

/**
 * \brief           balance an existing tree after the deletion of a node.
 * \param[in]       tree: pointer to the tree.
 * \param[in]       node: node that replaced the deleted value, from which we should start balancing.
 * \param[in]       leaf_parent: parent of the node. We are forced to pass this parameter as we are not using a special struct to handle empty leafs and we might need to handle
 *                  `NULL` node values.
 * \note            this function is a bit verbose, and it could be shortened by a couple of generic purposes utility functions BUT I'm going to leave it this way, 
 *                  to make it easier for anyone looking to understand the balancing process of a red-black tree delete operation.
 */
static void
balance_tree_after_delete(binary_search_tree_t* tree, binary_search_tree_node_t* node,
                          binary_search_tree_node_t* leaf_parent) {
    binary_search_tree_node_t *parent, *sibling;

    while (node != tree->root && (node == NULL || node->color == BLACK)) {
        parent = node != NULL ? node->parent : leaf_parent;
        if (parent == NULL) {
            fprintf(
                stderr,
                "[balance_tree_after_delete] Internal error. The balancing operation resulted in a malformed tree.");
            exit(INTERNAL_ERROR);
        }

        if (node == parent->left) { /* node on the left, sibling on the right */
            sibling = parent->right;
            if (sibling == NULL) {
                fprintf(stderr, "[balance_tree_after_delete] Internal error. The balancing operation resulted in a "
                                "malformed tree.");
                exit(INTERNAL_ERROR);
            }

            /* if the sibling is red, we recolor it and the node, and then left rotate the parent */
            if (sibling->color == RED) {
                /*
                *           p(B)                s(B)
                *         /   \		           /   \
                *        n(B)  s(R)    =>      p(R)  c2(B)
                *             /    \         /   \
                *            c1(B) c2(B)    n(B)  c1(B) <-the new sibling of n is c1, and we moved s up a level
                */
                sibling->color = BLACK;
                parent->color = RED;
                rotate_left(tree, parent);
                sibling = parent->right; /* update sibling after the rotation*/
            }

            /* if both sibling children are black, we can recolor it to keep black height consistent and move the analysis to parent */
            if ((sibling->left == NULL || sibling->left->color == BLACK)
                && (sibling->right == NULL || sibling->right->color == BLACK)) {
                /*
                *           p                       p <- switch focus on the parent   
                *         /   \	                  /   \
                *        n(B)  s(B)    =>      n(B)   s(R)
                *             /    \                 /   \
                *            c1(B) c2(B)            c1(B)  c2(B)
                */
                sibling->color = RED;
                node = parent;
                continue; /* go to next iteration */
            }

            /* the right children is black, the left is red. we can get rid of this scenario by transforming it */
            if (sibling->right == NULL || sibling->right->color == BLACK) {
                /*
                *           p                      p   
                *         /   \	                 /    \
                *        n(B)  s(B)    =>      n(B)   c1(B)  <= note that c1 was red, so we are sure that its left children will be black
                *             /    \                   /  \
                *            c1(R) c2(B)             x(B) s(R)
                */
                if (sibling->left != NULL) {
                    sibling->left->color = BLACK;
                }

                sibling->color = RED;
                rotate_right(tree, sibling);
                sibling = parent->right;
            }

            /* with the previous condition we are sure that the right children is red, and the left children is black. 
            *  in this scenario all the possible violations have already been solved, we just need to fix the original black height problem.
            *  luckily we can do so simply by recoloring and rotating.
            * 
            *           p(x)                 s(x) <- preserve parent color after the rotation
            *         /   \	                /    \
            *        n(B)  s(B)    =>      p(B)   c2(B) 
            *             /    \          /  \       
            *            c1(B) c2(R)    n(B)  c1(B) 
            */
            sibling->color = parent->color;
            parent->color = BLACK;

            if (sibling->right != NULL) {
                sibling->right->color = BLACK;
            }

            rotate_left(tree, parent);
        } else { /* node on the right, sibling on the left */
            sibling = parent->left;
            if (sibling == NULL) {
                fprintf(stderr, "[balance_tree_after_delete] Internal error. The balancing operation resulted in a "
                                "malformed tree.");
                exit(INTERNAL_ERROR);
            }

            /* if the sibling is red, we recolor it and the node, and then right rotate the parent*/
            if (sibling->color == RED) {
                /*
                *           p(B)                s(B)
                *         /   \		           /   \
                *        s(R)  n(B)    =>    c1(B) p(R)  
                *      /   \                       /  \
                *     c1(B) c2(B)               c2(B) n(B) <-the new sibling of n is c2, and we moved s up a level
                */
                sibling->color = BLACK;
                parent->color = RED;
                rotate_right(tree, parent);
                sibling = parent->left; /* update sibling after the rotation*/
            }

            /* if both sibling children are black, we can recolor it to keep black height consistent and move the analysis to parent */
            if ((sibling->left == NULL || sibling->left->color == BLACK)
                && (sibling->right == NULL || sibling->right->color == BLACK)) {
                /*
                *           p                       p <- switch focus on the parent   
                *         /   \	                  /   \
                *        s(B)  n(B)    =>      s(R)   n(B)
                *       /    \                 /   \
                *     c1(B) c2(B)           c1(B)  c2(B)
                */
                sibling->color = RED;
                node = parent;
                continue; /* go to next iteration */
            }

            /* the left children is black, the right is red. we can get rid of this scenario by transforming it */
            if (sibling->left == NULL || sibling->left->color == BLACK) {
                /*
                *           p                       p   
                *         /   \	                  /   \
                *        s(B)  n(B)    =>      c2(R)   n(B) 
                *       /    \                 /  \ 
                *     c1(B) c2(R)           s(B)  x(B) <= note that c2 was red, so we are sure that its right children will be black
                */
                if (sibling->right != NULL) {
                    sibling->right->color = BLACK;
                }

                sibling->color = RED;
                rotate_left(tree, sibling);
                sibling = parent->left;
            }

            /* with the previous condition we are sure that the left children is red, and the right children is black. 
            *  in this scenario all the possible violations have already been solved, we just need to fix the original black height problem.
            *  luckily we can do so simply by recoloring and rotating.
            * 
            *           p(x)                   s(x) <- preserve parent color after the rotation
            *         /   \	                  /   \
            *        s(B)  n(B)    =>      c1(b)   p(B) 
            *       /    \                        /   \
            *     c1(B) c2(R)                   c2(B)  n(B)
            */
            sibling->color = parent->color;
            parent->color = BLACK;

            if (sibling->left != NULL) {
                sibling->left->color = BLACK;
            }

            rotate_right(tree, parent);
        }

        node = tree->root; /* move reference to root and end the cycle */
    }

    if (node != NULL) {
        node->color = BLACK;
    }
}

/**
 * \brief           delete the given node from the tree.
 * \param[in]       tree: tree pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       node: node to delete. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \relates         binary_search_tree_t
 */
void
bstree_delete(binary_search_tree_t* tree, binary_search_tree_node_t* node) {
    binary_search_tree_node_t* replacement;
    bstnode_color_t node_color;

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

    node_color = node->color;

    if (node->left == NULL) { /* the node has got 1 child on its right side, we can use it as replacement... */
        replacement = node->right;
        replace_node(tree, node, replacement);
    } else if (node->right == NULL) { /* ...and vice-versa on the left side */
        replacement = node->left;
        replace_node(tree, node, replacement);
    } else { /* if the node has got 2 child, we look for the minimum value of it's right subtree */
        binary_search_tree_node_t* min;

        min = find_subtree_min(node->right);
        node_color = min->color;
        replacement = min->right; /* replacement in this case will replace min, and not node */

        if (min->parent != node) { /* if min is not a direct child of the node, we need to replace it first */
            replace_node(tree, min, replacement);
            min->right = node->right;
            min->right->parent = min;
        }

        replace_node(tree, node, min); /* and then we use min to replace the node itself */
        min->left = node->left;
        min->left->parent = min;
        min->color = node->color;
    }

    if (node_color == BLACK) {
        balance_tree_after_delete(tree, replacement, node->parent);
    }

    free_s(node);
    tree->count--;
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
 * \relates         binary_search_tree_t
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
 * \relates         binary_search_tree_t
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
 * \relates         binary_search_tree_t
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
 * \relates         binary_search_tree_t
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
 * \relates         binary_search_tree_t
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
 * \relates         binary_search_tree_t
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
 * \relates         binary_search_tree_t
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