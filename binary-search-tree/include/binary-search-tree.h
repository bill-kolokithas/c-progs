#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#define MAXLEN 80

typedef char *Value;
typedef struct node {
	int key, size;
	char *value;
	struct node *left, *right;
} *Bst;

#define max(a, b) ({    \
	typeof(a) _a = (a); \
	typeof(b) _b = (b); \
	_a > _b ? _a : _b;  \
})

#define bst_is_empty(root) (bst_size(root) == 0)
#define bst_size(node) ((node) == NULL ? 0 : node->size)
#define bst_contains(root, key) (bst_get(root, key) != NULL)
#define bst_min(root) (bst_is_empty(root) ? -1 : _bst_min(root)->key)
#define bst_max(root) (bst_is_empty(root) ? -1 : _bst_max(root)->key)
#define bst_floor(root, _key) ({ Bst node; (node = _bst_floor(root, _key)) ? node->key : -1; })
#define bst_ceiling(root, _key) ({ Bst node; (node = _bst_ceiling(root, _key)) ? node->key : -1; })
#define bst_select(root, k) ({ (k < 0 || k >= bst_size(root)) ? -1 : _bst_select(root, k)->key; })

Value bst_get(Bst root, int key);
Bst bst_put(Bst root, int key, Value value);
Bst _bst_min(Bst node);
Bst _bst_max(Bst node);
Bst _bst_floor(Bst root, int key);
Bst _bst_ceiling(Bst root, int key);
Bst _bst_select(Bst root, int key);
int bst_rank(Bst root, int key);
int bst_height(Bst root);
int bst_size_range(Bst root, int lo, int hi);
void bst_print(Bst root);
void bst_print_keys(Bst root, int lo, int hi);
void bst_destroy(Bst bst);

#endif
