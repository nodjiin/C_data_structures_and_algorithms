/* 
* if you are having issues visualizing the red black tree structure during insertion/deletions try out this tool:
* https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
*/

#include <assert.h>
#include "binarysearchtree_test.h"
#include "data_structures/binarysearchtree.h"
#include "testvalues.h"

void
bstree_construct_test(void) {
    binary_search_tree_t* tree;

    tree = bstree_construct(compare);

    assert(tree != NULL);
    assert(tree->root == NULL);
    assert(tree->compare == compare);
    assert(tree->count == 0);
}

void
bstree_insert_test(void) {
    binary_search_tree_t* tree;

    tree = bstree_construct(compare);

    /* insert 1,4,6,3,5,7,8,2,9 */
    bstree_insert(tree, TESTVAL1);
    bstree_insert(tree, TESTVAL4);
    bstree_insert(tree, TESTVAL6);
    bstree_insert(tree, TESTVAL3);
    bstree_insert(tree, TESTVAL5);
    bstree_insert(tree, TESTVAL7);
    bstree_insert(tree, TESTVAL8);
    bstree_insert(tree, TESTVAL2);
    bstree_insert(tree, TESTVAL9);

    /*
    *	we expect a tree with the following structure:
    *	
    *	                     4
    *                      /    \
    *                    2       6
    *                  /   \    /  \
    *                 1     3  5    8
    *                             /   \
    *                            7     9
    */
    assert(tree->count == 9);
    assert(tree->root->value == TESTVAL4); /* root */
    assert(tree->root->color == BLACK);
    assert(tree->root->left->value == TESTVAL2); /* left subtree */
    assert(tree->root->left->color == BLACK);
    assert(tree->root->left->left->value == TESTVAL1);
    assert(tree->root->left->left->color == RED);
    assert(tree->root->left->right->value == TESTVAL3);
    assert(tree->root->left->right->color == RED);
    assert(tree->root->right->value == TESTVAL6); /* right subtree */
    assert(tree->root->right->color == RED);
    assert(tree->root->right->left->value == TESTVAL5);
    assert(tree->root->right->left->color == BLACK);
    assert(tree->root->right->right->value == TESTVAL8); /* right-right subtree */
    assert(tree->root->right->right->color == BLACK);
    assert(tree->root->right->right->left->value == TESTVAL7);
    assert(tree->root->right->right->left->color == RED);
    assert(tree->root->right->right->right->value == TESTVAL9);
    assert(tree->root->right->right->right->color == RED);
}

void
bstree_delete_test(void) {
    binary_search_tree_t* tree;
    binary_search_tree_node_t* to_delete;
    tree = bstree_construct(compare);

    /* insert 1,4,6,3,5,7,8,2,9 */
    bstree_insert(tree, TESTVAL1);
    bstree_insert(tree, TESTVAL4);
    bstree_insert(tree, TESTVAL6);
    bstree_insert(tree, TESTVAL3);
    bstree_insert(tree, TESTVAL5);
    bstree_insert(tree, TESTVAL7);
    bstree_insert(tree, TESTVAL8);
    bstree_insert(tree, TESTVAL2);
    bstree_insert(tree, TESTVAL9);

    to_delete = bstree_search(tree, TESTVAL8);
    bstree_delete(tree, to_delete);
    to_delete = bstree_search(tree, TESTVAL6);
    bstree_delete(tree, to_delete);

    /*
    *	we expect a tree with the following structure:
    *	
    *	                     4
    *                      /    \
    *                    2       7
    *                  /   \    /  \
    *                 1     3  5    9
    */
    assert(tree->count == 7);
    assert(tree->root->value == TESTVAL4); /* root */
    assert(tree->root->color == BLACK);
    assert(tree->root->left->value == TESTVAL2); /* left subtree */
    assert(tree->root->left->color == BLACK);
    assert(tree->root->left->left->value == TESTVAL1);
    assert(tree->root->left->left->color == RED);
    assert(tree->root->left->right->value == TESTVAL3);
    assert(tree->root->left->right->color == RED);
    assert(tree->root->right->value == TESTVAL7); /* right subtree */
    assert(tree->root->right->color == RED);
    assert(tree->root->right->left->value == TESTVAL5);
    assert(tree->root->right->left->color == BLACK);
    assert(tree->root->right->right->value == TESTVAL9);
    assert(tree->root->right->right->color == BLACK);
}

void
bstree_delete_test_2(void) {
    binary_search_tree_t* tree;
    binary_search_tree_node_t* to_delete;
    tree = bstree_construct(compare);

    /* insert 1,4,6,3,5,7,8,2,9 */
    bstree_insert(tree, TESTVAL1);
    bstree_insert(tree, TESTVAL4);
    bstree_insert(tree, TESTVAL6);
    bstree_insert(tree, TESTVAL3);
    bstree_insert(tree, TESTVAL5);
    bstree_insert(tree, TESTVAL7);
    bstree_insert(tree, TESTVAL8);
    bstree_insert(tree, TESTVAL2);
    bstree_insert(tree, TESTVAL9);

    to_delete = bstree_search(tree, TESTVAL1);
    bstree_delete(tree, to_delete);
    to_delete = bstree_search(tree, TESTVAL2);
    bstree_delete(tree, to_delete);
    to_delete = bstree_search(tree, TESTVAL3);
    bstree_delete(tree, to_delete);

    /*
    *	we expect a tree with the following structure:
    *	
    *	                     6
    *                      /    \
    *                    4       8
    *                      \    /  \
    *                       5  7    9
    */
    assert(tree->count == 6);
    assert(tree->root->value == TESTVAL6); /* root */
    assert(tree->root->color == BLACK);
    assert(tree->root->left->value == TESTVAL4); /* left subtree */
    assert(tree->root->left->color == BLACK);
    assert(tree->root->left->right->value == TESTVAL5);
    assert(tree->root->left->right->color == RED);
    assert(tree->root->right->value == TESTVAL8); /* right subtree */
    assert(tree->root->right->color == BLACK);
    assert(tree->root->right->left->value == TESTVAL7);
    assert(tree->root->right->left->color == RED);
    assert(tree->root->right->right->value == TESTVAL9);
    assert(tree->root->right->right->color == RED);
}

void
bstree_search_test(void) {
    binary_search_tree_t* tree;
    binary_search_tree_node_t* found_node;
    binary_search_tree_node_t* not_found_node;

    tree = bstree_construct(compare);
    bstree_insert(tree, TESTVAL1);
    bstree_insert(tree, TESTVAL2);
    bstree_insert(tree, TESTVAL3);

    not_found_node = bstree_search(tree, TESTVAL4);
    found_node = bstree_search(tree, TESTVAL3);

    assert(not_found_node == NULL);
    assert(found_node != NULL);
    assert(found_node->value == TESTVAL3);
}

void
bstree_find_min_test(void) {
    binary_search_tree_t* tree;
    binary_search_tree_node_t* min;

    tree = bstree_construct(compare);
    bstree_insert(tree, TESTVAL1);
    bstree_insert(tree, TESTVAL2);
    bstree_insert(tree, TESTVAL3);

    min = bstree_find_min(tree);

    assert(min->value == TESTVAL1);
}

void
bstree_find_max_test(void) {
    binary_search_tree_t* tree;
    binary_search_tree_node_t* max;

    tree = bstree_construct(compare);
    bstree_insert(tree, TESTVAL1);
    bstree_insert(tree, TESTVAL2);
    bstree_insert(tree, TESTVAL3);

    max = bstree_find_min(tree);

    assert(max->value == TESTVAL1);
}

void
bstree_count_test(void) {
    binary_search_tree_t* tree;

    tree = bstree_construct(compare);
    bstree_insert(tree, TESTVAL1);
    bstree_insert(tree, TESTVAL2);
    bstree_insert(tree, TESTVAL3);

    assert(bstree_count(tree) == 3);
}

void
bstree_is_empty_test(void) {
    binary_search_tree_t* tree;
    bool is_empty, is_not_empty;

    tree = bstree_construct(compare);
    is_empty = bstree_is_empty(tree);
    bstree_insert(tree, TESTVAL1);
    bstree_insert(tree, TESTVAL2);
    bstree_insert(tree, TESTVAL3);
    is_not_empty = !bstree_is_empty(tree);

    assert(is_empty);
    assert(is_not_empty);
}

int sum;

void
process(data_type value) {
    sum += value;
}

void
bstree_traverse_test(void) {
    binary_search_tree_t* tree;

    tree = bstree_construct(compare);
    bstree_insert(tree, TESTVAL1);
    bstree_insert(tree, TESTVAL2);
    bstree_insert(tree, TESTVAL3);

    bstree_traverse(tree, process);

    assert(sum == (TESTVAL1 + TESTVAL2 + TESTVAL3));
}

void
bstree_clear_test(void) {
    binary_search_tree_t* tree;

    tree = bstree_construct(compare);
    bstree_insert(tree, TESTVAL1);
    bstree_insert(tree, TESTVAL2);
    bstree_insert(tree, TESTVAL3);

    bstree_clear(&tree);

    assert(tree == NULL);
}

void
bstree_testall(void) {
    bstree_construct_test();
    bstree_insert_test();
    bstree_delete_test();
    bstree_delete_test_2();
    bstree_search_test();
    bstree_find_min_test();
    bstree_find_max_test();
    bstree_count_test();
    bstree_is_empty_test();
    bstree_traverse_test();
    bstree_clear_test();
}