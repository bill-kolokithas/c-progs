#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary-search-tree.h"

struct node {
	int key, size;
	char *value;
	struct node *left, *right;
};

static int max(int a, int b);
static Bst _bst_min(Bst node);
static Bst _bst_max(Bst node);
static Bst _bst_select(Bst node, int key);
static Bst _bst_floor(Bst node, int key);
static Bst _bst_ceiling(Bst node, int key);
Bst _bst_delete_min(Bst node);
Bst _bst_delete_max(Bst node);

static Bst bst_new_node(int key, Value value) {

	int len;
	Bst node;

	node = malloc(sizeof(struct node));
	if (node == NULL) {
		fprintf(stderr, "Error in node creation");
		exit(EXIT_FAILURE);
	}
	len = strlen(value);
	node->value = malloc((len = len > MAXLEN ? MAXLEN : len) + 1);
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

Bst bst_put(Bst root, int key, Value value) {

	int cmp, len;

	if (root == NULL)
		return bst_new_node(key, value);

	cmp = key - root->key;
	if (cmp < 0)
		root->left = bst_put(root->left, key, value);
	else if (cmp > 0)
		root->right = bst_put(root->right, key, value);
	else {
		len = strlen(value);
		root->value = realloc(root->value, (len = len > MAXLEN ? MAXLEN : len) + 1);
		if (root->value == NULL) {
			fprintf(stderr, "Error in put");
			exit(EXIT_FAILURE);
		}
		strncpy(root->value, value, len);
		root->value[len] = '\0';
	}
	root->size = 1 + bst_size(root->left) + bst_size(root->right);
	return root;
}

Value bst_get(Bst root, int key) {

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

int bst_is_empty(Bst root) {

	return bst_size(root) == 0;
}

int bst_size(Bst node) {

	if (node == NULL)
		return 0;

	return node->size;
}

int bst_contains(Bst root, int key) {

	return bst_get(root, key) != NULL;
}

int bst_height(Bst root) {

	if (root == NULL)
		return -1;

	return 1 + max(bst_height(root->left), bst_height(root->right));
}

static int max(int a, int b) {

	return a > b ? a : b;
}

int bst_min(Bst root) {

	if (bst_is_empty(root))
		return -1;

	return _bst_min(root)->key;
}

static Bst _bst_min(Bst node) {

	if (node->left == NULL)
		return node;

	return _bst_min(node->left);
}

int bst_max(Bst root) {

	if (bst_is_empty(root))
		return -1;

	return _bst_max(root)->key;
}

static Bst _bst_max(Bst node) {

	if (node->right == NULL)
		return node;

	return _bst_max(node->right);
}

int bst_floor(Bst root, int key) {

	Bst node = _bst_floor(root, key);
	if (node == NULL)
		return -1;

	return node->key;
}

static Bst _bst_floor(Bst node, int key) {

	int cmp;
	Bst test;

	if (node == NULL)
		return NULL;

	cmp = key - node->key;
	if (cmp == 0)
		return node;
	else if (cmp < 0)
		return _bst_floor(node->left, key);
	else {
		test = _bst_floor(node->right, key);
		if (test != NULL)
			return test;
	}
	return node;
}

int bst_ceiling(Bst root, int key) {

	Bst node = _bst_ceiling(root, key);
	if (node == NULL)
		return -1;

	return node->key;
}

static Bst _bst_ceiling(Bst node, int key) {

	int cmp;
	Bst test;

	if (node == NULL)
		return NULL;

	cmp = key - node->key;
	if (cmp == 0)
		return node;
	else if (cmp < 0) {
		test = _bst_ceiling(node->left, key);
		if (test != NULL)
			return test;
		return node;
	}
	return _bst_ceiling(node->right, key);
}

int bst_size_range(Bst root, int lo, int hi) {

	if (lo > hi)
		return 0;
	else if (bst_contains(root, hi))
		return 1 + bst_rank(root, hi) - bst_rank(root, lo);

	return bst_rank(root, hi) - bst_rank(root, lo);
}

int bst_rank(Bst root, int key) {

	int cmp;

	if (root == NULL)
		return 0;

	cmp = key - root->key;
	if (cmp < 0)
		return bst_rank(root->left, key);
	else if (cmp > 0)
		return 1 + bst_size(root->left) + bst_rank(root->right, key);

	return bst_size(root->left);
}

int bst_select(Bst root, int k) {

	if (k < 0 || k >= bst_size(root))
		return -1;

	return _bst_select(root, k)->key;
}

static Bst _bst_select(Bst node, int k) {

	int test;

	if (node == NULL)
		return NULL;

	test = bst_size(node->left);
	if (test > k)
		return _bst_select(node->left, k);
	else if (test < k)
		return _bst_select(node->right, k - test - 1);

	return node;
}

int bst_delete_min(Bst root) {

	if (bst_is_empty(root))
		return -1;

	return _bst_delete_min(root)->key;
}

Bst _bst_delete_min(Bst node) {

	if (node->left == NULL)
		return node->right;

	node->left = _bst_delete_min(node->left);
	node->size = 1 + bst_size(node->left) + bst_size(node->right);

	return node;
}

int bst_delete_max(Bst root) {

	if (bst_is_empty(root))
		return -1;

	return _bst_delete_max(root)->key;
}

Bst _bst_delete_max(Bst node) {

	if (node->right == NULL)
		return node->left;

	node->right = _bst_delete_max(node->right);
	node->size = 1 + bst_size(node->left) + bst_size(node->right);

	return node;
}

Bst bst_delete(Bst node, int key) {

	Bst test;
	int cmp;

	if (node == NULL)
		return NULL;

	cmp = key - node->key;
	if (cmp < 0)
		node->left = bst_delete(node->left, key);
	else if (cmp > 0)
		node->right = bst_delete(node->right, key);
	else {
		if (node->right == NULL)
			return node->left;
		else if (node->left == NULL)
			return node->right;

		test = node;
		node = _bst_min(test->right);
		node->right = _bst_delete_min(test->right);
		node->left = test->left;
	}
	node->size = 1 + bst_size(node->left) + bst_size(node->right);
	return node;
}

void bst_print(Bst root) {

	if (root == NULL)
		return;

	bst_print(root->left);
	printf("%d %s\n", root->key, root->value);
	bst_print(root->right);
}

void bst_print_keys(Bst root, int lo, int hi) {

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

void bst_destroy(Bst root) {

	if (root == NULL)
		return;

	free(root->value);
	free(root);
	bst_destroy(root->left);
	bst_destroy(root->right);
}
