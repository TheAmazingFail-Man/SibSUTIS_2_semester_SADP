#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "bstree.h"

double wtime() {
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

int main()
{
	int n = 0, i, j;
	double time, alltime = 0;
	int w;
	struct bstree *tree, *node;
	FILE *book = fopen("book.txt", "r");
	while (!feof(book)) { //считает количество слов в книге
		if (fgetc(book) == '\n') {
			n++;
		}
	}
	char words[n];
	for(i = 0; i < n; i++) { //заполняет массив словами из книги
		fgets(words[n], n, book);
    }
	fclose(book);
	
//	printf("%s", words[n / 2 + 1]);
	
	tree = bstree_create(words[0], 0); //создает корень дерева
	
	for (i = 5000; i < 50000; i += 5000) {
  		bstree_add(tree, words[0], 0);
		//if (i % 10000 == 0) {
			//for (j = 0; j < i; j++) {
				w = getrand(0, i - 1);
				FILE *time = fopen("bstreetime.txt", "w");
				time = wtime();
				node = bstree_lookup(tree, w);
				time = wtime() - time;
				fprintf(time, "n = %d; Elapsed time: %.6f sec.\n", i - 1, alltime);
				alltime = alltime + time;
  			//}
  		//alltime = alltime / i;
  		//printf("n = %d; Elapsed time: %.6f sec.\n", i - 1, alltime);
  		//}
	}
	
	return 0;
}