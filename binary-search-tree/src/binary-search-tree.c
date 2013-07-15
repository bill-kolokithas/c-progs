#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary-search-tree.h"


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

Value bst_get(Bst root, int key) {

	int cmp;

	if (root == NULL)
		return NULL;

	cmp = key - root->key;
	if (cmp < 0)
		return bst_get(root->left, key);
	if (cmp > 0)
		return bst_get(root->right, key);

	return root->value;
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

int bst_size_range(Bst root, int lo, int hi) {

	if (lo > hi)
		return 0;
	if (bst_contains(root, hi))
		return 1 + bst_rank(root, hi) - bst_rank(root, lo);

	return bst_rank(root, hi) - bst_rank(root, lo);
}

int bst_height(Bst root) {

	return root ? 1 + max(bst_height(root->left), bst_height(root->right)) : -1;
}

Bst _bst_min(Bst node) {

	return node->left == NULL ? node : _bst_min(node->left);
}

Bst _bst_max(Bst node) {

	return node->right == NULL ? node : _bst_max(node->right);
}

Bst _bst_floor(Bst node, int key) {

	int cmp;
	Bst test;

	if (node == NULL)
		return NULL;

	cmp = key - node->key;
	if (cmp == 0)
		return node;
	if (cmp < 0)
		return _bst_floor(node->left, key);

	test = _bst_floor(node->right, key);
	if (test != NULL)
		return test;

	return node;
}

Bst _bst_ceiling(Bst node, int key) {

	int cmp;
	Bst test;

	if (node == NULL)
		return NULL;

	cmp = key - node->key;
	if (cmp == 0)
		return node;
	if (cmp < 0) {
		test = _bst_ceiling(node->left, key);
		if (test != NULL)
			return test;
		return node;
	}
	return _bst_ceiling(node->right, key);
}

Bst _bst_select(Bst node, int k) {

	int test;

	if (node == NULL)
		return NULL;

	test = bst_size(node->left);
	if (test > k)
		return _bst_select(node->left, k);
	if (test < k)
		return _bst_select(node->right, k - test - 1);

	return node;
}

int bst_rank(Bst root, int key) {

	int cmp;

	if (root == NULL)
		return 0;

	cmp = key - root->key;
	if (cmp < 0)
		return bst_rank(root->left, key);
	if (cmp > 0)
		return 1 + bst_size(root->left) + bst_rank(root->right, key);

	return bst_size(root->left);
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
