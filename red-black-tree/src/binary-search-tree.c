#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "binary-search-tree.h"

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
static void rbt_flip_colors(RBnode *node);
static RBnode *rbt_rotate_left(RBnode *node);
static RBnode *rbt_rotate_right(RBnode *node);
static RBnode *rbt_new_node(int key, const char *value);
static RBnode *_rbt_put(RBnode *root, int key, const char *value);
static RBnode *_rbt_min(RBnode *node);
static RBnode *_rbt_max(RBnode *node);
static RBnode *_rbt_select(RBnode *node, int key);
static RBnode *_rbt_floor(RBnode *node, int key);
static RBnode *_rbt_ceiling(RBnode *node, int key);
static RBnode *_rbt_delete_min(RBnode *node, bool flag);
static RBnode *_rbt_delete_max(RBnode *node, bool flag);
static RBnode *_rbt_delete(RBnode *node, int key);


static RBnode *rbt_rotate_left(RBnode *node) {

	RBnode *temp = node->right;
	node->right = temp->left;
	temp->left  = node;
	temp->color = node->color;
	node->color = RED;
	temp->size  = node->size;
	node->size  = 1 + _rbt_size(node->left) + _rbt_size(node->right);

	return temp;
}

static RBnode *rbt_rotate_right(RBnode *node) {

	RBnode *temp = node->left;
	node->left  = temp->right;
	temp->right = node;
	temp->color = node->color;
	node->color = RED;
	temp->size  = node->size;
	node->size  = 1 + _rbt_size(node->left) + _rbt_size(node->right);

	return temp;
}

static void rbt_flip_colors(RBnode *node) {

	node->color        = !node->color;
	node->left->color  = !node->left->color;
	node->right->color = !node->right->color;
}

static RBnode *rbt_new_node(int key, const char *value) {

	int len;
	RBnode *node;

	node = malloc(sizeof(struct node));
	if (node == NULL) {
		fprintf(stderr, "Error in node creation");
		exit(EXIT_FAILURE);
	}
	len = strlen(value);
	node->value = malloc((len = len > MAX_VALUE_LEN ? MAX_VALUE_LEN : len) + 1);
	if (node->value == NULL) {
		fprintf(stderr, "Error in node creation");
		exit(EXIT_FAILURE);
	}
	strncpy(node->value, value, len);
	node->value[len] = '\0';
	node->key   = key;
	node->size  = 1;
	node->left  = node->right = NULL;
	node->color = RED;

	return node;
}

void rbt_put(RBnode **root, int key, const char *value) {

	*root = _rbt_put(*root, key, value);
	(*root)->color = BLACK;
}

static RBnode *_rbt_put(RBnode *root, int key, const char *value) {

	int cmp, len;

	if (root == NULL)
		return rbt_new_node(key, value);

	cmp = key - root->key;
	if (cmp < 0)
		root->left = _rbt_put(root->left, key, value);
	else if (cmp > 0)
		root->right = _rbt_put(root->right, key, value);
	else {
		len = strlen(value);
		root->value = realloc(root->value, (len = len > MAX_VALUE_LEN ? MAX_VALUE_LEN : len) + 1);
		if (root->value == NULL) {
			fprintf(stderr, "Error in put");
			exit(EXIT_FAILURE);
		}
		strncpy(root->value, value, len);
		root->value[len] = '\0';
	}
	if (rbt_isRed(root->right) && !rbt_isRed(root->left))
		root = rbt_rotate_left(root);

	if (rbt_isRed(root->left) && rbt_isRed(root->left->left))
		root = rbt_rotate_right(root);

	if (rbt_isRed(root->left) && rbt_isRed(root->right))
		rbt_flip_colors(root);

	root->size = 1 + _rbt_size(root->left) + _rbt_size(root->right);

	return root;
}

char *rbt_get(RBnode *root, int key) {

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

bool rbt_isEmpty(RBnode *root) {

	return _rbt_size(root) == 0;
}

bool rbt_contains(RBnode *root, int key) {

	return rbt_get(root, key) != NULL;
}

int rbt_size(RBnode *node) {

	if (node == NULL)
		return 0;

	return node->size;
}

int rbt_height(RBnode *root) {

	if (root == NULL)
		return -1;

	return 1 + max(rbt_height(root->left), rbt_height(root->right));
}

static int max(int a, int b) {

	return a > b ? a : b;
}

int rbt_min(RBnode *root) {

	if (rbt_isEmpty(root))
		return -1;

	return _rbt_min(root)->key;
}

static RBnode *_rbt_min(RBnode *node) {

	if (node->left == NULL)
		return node;

	return _rbt_min(node->left);
}

int rbt_max(RBnode *root) {

	if (rbt_isEmpty(root))
		return -1;

	return _rbt_max(root)->key;
}

static RBnode *_rbt_max(RBnode *node) {

	if (node->right == NULL)
		return node;

	return _rbt_max(node->right);
}

int rbt_floor(RBnode *root, int key) {

	RBnode *node = _rbt_floor(root, key);
	if (node == NULL)
		return -1;

	return node->key;
}

static RBnode *_rbt_floor(RBnode *node, int key) {

	int cmp;
	RBnode *temp;

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

int rbt_ceiling(RBnode *root, int key) {

	RBnode *node = _rbt_ceiling(root, key);
	if (node == NULL)
		return -1;

	return node->key;
}

static RBnode *_rbt_ceiling(RBnode *node, int key) {

	int cmp;
	RBnode *temp;

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

int rbt_size_range(RBnode *root, int lo, int hi) {

	if (lo > hi)
		return 0;
	else if (rbt_contains(root, hi))
		return 1 + rbt_rank(root, hi) - rbt_rank(root, lo);

	return rbt_rank(root, hi) - rbt_rank(root, lo);
}

int rbt_rank(RBnode *root, int key) {

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

int rbt_select(RBnode *root, int k) {

	if (k < 0 || k >= _rbt_size(root))
		return -1;

	return _rbt_select(root, k)->key;
}

static RBnode *_rbt_select(RBnode *node, int k) {

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

void rbt_delete_min(RBnode **root) {

	if (rbt_isEmpty(*root))
		*root = NULL;

	*root = _rbt_delete_min(*root, true);
}

static RBnode *_rbt_delete_min(RBnode *node, bool flag) {

	RBnode *right;

	if (node->left == NULL) {
		right = node->right;
		if (flag) {
			free(node->value);
			free(node);
		}
		return right;
	}
	node->left = _rbt_delete_min(node->left, flag);
	node->size = 1 + _rbt_size(node->left) + _rbt_size(node->right);

	return node;
}

void rbt_delete_max(RBnode **root) {

	if (rbt_isEmpty(*root))
		*root = NULL;

	*root = _rbt_delete_max(*root, true);
}

static RBnode *_rbt_delete_max(RBnode *node, bool flag) {

	RBnode *left;

	if (node->right == NULL) {
		left = node->left;
		if (flag) {
			free(node->value);
			free(node);
		}
		return left;
	}
	node->right = _rbt_delete_max(node->right, flag);
	node->size = 1 + _rbt_size(node->left) + _rbt_size(node->right);

	return node;
}

void rbt_delete(RBnode **root, int key) {

	*root = _rbt_delete(*root, key);
}

static RBnode *_rbt_delete(RBnode *node, int key) {

	RBnode *temp;
	int cmp;

	if (node == NULL)
		return NULL;

	cmp = key - node->key;
	if (cmp < 0)
		node->left = _rbt_delete(node->left, key);
	else if (cmp > 0)
		node->right = _rbt_delete(node->right, key);
	else {
		if (node->right == NULL)
			return node->left;
		else if (node->left == NULL)
			return node->right;

		temp = node;
		node = _rbt_min(temp->right);
		node->right = _rbt_delete_min(temp->right, false);
		node->left = temp->left;
		free(temp->value);
		free(temp);
	}
	node->size = 1 + _rbt_size(node->left) + _rbt_size(node->right);
	return node;
}

void rbt_print(RBnode *root) {

	if (root == NULL)
		return;

	rbt_print(root->left);
	printf("%d %s\n", root->key, root->value);
	rbt_print(root->right);
}

void rbt_print_keys(RBnode *root, int lo, int hi) {

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

void rbt_destroy(RBnode *root) {

	RBnode *left, *right;

	if (root == NULL)
		return;

	left = root->left;
	right = root->right;
	free(root->value);
	free(root);
	rbt_destroy(left);
	rbt_destroy(right);
}
