#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdbool.h>

#define MAX_VALUE_LEN 80

typedef struct node RBnode;

void rbt_put(RBnode **root, int key, const char *value);
char *rbt_get(RBnode *root, int key);
bool rbt_isEmpty(RBnode *root);
bool rbt_contains(RBnode *root, int key);
int rbt_size(RBnode *node);
int rbt_height(RBnode *root);
int rbt_min(RBnode *root);
int rbt_max(RBnode *root);
int rbt_floor(RBnode *root, int key);
int rbt_ceiling(RBnode *root, int key);
int rbt_size_range(RBnode *root, int lo, int hi);
int rbt_rank(RBnode *root, int key);
int rbt_select(RBnode *root, int k);
void rbt_delete_min(RBnode **root);
void rbt_delete_max(RBnode **root);
void rbt_delete(RBnode **root, int key);
void rbt_print(RBnode *root);
void rbt_print_keys(RBnode *root, int lo, int hi);
void rbt_destroy(RBnode *root);

#endif
