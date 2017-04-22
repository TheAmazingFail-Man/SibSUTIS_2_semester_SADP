#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include "bstree.h"
#include "hashtab.h"

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
	int n = 0, m = 0, max = 0, i;
	double t, alltime = 0;
	srand(time(NULL));
	struct bstree *tree, *node;
	FILE *book = fopen("book.txt", "r");
	while (!feof(book)) {	//считает количество слов в книге и ищет самое длинное слово
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
	for(i = 0; i < n; i++) {	//заполняет массив словами из книги
		fscanf(book, "%s", words[i]);
    }
	fclose(book);
	
	tree = bstree_create(words[0], 0);	//создает корень дерева

	for (i = 1; i < n; i++) {	//эксперимент 1 для бинарного дерева
  		bstree_add(tree, words[i], i);
		if (i % 4999 == 0) {
			//for (j = 0; j < i; j++) {
				FILE *timebstree1 = fopen("Experiment1bstree.txt", "w");
				t = wtime();
				node = bstree_lookup(tree, words[getrand(0, i)]);
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
