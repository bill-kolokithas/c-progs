#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdbool.h>

#define MAX_VALUE_LEN 80

typedef struct node BSTnode;

char *bst_get(BSTnode *root, int key);
void bst_put(BSTnode **root, int key, const char *value);
bool bst_is_empty(BSTnode *root);
bool bst_contains(BSTnode *root, int key);
int bst_size(BSTnode *node);
int bst_height(BSTnode *root);
int bst_min(BSTnode *root);
int bst_max(BSTnode *root);
int bst_floor(BSTnode *root, int key);
int bst_ceiling(BSTnode *root, int key);
int bst_size_range(BSTnode *root, int lo, int hi);
int bst_rank(BSTnode *root, int key);
int bst_select(BSTnode *root, int k);
void bst_delete_min(BSTnode **root);
void bst_delete_max(BSTnode **root);
void bst_delete(BSTnode **node, int key);
void bst_print(BSTnode *root);
void bst_print_keys(BSTnode *root, int lo, int hi);
void bst_destroy(BSTnode *bst);

#endif
