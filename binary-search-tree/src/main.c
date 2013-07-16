#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binary-search-tree.h"


int main(void) {

	Bst root;
	char value[MAXLEN];
	int i, r, key, sum = 0;

	scanf("%d %s", &key, value);
	root = bst_put(NULL, key, value);

	while (scanf("%d %s", &key, value) == 2)
		bst_put(root, key, value);

	srand(time(NULL));
	for (i = 0; i < 1000000; i++) {
		r = rand() % 1000000 + 1;
		sum += bst_rank(root, r);
		sum += bst_select(root, r);
		sum += bst_floor(root, r);
		sum += bst_floor(root, r);
		sum += bst_size_range(root, r - (rand() % r), r);
	}
	printf("%d\n", sum);
	bst_print(root);

	bst_destroy(root);
	return 0;
}
