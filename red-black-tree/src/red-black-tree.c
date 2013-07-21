#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "red-black-tree.h"

#define RED true
#define BLACK false

struct node {
	int key, size;
	char *value;
	struct node *left, *right;
	bool color;
};

#define _rbt_size(node) (node == NULL ? 0 : node->size)
#define rbt_isRed(node) (node == NULL ? false : node->color == RED)

static int max(int a, int b);
static void copy_value(char **src, const char *dest);
static void rbt_flip_colors(RBTnode *node);
static RBTnode *rbt_rotate_left(RBTnode *node);
static RBTnode *rbt_rotate_right(RBTnode *node);
static RBTnode *rbt_move_RED_left(RBTnode *node);
static RBTnode *rbt_move_RED_right(RBTnode *node);
static RBTnode *rbt_balance(RBTnode *node);
static RBTnode *rbt_new_node(int key, const char *value);
static RBTnode *_rbt_put(RBTnode *root, int key, const char *value);
static RBTnode *_rbt_min(RBTnode *node);
static RBTnode *_rbt_max(RBTnode *node);
static RBTnode *_rbt_select(RBTnode *node, int key);
static RBTnode *_rbt_floor(RBTnode *node, int key);
static RBTnode *_rbt_ceiling(RBTnode *node, int key);
static RBTnode *_rbt_delete_min(RBTnode *node);
static RBTnode *_rbt_delete_max(RBTnode *node);
static RBTnode *_rbt_delete(RBTnode *node, int key);


static int max(int a, int b) {

	return a > b ? a : b;
}

static void copy_value(char **src, const char *dest) {

	int len;

	len = strlen(dest);
	len = len > MAX_VALUE_LEN ? MAX_VALUE_LEN : len;

	*src = realloc(*src, len + 1);
	if (*src == NULL) {
		fprintf(stderr, "Error in value copy");
		exit(EXIT_FAILURE);
	}
	strncpy(*src, dest, len);
	(*src)[len] = '\0';
}

static void rbt_flip_colors(RBTnode *node) {

	node->color        = !node->color;
	node->left->color  = !node->left->color;
	node->right->color = !node->right->color;
}

static RBTnode *rbt_rotate_left(RBTnode *node) {

	RBTnode *temp;

	temp        = node->right;
	node->right = temp->left;
	temp->left  = node;
	temp->color = node->color;
	node->color = RED;
	temp->size  = node->size;
	node->size  = 1 + _rbt_size(node->left) + _rbt_size(node->right);

	return temp;
}

static RBTnode *rbt_rotate_right(RBTnode *node) {

	RBTnode *temp;

	temp        = node->left;
	node->left  = temp->right;
	temp->right = node;
	temp->color = node->color;
	node->color = RED;
	temp->size  = node->size;
	node->size  = 1 + _rbt_size(node->left) + _rbt_size(node->right);

	return temp;
}

static RBTnode *rbt_move_RED_left(RBTnode *node) {

	rbt_flip_colors(node);

	if (rbt_isRed(node->right->left)) {
		node->right = rbt_rotate_right(node->right);
		node        = rbt_rotate_left(node);
	}
	return node;
}

static RBTnode *rbt_move_RED_right(RBTnode *node) {

	rbt_flip_colors(node);

	if (rbt_isRed(node->left->left))
		node = rbt_rotate_right(node);

	return node;
}

static RBTnode *rbt_balance(RBTnode *node) {

	if (rbt_isRed(node->right))
		node = rbt_rotate_left(node);

	if (rbt_isRed(node->left) && rbt_isRed(node->left->left))
		node = rbt_rotate_right(node);

	if (rbt_isRed(node->left) && rbt_isRed(node->right))
		rbt_flip_colors(node);

	node->size = 1 + _rbt_size(node->left) + _rbt_size(node->right);

	return node;
}

static RBTnode *rbt_new_node(int key, const char *value) {

	RBTnode *node;

	node = malloc(sizeof(struct node));
	if (node == NULL) {
		fprintf(stderr, "Error in node creation");
		exit(EXIT_FAILURE);
	}
	node->value = NULL;
	copy_value(&node->value, value);
	node->key   = key;
	node->size  = 1;
	node->left  = NULL;
	node->right = NULL;
	node->color = RED;

	return node;
}

void rbt_put(RBTnode **root, int key, const char *value) {

	*root = _rbt_put(*root, key, value);
	(*root)->color = BLACK;
}

static RBTnode *_rbt_put(RBTnode *node, int key, const char *value) {

	int cmp;

	if (node == NULL)
		return rbt_new_node(key, value);

	cmp = key - node->key;
	if (cmp < 0)
		node->left  = _rbt_put(node->left, key, value);
	else if (cmp > 0)
		node->right = _rbt_put(node->right, key, value);
	else
		copy_value(&node->value, value);

	if (rbt_isRed(node->right) && !rbt_isRed(node->left))
		node = rbt_rotate_left(node);

	if (rbt_isRed(node->left) && rbt_isRed(node->left->left))
		node = rbt_rotate_right(node);

	if (rbt_isRed(node->left) && rbt_isRed(node->right))
		rbt_flip_colors(node);

	node->size = 1 + _rbt_size(node->left) + _rbt_size(node->right);

	return node;
}

char *rbt_get(RBTnode *root, int key) {

	int cmp;

	if (root == NULL)
		return NULL;

	cmp = key - root->key;
	if (cmp < 0)
		return rbt_get(root->left, key);
	else if (cmp > 0)
		return rbt_get(root->right, key);

	return root->value;
}

bool rbt_isEmpty(RBTnode *root) {

	return _rbt_size(root) == 0;
}

bool rbt_contains(RBTnode *root, int key) {

	return rbt_get(root, key) != NULL;
}

int rbt_size(RBTnode *node) {

	if (node == NULL)
		return 0;

	return node->size;
}

int rbt_height(RBTnode *root) {

	if (root == NULL)
		return -1;

	return 1 + max(rbt_height(root->left), rbt_height(root->right));
}

int rbt_min(RBTnode *root) {

	if (rbt_isEmpty(root))
		return -1;

	return _rbt_min(root)->key;
}

static RBTnode *_rbt_min(RBTnode *node) {

	if (node->left == NULL)
		return node;

	return _rbt_min(node->left);
}

int rbt_max(RBTnode *root) {

	if (rbt_isEmpty(root))
		return -1;

	return _rbt_max(root)->key;
}

static RBTnode *_rbt_max(RBTnode *node) {

	if (node->right == NULL)
		return node;

	return _rbt_max(node->right);
}

int rbt_floor(RBTnode *root, int key) {

	RBTnode *node = _rbt_floor(root, key);
	if (node == NULL)
		return -1;

	return node->key;
}

static RBTnode *_rbt_floor(RBTnode *node, int key) {

	int cmp;
	RBTnode *temp;

	if (node == NULL)
		return NULL;

	cmp = key - node->key;
	if (cmp == 0)
		return node;
	else if (cmp < 0)
		return _rbt_floor(node->left, key);
	else {
		temp = _rbt_floor(node->right, key);
		if (temp != NULL)
			return temp;
	}
	return node;
}

int rbt_ceiling(RBTnode *root, int key) {

	RBTnode *node = _rbt_ceiling(root, key);
	if (node == NULL)
		return -1;

	return node->key;
}

static RBTnode *_rbt_ceiling(RBTnode *node, int key) {

	int cmp;
	RBTnode *temp;

	if (node == NULL)
		return NULL;

	cmp = key - node->key;
	if (cmp == 0)
		return node;
	else if (cmp < 0) {
		temp = _rbt_ceiling(node->left, key);
		if (temp != NULL)
			return temp;
		return node;
	}
	return _rbt_ceiling(node->right, key);
}

int rbt_size_range(RBTnode *root, int lo, int hi) {

	if (lo > hi)
		return 0;
	else if (rbt_contains(root, hi))
		return 1 + rbt_rank(root, hi) - rbt_rank(root, lo);

	return rbt_rank(root, hi) - rbt_rank(root, lo);
}

int rbt_rank(RBTnode *root, int key) {

	int cmp;

	if (root == NULL)
		return 0;

	cmp = key - root->key;
	if (cmp < 0)
		return rbt_rank(root->left, key);
	else if (cmp > 0)
		return 1 + _rbt_size(root->left) + rbt_rank(root->right, key);

	return _rbt_size(root->left);
}

int rbt_select(RBTnode *root, int k) {

	if (k < 0 || k >= _rbt_size(root))
		return -1;

	return _rbt_select(root, k)->key;
}

static RBTnode *_rbt_select(RBTnode *node, int k) {

	int test;

	if (node == NULL)
		return NULL;

	test = _rbt_size(node->left);
	if (test > k)
		return _rbt_select(node->left, k);
	else if (test < k)
		return _rbt_select(node->right, k - test - 1);

	return node;
}

void rbt_delete_min(RBTnode **root) {

	if (rbt_isEmpty(*root))
		return;

	if (!rbt_isRed((*root)->left) && !rbt_isRed((*root)->right))
		(*root)->color = RED;

	*root = _rbt_delete_min(*root);

	if (!rbt_isEmpty(*root))
		(*root)->color = BLACK;
}

static RBTnode *_rbt_delete_min(RBTnode *node) {

	if (node->left == NULL) {
		free(node->value);
		free(node);
		return NULL;
	}
	if (!rbt_isRed(node->left) && !rbt_isRed(node->left->left))
		node = rbt_move_RED_left(node);

	node->left = _rbt_delete_min(node->left);

	return rbt_balance(node);
}

void rbt_delete_max(RBTnode **root) {

	if (rbt_isEmpty(*root))
		return;

	if (!rbt_isRed((*root)->left) && !rbt_isRed((*root)->right))
		(*root)->color = RED;

	*root = _rbt_delete_max(*root);

	if (!rbt_isEmpty(*root))
		(*root)->color = BLACK;
}

static RBTnode *_rbt_delete_max(RBTnode *node) {

	if (rbt_isRed(node->left))
		node = rbt_rotate_right(node);

	if (node->right == NULL) {
		free(node->value);
		free(node);
		return NULL;
	}
	if (!rbt_isRed(node->right) && !rbt_isRed(node->right->left))
		node = rbt_move_RED_right(node);

	node->right = _rbt_delete_max(node->right);

	return rbt_balance(node);
}

void rbt_delete(RBTnode **root, int key) {

	if (!rbt_contains(*root, key))
		return;

	if (!rbt_isRed((*root)->left) && !rbt_isRed((*root)->right))
		(*root)->color = RED;

	*root = _rbt_delete(*root, key);

	if (!rbt_isEmpty(*root))
		(*root)->color = BLACK;
}

static RBTnode *_rbt_delete(RBTnode *node, int key) {

	int cmp;
	char *value;

	cmp = key - node->key;
	if (cmp < 0) {
		if (!rbt_isRed(node->left) && !rbt_isRed(node->left->left))
			node = rbt_move_RED_left(node);

		node->left = _rbt_delete(node->left, key);
	}
	else {
		if (rbt_isRed(node->left))
			node = rbt_rotate_right(node);

		if (cmp == 0 && node->right == NULL) {
			free(node->value);
			free(node);
			return NULL;
		}
		if (!rbt_isRed(node->right) && !rbt_isRed(node->right->left))
			node = rbt_move_RED_right(node);

		if (cmp == 0) {
			node->key = _rbt_min(node->right)->key;
			value = rbt_get(node->right, node->key);
			copy_value(&node->value, value);
			node->right = _rbt_delete_min(node->right);
		} else
			node->right = _rbt_delete(node->right, key);
	}
	return rbt_balance(node);
}

void rbt_print(RBTnode *root) {

	if (root == NULL)
		return;

	rbt_print(root->left);
	printf("%d %s\n", root->key, root->value);
	rbt_print(root->right);
}

void rbt_print_keys(RBTnode *root, int lo, int hi) {

	int cmp_lo, cmp_hi;

	if (root == NULL)
		return;

	cmp_lo = lo - root->key;
	cmp_hi = hi - root->key;

	if (cmp_lo < 0)
		rbt_print_keys(root->left, lo, hi);
	if (cmp_lo <= 0 && cmp_hi >= 0)
		printf("%d\n", root->key);
	if (cmp_hi > 0)
		rbt_print_keys(root->right, lo, hi);
}

void rbt_destroy(RBTnode *root) {

	RBTnode *left, *right;

	if (root == NULL)
		return;

	left  = root->left;
	right = root->right;
	free(root->value);
	free(root);
	rbt_destroy(left);
	rbt_destroy(right);
}
