#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#define MAXLEN 80

typedef char *Value;
typedef struct node *Bst;

Bst bst_put(Bst root, int key, const Value value);
Value bst_get(Bst root, int key);
int bst_is_empty(Bst root);
int bst_size(Bst node);
int bst_contains(Bst root, int key);
int bst_height(Bst root);
int bst_min(Bst root);
int bst_max(Bst root);
int bst_floor(Bst root, int key);
int bst_ceiling(Bst root, int key);
int bst_size_range(Bst root, int lo, int hi);
int bst_rank(Bst root, int key);
int bst_select(Bst root, int k);
Bst bst_delete_min(Bst root);
Bst bst_delete_max(Bst root);
Bst bst_delete(Bst node, int key);
void bst_print(Bst root);
void bst_print_keys(Bst root, int lo, int hi);
void bst_destroy(Bst bst);

#endif
