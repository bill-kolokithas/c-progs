#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#define MAX_VALUE_LEN 80

typedef char *Value;
typedef struct node *BStree;

BStree bst_put(BStree root, int key, const Value value);
Value bst_get(BStree root, int key);
int bst_is_empty(BStree root);
int bst_size(BStree node);
int bst_contains(BStree root, int key);
int bst_height(BStree root);
int bst_min(BStree root);
int bst_max(BStree root);
int bst_floor(BStree root, int key);
int bst_ceiling(BStree root, int key);
int bst_size_range(BStree root, int lo, int hi);
int bst_rank(BStree root, int key);
int bst_select(BStree root, int k);
BStree bst_delete_min(BStree root);
BStree bst_delete_max(BStree root);
BStree bst_delete(BStree node, int key);
void bst_print(BStree root);
void bst_print_keys(BStree root, int lo, int hi);
void bst_destroy(BStree bst);

#endif
