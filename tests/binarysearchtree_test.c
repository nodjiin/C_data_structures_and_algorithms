#include <assert.h>
#include "binarysearchtree_test.h"
#include "data_structures/binarysearchtree.h"
#include "testvalues.h"

void
bstree_construct_test(void) {
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
bstree_insert_test(void) {
    assert(0);
}

void
bstree_delete_test(void) {
    assert(0);
}

void
bstree_search_test(void) {
    assert(0);
}

void
bstree_find_min_test(void) {
    assert(0);
}

void
bstree_find_max_test(void) {
    assert(0);
}

void
tree_count_test(void) {
    assert(0);
}

void
tree_is_empty_test(void) {
    assert(0);
}

void
bstree_traverse_test(void) {
    assert(0);
}

void
bstree_clear_test(void) {
    assert(0);
}

void
bstree_testall(void) {
    bstree_construct_test();
    bstree_insert_test();
    bstree_delete_test();
    bstree_search_test();
    bstree_find_min_test();
    bstree_find_max_test();
    tree_count_test();
    tree_is_empty_test();
    bstree_traverse_test();
    bstree_clear_test();
}