#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
//#include "bstree.h"
//#include "hashtab.h"

double wtime() {
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

typedef struct {
	char *value;
	int key;
	struct bstree *parent;
	struct bstree *left;
	struct bstree *right;
} bstree;

struct bstree *bstree_create(char *key, int value) {
	struct bstree *node = malloc(sizeof(*node));
	if (node != NULL) {
		node->key = key;
		node->value = value;
		node->left = NULL;
		node->right = NULL;
	}
	
	return node;
}

struct bstree *bstree_lookup(struct bstree *tree, int value) {
	while(tree != NULL) {
		if(value == tree->value) {
			return tree;
		} else if (value < tree->value) {
			tree = tree->left;
		} else {
			tree = tree->right;
		}
	}
	
	return tree;
}

int main()
{
	int n = 0, m = 0, max = 0, i;
	double t, alltime = 0;
	srand(time(NULL));
	struct bstree *tree, *node;
	FILE *book = fopen("book.txt", "r");
	while (!feof(book)) {
		if (fgetc(book) == '\n') {
			n++;
			max = m;
			m = 0;
		} else {
			m++;
		}
	}
	//words = (char*)malloc(n * max * sizeof(char));
	char words[n][max];
	for(i = 0; i < n; i++) {
		fscanf(book, "%s", words[i]);
    }
	fclose(book);
	
	tree = bstree_create(words[0], 0);

	for (i = 1; i < n; i++) {
  		bstree_add(tree, words[i], i);
		if (i % 5000 == 0) {
			//for (j = 0; j < i; j++) {
				FILE *timebstree1 = fopen("Experiment1bstree.txt", "w");
				t = wtime();
				node = bstree_lookup(tree, words[getrand(i - 5000, i)]);
				t = wtime() - t;
				alltime += t;
				fprintf(timebstree1, "n = %d; Elapsed time: %.6f sec.\n", i, alltime);
				fclose(timebstree1);
  		}
  		//alltime = alltime / i;
  		//printf("n = %d; Elapsed time: %.6f sec.\n", i, alltime);
  		//}
	}
	
	return 0;
}
