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

static int max(int a, int b);
static BStree _bst_min(BStree node);
static BStree _bst_max(BStree node);
static BStree _bst_select(BStree node, int key);
static BStree _bst_floor(BStree node, int key);
static BStree _bst_ceiling(BStree node, int key);
static BStree _bst_delete_min(BStree node, bool flag);
static BStree _bst_delete_max(BStree node, bool flag);

static BStree bst_new_node(int key, const Value value) {

	int len;
	BStree node;

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

BStree bst_put(BStree root, int key, const Value value) {

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
		root->value = realloc(root->value, (len = len > MAX_VALUE_LEN ? MAX_VALUE_LEN : len) + 1);
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

Value bst_get(BStree root, int key) {

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

int bst_is_empty(BStree root) {

	return bst_size(root) == 0;
}

int bst_size(BStree node) {

	if (node == NULL)
		return 0;

	return node->size;
}

int bst_contains(BStree root, int key) {

	return bst_get(root, key) != NULL;
}

int bst_height(BStree root) {

	if (root == NULL)
		return -1;

	return 1 + max(bst_height(root->left), bst_height(root->right));
}

static int max(int a, int b) {

	return a > b ? a : b;
}

int bst_min(BStree root) {

	if (bst_is_empty(root))
		return -1;

	return _bst_min(root)->key;
}

static BStree _bst_min(BStree node) {

	if (node->left == NULL)
		return node;

	return _bst_min(node->left);
}

int bst_max(BStree root) {

	if (bst_is_empty(root))
		return -1;

	return _bst_max(root)->key;
}

static BStree _bst_max(BStree node) {

	if (node->right == NULL)
		return node;

	return _bst_max(node->right);
}

int bst_floor(BStree root, int key) {

	BStree node = _bst_floor(root, key);
	if (node == NULL)
		return -1;

	return node->key;
}

static BStree _bst_floor(BStree node, int key) {

	int cmp;
	BStree temp;

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

int bst_ceiling(BStree root, int key) {

	BStree node = _bst_ceiling(root, key);
	if (node == NULL)
		return -1;

	return node->key;
}

static BStree _bst_ceiling(BStree node, int key) {

	int cmp;
	BStree temp;

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

int bst_size_range(BStree root, int lo, int hi) {

	if (lo > hi)
		return 0;
	else if (bst_contains(root, hi))
		return 1 + bst_rank(root, hi) - bst_rank(root, lo);

	return bst_rank(root, hi) - bst_rank(root, lo);
}

int bst_rank(BStree root, int key) {

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

int bst_select(BStree root, int k) {

	if (k < 0 || k >= bst_size(root))
		return -1;

	return _bst_select(root, k)->key;
}

static BStree _bst_select(BStree node, int k) {

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

BStree bst_delete_min(BStree root) {

	if (bst_is_empty(root))
		return NULL;

	return _bst_delete_min(root, true);
}

static BStree _bst_delete_min(BStree node, bool flag) {

	BStree right;

	if (node->left == NULL) {
		right = node->right;
		if (flag) {
			free(node->value);
			free(node);
		}
		return right;
	}
	node->left = _bst_delete_min(node->left, flag);
	node->size = 1 + bst_size(node->left) + bst_size(node->right);

	return node;
}

BStree bst_delete_max(BStree root) {

	if (bst_is_empty(root))
		return NULL;

	return _bst_delete_max(root, true);
}

static BStree _bst_delete_max(BStree node, bool flag) {

	BStree left;

	if (node->right == NULL) {
		left = node->left;
		if (flag) {
			free(node->value);
			free(node);
		}
		return left;
	}
	node->right = _bst_delete_max(node->right, flag);
	node->size = 1 + bst_size(node->left) + bst_size(node->right);

	return node;
}

BStree bst_delete(BStree node, int key) {

	BStree temp;
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

		temp = node;
		node = _bst_min(temp->right);
		node->right = _bst_delete_min(temp->right, false);
		node->left = temp->left;
		free(temp->value);
		free(temp);
	}
	node->size = 1 + bst_size(node->left) + bst_size(node->right);
	return node;
}

void bst_print(BStree root) {

	if (root == NULL)
		return;

	bst_print(root->left);
	printf("%d %s\n", root->key, root->value);
	bst_print(root->right);
}

void bst_print_keys(BStree root, int lo, int hi) {

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

void bst_destroy(BStree root) {

	BStree left, right;

	if (root == NULL)
		return;

	left = root->left;
	right = root->right;
	free(root->value);
	free(root);
	bst_destroy(left);
	bst_destroy(right);
}
