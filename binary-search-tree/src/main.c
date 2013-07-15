#include <stdio.h>
#include <stdlib.h>
#include "binary-search-tree.h"


int main(void) {

	Bst root;
	char value[MAXLEN];
	int key;

	scanf("%d %s", &key, value);
	root = bst_put(NULL, key, value);

	while (scanf("%d %s", &key, value) == 2)
		bst_put(root, key, value);

	bst_print(root);

	bst_destroy(root);
	return 0;
}
