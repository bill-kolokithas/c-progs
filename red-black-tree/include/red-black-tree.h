#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <stdbool.h>

#define MAX_VALUE_LEN 80

typedef struct node RBTnode;

char *rbt_get(RBTnode *root, int key);
void rbt_put(RBTnode **root, int key, const char *value);
bool rbt_isEmpty(RBTnode *root);
bool rbt_contains(RBTnode *root, int key);
int rbt_size(RBTnode *node);
int rbt_height(RBTnode *root);
int rbt_min(RBTnode *root);
int rbt_max(RBTnode *root);
int rbt_floor(RBTnode *root, int key);
int rbt_ceiling(RBTnode *root, int key);
int rbt_size_range(RBTnode *root, int lo, int hi);
int rbt_rank(RBTnode *root, int key);
int rbt_select(RBTnode *root, int k);
void rbt_delete_min(RBTnode **root);
void rbt_delete_max(RBTnode **root);
void rbt_delete(RBTnode **root, int key);
void rbt_print(RBTnode *root);
void rbt_print_keys(RBTnode *root, int lo, int hi);
void rbt_destroy(RBTnode *root);

#endif
