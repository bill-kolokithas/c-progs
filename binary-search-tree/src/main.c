#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binary-search-tree.h"


int main(void) {

	BSTnode *root = NULL;
	char value[MAX_VALUE_LEN];
	int i, r, key;

	while (scanf("%d %s", &key, value) == 2)
		bst_put(&root, key, value);

	srand(time(NULL));
	for (i = 0; i < 100000; i++) {
		r = rand() % bst_size(root) + 1;
		bst_rank(root, r);
		bst_select(root, r);
		bst_floor(root, r);
		bst_ceiling(root, r);
		bst_size_range(root, r - (rand() % r), r);
	}
	bst_print(root);
	bst_destroy(root);

	return 0;
}
