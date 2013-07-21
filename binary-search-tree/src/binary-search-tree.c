#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "binary-search-tree.h"

struct node {
	int key, size;
	char *value;
	struct node *left, *right;
};

#define _bst_size(node) (node == NULL ? 0 : node->size)

static int max(int a, int b);
static BSTnode *bst_new_node(int key, const char *value);
static BSTnode *_bst_put(BSTnode *node, int key, const char *value);
static BSTnode *_bst_min(BSTnode *node);
static BSTnode *_bst_max(BSTnode *node);
static BSTnode *_bst_select(BSTnode *node, int key);
static BSTnode *_bst_floor(BSTnode *node, int key);
static BSTnode *_bst_ceiling(BSTnode *node, int key);
static BSTnode *_bst_delete_min(BSTnode *node, bool flag);
static BSTnode *_bst_delete_max(BSTnode *node, bool flag);
static BSTnode *_bst_delete(BSTnode *node, int key);


static int max(int a, int b) {

	return a > b ? a : b;
}

static BSTnode *bst_new_node(int key, const char *value) {

	int len;
	BSTnode *node;

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
	node->key = key;
	node->size = 1;
	node->left = node->right = NULL;

	return node;
}

void bst_put(BSTnode **root, int key, const char *value) {

	*root = _bst_put(*root, key, value);
}

static BSTnode *_bst_put(BSTnode *node, int key, const char *value) {

	int cmp, len;

	if (node == NULL)
		return bst_new_node(key, value);

	cmp = key - node->key;
	if (cmp < 0)
		node->left = _bst_put(node->left, key, value);
	else if (cmp > 0)
		node->right = _bst_put(node->right, key, value);
	else {
		len = strlen(value);
		node->value = realloc(node->value, (len = len > MAX_VALUE_LEN ? MAX_VALUE_LEN : len) + 1);
		if (node->value == NULL) {
			fprintf(stderr, "Error in put");
			exit(EXIT_FAILURE);
		}
		strncpy(node->value, value, len);
		node->value[len] = '\0';
	}
	node->size = 1 + _bst_size(node->left) + _bst_size(node->right);

	return node;
}

char *bst_get(BSTnode *root, int key) {

	int cmp;

	if (root == NULL)
		return NULL;

	cmp = key - root->key;
	if (cmp < 0)
		return bst_get(root->left, key);
	else if (cmp > 0)
		return bst_get(root->right, key);

	return root->value;
}

bool bst_is_empty(BSTnode *root) {

	return _bst_size(root) == 0;
}

bool bst_contains(BSTnode *root, int key) {

	return bst_get(root, key) != NULL;
}

int bst_size(BSTnode *node) {

	if (node == NULL)
		return 0;

	return node->size;
}

int bst_height(BSTnode *root) {

	if (root == NULL)
		return -1;

	return 1 + max(bst_height(root->left), bst_height(root->right));
}

int bst_min(BSTnode *root) {

	if (bst_is_empty(root))
		return -1;

	return _bst_min(root)->key;
}

static BSTnode *_bst_min(BSTnode *node) {

	if (node->left == NULL)
		return node;

	return _bst_min(node->left);
}

int bst_max(BSTnode *root) {

	if (bst_is_empty(root))
		return -1;

	return _bst_max(root)->key;
}

static BSTnode *_bst_max(BSTnode *node) {

	if (node->right == NULL)
		return node;

	return _bst_max(node->right);
}

int bst_floor(BSTnode *root, int key) {

	BSTnode *node = _bst_floor(root, key);
	if (node == NULL)
		return -1;

	return node->key;
}

static BSTnode *_bst_floor(BSTnode *node, int key) {

	int cmp;
	BSTnode *temp;

	if (node == NULL)
		return NULL;

	cmp = key - node->key;
	if (cmp == 0)
		return node;
	else if (cmp < 0)
		return _bst_floor(node->left, key);
	else {
		temp = _bst_floor(node->right, key);
		if (temp != NULL)
			return temp;
	}
	return node;
}

int bst_ceiling(BSTnode *root, int key) {

	BSTnode *node = _bst_ceiling(root, key);
	if (node == NULL)
		return -1;

	return node->key;
}

static BSTnode *_bst_ceiling(BSTnode *node, int key) {

	int cmp;
	BSTnode *temp;

	if (node == NULL)
		return NULL;

	cmp = key - node->key;
	if (cmp == 0)
		return node;
	else if (cmp < 0) {
		temp = _bst_ceiling(node->left, key);
		if (temp != NULL)
			return temp;
		return node;
	}
	return _bst_ceiling(node->right, key);
}

int bst_size_range(BSTnode *root, int lo, int hi) {

	if (lo > hi)
		return 0;
	else if (bst_contains(root, hi))
		return 1 + bst_rank(root, hi) - bst_rank(root, lo);

	return bst_rank(root, hi) - bst_rank(root, lo);
}

int bst_rank(BSTnode *root, int key) {

	int cmp;

	if (root == NULL)
		return 0;

	cmp = key - root->key;
	if (cmp < 0)
		return bst_rank(root->left, key);
	else if (cmp > 0)
		return 1 + _bst_size(root->left) + bst_rank(root->right, key);

	return _bst_size(root->left);
}

int bst_select(BSTnode *root, int k) {

	if (k < 0 || k >= _bst_size(root))
		return -1;

	return _bst_select(root, k)->key;
}

static BSTnode *_bst_select(BSTnode *node, int k) {

	int test;

	if (node == NULL)
		return NULL;

	test = _bst_size(node->left);
	if (test > k)
		return _bst_select(node->left, k);
	else if (test < k)
		return _bst_select(node->right, k - test - 1);

	return node;
}

void bst_delete_min(BSTnode **root) {

	if (bst_is_empty(*root))
		return;

	*root = _bst_delete_min(*root, true);
}

static BSTnode *_bst_delete_min(BSTnode *node, bool flag) {

	BSTnode *right;

	if (node->left == NULL) {
		right = node->right;
		if (flag) {
			free(node->value);
			free(node);
		}
		return right;
	}
	node->left = _bst_delete_min(node->left, flag);
	node->size = 1 + _bst_size(node->left) + _bst_size(node->right);

	return node;
}

void bst_delete_max(BSTnode **root) {

	if (bst_is_empty(*root))
		return;

	*root = _bst_delete_max(*root, true);
}

static BSTnode *_bst_delete_max(BSTnode *node, bool flag) {

	BSTnode *left;

	if (node->right == NULL) {
		left = node->left;
		if (flag) {
			free(node->value);
			free(node);
		}
		return left;
	}
	node->right = _bst_delete_max(node->right, flag);
	node->size = 1 + _bst_size(node->left) + _bst_size(node->right);

	return node;
}

void bst_delete(BSTnode **root, int key) {

	if (!bst_contains(*root, key))
		return;

	*root = _bst_delete(*root, key);
}

static BSTnode *_bst_delete(BSTnode *node, int key) {

	BSTnode *temp;
	int cmp;

	if (node == NULL)
		return NULL;

	cmp = key - node->key;
	if (cmp < 0)
		node->left = _bst_delete(node->left, key);
	else if (cmp > 0)
		node->right = _bst_delete(node->right, key);
	else {
		if (node->right == NULL)
			return node->left;
		else if (node->left == NULL)
			return node->right;

		temp = node;
		node = _bst_min(temp->right);
		node->right = _bst_delete_min(temp->right, false);
		node->left  = temp->left;
		free(temp->value);
		free(temp);
	}
	node->size = 1 + _bst_size(node->left) + _bst_size(node->right);

	return node;
}

void bst_print(BSTnode *root) {

	if (root == NULL)
		return;

	bst_print(root->left);
	printf("%d %s\n", root->key, root->value);
	bst_print(root->right);
}

void bst_print_keys(BSTnode *root, int lo, int hi) {

	int cmp_lo, cmp_hi;

	if (root == NULL)
		return;

	cmp_lo = lo - root->key;
	cmp_hi = hi - root->key;

	if (cmp_lo < 0)
		bst_print_keys(root->left, lo, hi);
	if (cmp_lo <= 0 && cmp_hi >= 0)
		printf("%d\n", root->key);
	if (cmp_hi > 0)
		bst_print_keys(root->right, lo, hi);
}

void bst_destroy(BSTnode *root) {

	BSTnode *left, *right;

	if (root == NULL)
		return;

	left = root->left;
	right = root->right;
	free(root->value);
	free(root);
	bst_destroy(left);
	bst_destroy(right);
}
