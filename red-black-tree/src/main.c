#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binary-search-tree.h"


int main(void) {

	RBnode *root = NULL;
	char value[MAX_VALUE_LEN];
	int i, r, key;

	while (scanf("%d %s", &key, value) == 2)
		rbt_put(&root, key, value);

	srand(time(NULL));
	for (i = 0; i < 100000; i++) {
		r = rand() % 1000000 + 1;
		rbt_rank(root, r);
		rbt_select(root, r);
		rbt_floor(root, r);
		rbt_ceiling(root, r);
		rbt_size_range(root, r - (rand() % r), r);
	}
	rbt_print(root);
	rbt_destroy(root);

	return 0;
}
